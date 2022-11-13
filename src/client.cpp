#include "client.hpp"
#include "response.hpp"
#include <unistd.h> // for close()

Client::Client(int socket, const char* ip, const char* path_html)
    : m_socket(socket), m_ip(ip), m_path_html(path_html)
{}

Client::~Client()
{
    close(m_socket);
}

Client::Client(const Client& client)
    : m_socket(client.m_socket), m_ip(client.m_ip),
    m_request(client.m_request), m_response(client.m_response),
    m_path_html(client.m_path_html)
{}

Client& Client::operator=(const Client& client)
{
    m_socket = client.m_socket;
    m_ip = client.m_ip;
    m_request = client.m_request;
    m_response = client.m_response;
    m_path_html = client.m_path_html;
    return *this;
}

void Client::forming_response(const std::string& request)
{
    if(m_request == request)
        return;
    m_request = request;

    Response tmp(m_request, m_path_html);
    m_response = tmp.get_response();
}
