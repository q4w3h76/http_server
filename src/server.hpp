#ifndef SERVER_HPP
#define SERVER_HPP

#include <cstddef>

class Listener;
class Worker;

class Server
{
    Listener* m_listener;
    const size_t m_nproc;
    Worker** m_workers;
public:
    Server(const unsigned short, const char*);
    ~Server();

    void run();

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
};

#endif // SERVER_HPP
