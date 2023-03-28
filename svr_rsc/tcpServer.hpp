/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcpServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:29:15 by yismaili          #+#    #+#             */
/*   Updated: 2023/03/28 22:05:19 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <sstream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include<fstream>
#include <arpa/inet.h>

namespace http{
 class tcpServer{
        public:
          
         tcpServer() {}
         ~tcpServer(){}
        tcpServer &init_data(int port_, std::string ip_add){
           sockfd =  -1;
           port = port_;
           sock_addr_len = 0;
           ip_addr = ip_add;
            // AF stands for Address Family and PF stands for Protocol Family
            // This construct holds the information about the address family, port number, Internet address
            serv_addr.sin_family = AF_INET; // Address family // IPv4 Internet protocols    !!!get add info
            serv_addr.sin_addr.s_addr = inet_addr(ip_addr.c_str());  // Internet "address inet_addr(ip_addr.c_str());"
            serv_addr.sin_port = htons(port); // Port number // Network to Host Shor
            if(start_server() == false){
               std::cout<<"Failed to start server "<<std::endl;
               exit(1);
            }
            return (*this);
         }
         
        int git_sockfd()const{
            return (sockfd);
        }
        
        unsigned int &get_sock_addr_len() {
            return (sock_addr_len);
        }
        
        sockaddr_in &git_serv_addr(){
            return (serv_addr);
        }
        bool start_server() {
    // Socket System Call
            //Creates a socket and returns a Socket Descriptor (like file descriptor) which is an integer value
            sockfd = socket(AF_INET, SOCK_STREAM, 0); 
            //domain: specifies the communication domain, such as AF_INET for IPv4 or AF_INET6 for IPv6.
            //type: specifies the type of socket, such as SOCK_STREAM for a TCP socket or SOCK_DGRAM for a UDP socket.
            /*protocol: specifies the protocol to be used with the socket, such as IPPROTO_TCP for TCP or IPPROTO_UDP for UDP. 
            This argument is usually set to 0,which allows the operating system to choose the 
            appropriate protocol based on the socket type and domain.*/
            if (sockfd < 0) {
                return (false);
            }  
            sock_addr_len = sizeof(serv_addr);
    // Bind System Call
            //associate a socket with a specific address and port number
            if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
                //the second is a pointer to a struct sockaddr structure that contains the address
                return (false);
            }
            if (listen(sockfd, SOMAXCONN) < 0){
            //The second parameter specifies the number of requests that the system queues before it executes the accept()
               std::cout<<"Socket listen failed"<<std::endl;
               exit(1);
            }
            std::cout<<" Listening on adress ... "<<std::endl;
            return true;
    }
     public:
        int sockfd;
        int port;
        struct sockaddr_in serv_addr;
        std::string serv_message;
        unsigned int sock_addr_len;
        std::string ip_addr;   
 };
}