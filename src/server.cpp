#include "server.hpp"
#include "listener.hpp"
#include "worker.hpp"
#include <unistd.h>
#include <iostream>

Server::Server(const unsigned short port, const char* path_html)
    : m_listener(new Listener(port, path_html)), m_nproc(sysconf(_SC_NPROCESSORS_ONLN)),
    m_workers(new Worker*[m_nproc])
{
    for(size_t i = 0; i < m_nproc; ++i)
        m_workers[i] = new Worker;
}

Server::~Server()
{
    delete m_listener;
    for(size_t i = 0; i < m_nproc; ++i)
        delete m_workers[i];
    delete [] m_workers;
}

void Server::run()
{
    std::cout << m_nproc << std::endl;
    while(true)
        for(size_t i = 0; i < m_nproc; ++i)
        {
            Client* client = m_listener->accept_client();
            if(client != nullptr)
                m_workers[i]->add_fd(client);
        }
}
