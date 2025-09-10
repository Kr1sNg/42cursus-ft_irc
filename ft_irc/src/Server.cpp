/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:59:45 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/09/10 12:52:47 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ircserv.h"
#include "../includes/Server.hpp"

Server::Server(int port, const std::string &password): _port(port), _password(password)
{
	initServerSocket();
}
Server::~Server()
{
	close(_server_fd);
}

void	Server::initServerSocket()
{
	_server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_server_fd < 0)
		throw std::runtime_error("Error: socket() failed");
	
	int	yes = 1;
	if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0)
		throw std::runtime_error("Error: setsockopt() failed");
	
	// Set server socket to non-blocking mode
	fcntl(_server_fd, F_SETFL, O_NONBLOCK);
	
	
}
		void	acceptClient();
		void	handlerClientData(size_t index);
		
	public:
		
		
		// std::map<std::string, Channel>	_channels;
		
		void	run();