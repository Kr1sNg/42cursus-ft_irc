/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:31:53 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/09/11 16:52:11 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _IRCSERV_H_
# define _IRCSERV_H_

#include <exception>
#include <map>
#include <iostream>
#include <vector>
#include <sys/socket.h>	//-> for int socket(int domain, int type, int protocol);
// #include <sys/types.h> //-> for socket()
#include <netinet/in.h> //-> for sockaddr_in
#include <fcntl.h>	//->for fcntl()
#include <unistd.h> //-> for close()
#include <arpa/inet.h> //->for inet_ntoa()
#include <poll.h>	//->for poll()
#include <csignal> //for signal
#include <string>
#include <cstring>

#define BUFFER_SIZE 42

class Channel;
class Client;
class Server;

#endif