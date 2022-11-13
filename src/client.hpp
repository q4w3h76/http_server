#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client
{
    int m_socket;
    std::string m_ip,
                m_request,
                m_response,
                m_path_html;
public:
    Client(int, const char*, const char*);
    ~Client();
    Client(const Client&);
    Client& operator=(const Client&);

    void forming_response(const std::string&);

    // get methods
    inline const std::string& get_response()
    { return m_response; }
    inline const std::string& get_request()
    { return m_request; }
    inline const std::string& get_ip()
    { return m_ip; }
    inline int get_socket()
    { return m_socket; }
};

#endif // CLIENT_HPP
