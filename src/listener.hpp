#ifndef LISTENER_HPP
#define LISTENER_HPP

#include <fcntl.h>

class Client;

class Listener
{
    int m_listener;
    const char* m_path_html;

    inline int set_nonblocking(const int socket)
    { return fcntl(socket, F_SETFL, fcntl(socket, F_GETFL, 0) | O_NONBLOCK); }
public:
    Listener(const unsigned short, const char*);
    ~Listener();

    Client* accept_client(); // return socket of new client

    Listener(const Listener&) = delete;
    Listener& operator=(const Listener&) = delete;
};

#endif // LISTENER_HPP
