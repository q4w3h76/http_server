#include "listener.hpp"
#include "client.hpp"
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <cstring>

Listener::Listener(const unsigned short port, const char* path_html)
    : m_path_html(path_html)
{
    struct sockaddr_in m_local;
    memset(&m_local, 0, sizeof(m_local));
    m_local.sin_family = AF_INET;
    m_local.sin_port = htons(port);
    m_local.sin_addr.s_addr = htonl(INADDR_ANY);
    // create master socket
    m_listener = socket(AF_INET, SOCK_STREAM, 0);
    if(m_listener < 0)
        throw std::runtime_error("Failed to create master socket");
    // make socket non-blocking
    if(set_nonblocking(m_listener) < 0)
        throw std::runtime_error("Failed to make socket non-blocking");
    if(bind(m_listener, (struct sockaddr*)&m_local, sizeof(m_local)) < 0)
        throw std::runtime_error("Failed call of bind");
    if(listen(m_listener, 128) < 0)
        throw std::runtime_error("Failed call of listen");
}

Listener::~Listener()
{
    close(m_listener);
}

Client* Listener::accept_client()
{
    struct sockaddr_in peer;
    socklen_t peerlen = sizeof(peer);
    int fd = accept(m_listener, (struct sockaddr*)&peer, &peerlen);
    set_nonblocking(fd);
    if(fd < 0)
        return nullptr;
    else
        return new Client(fd, inet_ntoa(peer.sin_addr), m_path_html);
}
