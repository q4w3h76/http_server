#include "response.hpp"
#include <unistd.h>
#include <cstring>
#include <fstream>
#include <sstream>

Response::Response(const std::string& request, const std::string& path)
{
    request_parse(request); 
    html_parse(path);
}

Response::~Response()
{
    
}

Response::Response(const Response& response)
    : m_response(response.m_response),m_method(response.m_method),
    m_path(response.m_path), m_type(response.m_type)
{}

Response& Response::operator=(const Response& response)
{
    m_response = response.m_response;
    m_method = response.m_method;
    m_path = response.m_path;
    m_type = response.m_type;
    return *this;
}

void Response::request_parse(const std::string& request)
{
    char str[request.length()];
    strcpy(str, request.c_str());
    char* tmp = strtok(str, " ");
    m_method = (tmp != NULL)? tmp : "";
    tmp = strtok(NULL, " ");
    m_path = (tmp != NULL)? tmp : "";
    tmp = strtok(NULL, " \r");
    m_type = (tmp != NULL)? tmp : "";
}

void Response::html_parse(const std::string& path)
{
    // working with path
    std::string full_path(path);
    if((m_path == "/")||(m_path == ""))
        full_path += m_path += "index.html";
    else
        full_path += m_path;
    if(m_path.find(".html") == std::string::npos)
        full_path += ".html";
    
    std::string html;
    char current;
    std::stringstream response;
    // opening the desired html file
    std::ifstream f_html(full_path);
    if(f_html.is_open())
    {
        // reading html file
        while(!f_html.eof())
        {
            f_html.get(current);
            html += current;
        }
        f_html.close();
        // forming response
        response << "HTTP/1.1 200 OK\r\n"
        << "Content-Length: " << html.length()
        << "\r\n\r\n" << html << "\r\n";
    }
    else
    {
        f_html.open(std::string(path+std::string("/404.html")));
        // reading html file
        while(!f_html.eof())
        {
            f_html.get(current);
            html += current;
        }
        // forming response
        response << "HTTP/1.1 404 Not Found\r\n"
        << "Content-Length: " << html.length()
        << "\r\n\r\n" << html << "\r\n";
    }
    m_response = response.str();
}
