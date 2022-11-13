#include "worker.hpp"
#include "client.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdexcept>

// public methods
Worker::Worker()
{
    m_epoll = epoll_create1(0);
    if(m_epoll < 0)
        throw std::runtime_error("Failed to create epoll");
    m_thread = new std::thread(&Worker::run, this);
}

Worker::~Worker()
{
    m_thread->detach();
    delete m_thread;
}

void Worker::run()
{
    while(true)
    {
        unsigned int n = epoll_wait(m_epoll, m_clients_fd.data(), m_max_clients, -1);
        for(unsigned int i = 0; i < n; ++i)
        {
            struct epoll_event& event = m_clients_fd[i];
            if((event.events & EPOLLERR) || (event.events & EPOLLHUP))
                close(event.data.fd);
            else if(event.events & EPOLLIN)
                reading((Client*)event.data.ptr);
            else if(event.events & EPOLLOUT)
                sending((Client*)event.data.ptr);
        }
    }
}

void Worker::add_fd(Client* client)
{
    struct epoll_event tmp_event;
    int fd = client->get_socket();
    tmp_event.data.fd = fd;
    tmp_event.events = EPOLLIN | EPOLLET;
    tmp_event.data.ptr = client;
    // added fd in epoll
    if(epoll_ctl(m_epoll, EPOLL_CTL_ADD, fd, &tmp_event) < 0)
        delete client;
}

// private methods

void Worker::sending(Client* client)
{
    std::string response = client->get_response();
    int fd = client->get_socket();
    send(fd, response.c_str(), response.length(), MSG_NOSIGNAL);
    // deleted fd from epoll
    epoll_ctl(m_epoll, EPOLL_CTL_DEL, fd, NULL);
    delete client;
}

void Worker::reading(Client* client)
{
    const unsigned int buffer_size = 3000;
    int fd = client->get_socket();
    char buffer[buffer_size];
    int size = recv(fd, buffer , buffer_size, MSG_NOSIGNAL);
    if(size <= 0)
    {
        delete client;
        return;
    }
    buffer[size] = '\0';
    
    client->forming_response(std::string(buffer));

    struct epoll_event tmp_event;
    tmp_event.data.fd = fd;
    tmp_event.data.ptr = client;
    tmp_event.events = EPOLLOUT | EPOLLET;
    // modified event in epoll
    if(epoll_ctl(m_epoll, EPOLL_CTL_MOD, fd, &tmp_event) < 0)
        delete client;
}
