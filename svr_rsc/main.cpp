/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:21:09 by yismaili          #+#    #+#             */
/*   Updated: 2023/03/26 16:52:06 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http_server.hpp"

int main() {
    http::tcpServer server1(8080, "0.0.0.0");
    server1.run();
    return 0;
}