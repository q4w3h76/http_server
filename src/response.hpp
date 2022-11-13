#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "server.hpp"
#include <string>

class Response
{
    std::string m_response,
                m_method,
                m_path,
                m_type;

    void request_parse(const std::string&);
    void html_parse(const std::string&);
public:
    Response(const std::string&, const std::string&);
    ~Response();

    Response(const Response&);
    Response& operator=(const Response&);

    inline const std::string& get_response()
    { return m_response; }
};

#endif // RESPONSE_HPP
