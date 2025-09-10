/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:31:53 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/09/10 12:11:21 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _IRCSERV_H_
# define _IRCSERV_H_

#include <iostream>
#include <exception>
#include <vector>
#include <map>
#include <string>
#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 512

class Channel;
class Client;
class Server;

#endif