#ifndef IO_WORKER_HPP
#define IO_WORKER_HPP

#include <array>
#include <thread>
#include <sys/epoll.h>

class Client;

class Worker
{
    static constexpr unsigned int m_max_clients = 20000;
    int m_epoll;
    std::array<struct epoll_event, m_max_clients> m_clients_fd;
    std::thread* m_thread;

    void sending(Client*);
    void reading(Client*);
public:
    Worker();
    ~Worker();

    void run();
    void add_fd(Client*);

    Worker(const Worker&) = delete;
    Worker& operator=(const Worker&) = delete;
};

#endif // IO_WORKER_HPP
