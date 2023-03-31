#include "server.hpp"
#include <sstream>
#include <string>

std::string toLower(std::string str)
{
  for (std::string::iterator it = str.begin(); it != str.end(); ++it)
    *it = std::tolower(*it);
  return str;
}

std::string toUpper(std::string str) {
  for (std::string::iterator it = str.begin(); it != str.end(); ++it) 
    *it = std::toupper(*it);
  return str;
}

// int count_lines(const std::string& str) {
//     int count = 1;
//     for (char c : str) {
//         if (c == '\n') {
//             count++;
//         }
//     }
//     return count;
// }

bool isIpAddress(const std::string& ip) {
    int numDots = 0;
    std::string temp = "";

    for (int i = 0; i < ip.size(); i++)
    {
        if (ip[i] == '.') 
        {
            numDots++;
            if (numDots > 3)
                return 0;
            if (temp.size() == 0 || std::stoi(temp) > 255)
                return 0;
            temp = "";
        } 
        else if (!isdigit(ip[i])) 
            return 0;
        else 
            temp += ip[i];
    }
    if (temp.size() == 0 || std::stoi(temp) > 255 || numDots != 3) 
        return 0;
    return 1;
}

int isDomainName(const std::string& domainName)
{

    if (domainName.empty())
        return 0;
    int i = 0;
    while (domainName[i]) 
    {
        char c =  domainName[i];
        if (!std::isalnum(c) && c != '-' && c != '.') 
            return 0;
        i++;
    }

    if (domainName.front() == '-' || domainName.back() == '-')
        return 0;
    if (domainName.find('.') == std::string::npos) 
        return 0;
    return 1;
}

int search_char(std::string str, char c)
{
    int i = 0;
    while (str[i])
    {
        if(str[i] == c)
            return (1);
        i++;
    }
    return (0);
}

int is_number(const std::string& str)
{
    size_t i = 0;
    int exp = 0;
    int digit = 0;
    int flag = 0;

    for (i = 0; i < str.size(); i++)
    {
        if (i == 0 && (str[i] == '+' || str[i] == '-')) {
            i++;
            continue;
        }
        if (str[i] == 'e' || str[i] == 'E') {
            if (exp || !digit) {
                return 0;
            }
            exp = 1;
            if (i + 1 < str.size() && (str[i + 1] == '+' || str[i + 1] == '-')) {
                if(str[i + 1] == '-')
                    flag = 1;
                i++;
            }
            continue;
        }
        if(!isdigit(str[i]))
            return (0);
        digit = 1;
    }
    if(i == 1 && (str[0] == '+' || str[0] == '-'))
        return (0);
    if(flag)
        return (-1);
    return (1);
}

int ft_number(std::string value, std::string line)
{
    int port;
    if (!is_number(value))
    {
        std::cerr << " ERROOR : " << line << std::endl;
        exit (1);
    }
    try
    {
        port = std::stod(value);
    }
    catch(const std::exception& e)
    {
        std::cerr << " ERROOR : " << line << std::endl;
        exit (1);
    }
    return (port);
}

void ft_error(std::string line, std::string err)
{
    std::cerr << err <<" : " << line << std::endl;
    exit (1);
}

void is_empty_value(std::string value, std::string line)
{
        if (value.empty())
            ft_error(line, "Error");
}

int ft_numbers_value(std::istringstream &iss)
{
    int i = 0;
    std::string value;
    while (iss >> value)
        i++;
    return (i);
}

int ft_non_alphabetic(std::string value)
{
    int i = 0;
    while (value[i])
    {
        if (!isalpha(value[i]))
            return (1);
        i++;
    }
    return (0);
}

void ft_check_index(std::string index_file, std::string line)
{
    size_t i = index_file.find_last_of(".");
    if (i == -1)
        ft_error(line, "Error");
    std::string filedot = index_file.substr(i + 1);
    if (filedot != "html" && filedot != "php" && filedot != "htm" && filedot != "css"
        && filedot != "js" && filedot != "jpg" && filedot != "jpeg" && filedot != "png" && filedot != "gif"
        && filedot != "txt" && filedot != "xml" && filedot != "json") 
            ft_error(line, "Error");
}

void check_methods(std::string method, std::string line)
{
    if (method != "get" && method != "post" && method != "put" && method != "delete" && method != "head"
        && method != "options" && method != "connect" && method != "trace")
            ft_error(line, "Error is not method");
}

std::string ft_method(std::string value, std::string line, std::vector<std::string> v)
{
    value = toLower(value);
    check_methods(value, line);
    value = toUpper(value);
    std::vector<std::string>::iterator it = std::find(v.begin(), v.end(), value);
    if(it != v.end())
        ft_error(line, "error duplicate index");
    return (value);
}

server::server(Data_config data)
{
    std::istringstream ss(data.data_server);
    std::string line;
    int c_server_name = 0;
    int c_host = 0;
    int c_root = 0;
    int c_client_max_body_size = 0;
    int c_autoindex = 0;
    while (getline(ss, line))
    {
        if(line.empty() || line[0] == '#')
            continue;
        if (!search_char(line, '}') && !search_char(line, '{'))
        {
            if (line[line.size() - 1] != ';')
            {
                std::cerr << "missing ; in " << line << std::endl;
                exit (1);
            }
            line.erase(line.size() - 1);
        }
        std::string key, value;
        std::istringstream iss(line);
        iss >> key >> value;
        //std::cout << key << "|" << "\n";
        key = toLower(key);
        if (key == "server_name")
        {
            if(c_server_name)
                ft_error(line, "Duplicated");
            is_empty_value(value, line);
            if (ft_numbers_value(iss) || ft_non_alphabetic(value))
                ft_error(line, "Error");
            c_server_name++;
            _server_name.push_back(value);
        }
        else if (key == "host")
        {
            if(c_host)
                ft_error(line, "Duplicated");
            is_empty_value(value, line);
            if (ft_numbers_value(iss) || (!isDomainName(value) && !isIpAddress(value)))
                ft_error(line, "Error");
            c_host++;
            _host = value;
        }
        else if (key == "listen")
        {
            is_empty_value(value, line);
            int port = ft_number(value, line);
            if (port < 1 || port > 65535)
            {
                std::cerr << " ERROOR : " << line << std::endl;
                exit (1);
            }
            _listen.push_back(port);
            while (iss >> value)
            {
                int port = ft_number(value, line);
                if (port < 1024 || port > 65535)
                {
                    std::cerr << " ERROOR : " << line << std::endl;
                    exit (1);
                }
                _listen.push_back(port);
            }
        }
        else if (key == "root")
        {
            if(c_root)
                ft_error(line, "Duplicated");
            is_empty_value(value, line);
            if (ft_numbers_value(iss))
                ft_error(line, "Error");
            c_root++;
            _root = value;
        }
        else if (key == "client_max_body_size")
        {
            is_empty_value(value, line);
            if (ft_numbers_value(iss) || c_client_max_body_size)
                ft_error(line, "Error");
            int size = ft_number(value, line);
            if (size < 0)
                ft_error(line, "Error size is negative");
            c_client_max_body_size++;
            _client_max_body_size = size;
        }
        else if (key == "error_page")
        {
            int error_code = ft_number(value, line);
            if (error_code < 100 || error_code > 599)
                ft_error(line, "Error");
            is_empty_value(value, line);
            iss >> value;
            is_empty_value(value, line);
            if (ft_numbers_value(iss) )
                ft_error(line, "Error");
            _error_page[error_code] = value;
        }
        else if (key == "index")
        {
            is_empty_value(value, line);
            ft_check_index(value, line);
            _index.push_back(value);
            while (iss >> value)
            {
                ft_check_index(value, line);
                _index.push_back(value);
            }
        }
        else if (key == "allow_methods")
        {
            is_empty_value(value, line);
            value = ft_method(value, line, _allow_methods);
            _allow_methods.push_back(value);
            while (iss >> value)
            {
                value = ft_method(value, line, _allow_methods);
                _allow_methods.push_back(value);
            }
        }
        else if (key == "autoindex")
        {
            if (c_autoindex)
                ft_error(line, "Erro duplicated");
            is_empty_value(value, line);
            value = toLower(value);
            if (value == "on")
                _autoindex = true;
            else if (value == "off")
                _autoindex = false;
            else
                ft_error(line, "Error");
            if (ft_numbers_value(iss))
                ft_error(line, "Error");
            c_autoindex++;
        }
        else if (!search_char(line, '}') && !search_char(line, '{'))
        {
            std::cerr << " ERROOR : " << line << std::endl;
            exit (1);
        }
    }
}

server::~server()
{
}