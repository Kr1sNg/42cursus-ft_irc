/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:59:45 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/09/12 09:25:02 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ircserv.h"
#include "../includes/Server.hpp"

Server::Server(char	*port, char *password)
{
	for (size_t i = 0; port[i] != '\0'; ++i)
	{
		if (!std::isdigit(port[i]))
			throw std::invalid_argument("Error: Invalid port number");
	}
	_port = std::atoi(port);
	_password = password;
	initServerSocket();
}
Server::~Server()
{
	close(_server_fd);
}

void	Server::initServerSocket()
{
	// create new server socket (IPv4 address family and TCP stream socket) and return a fd
	_server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_server_fd < 0)
		throw std::runtime_error("Error: socket() failed");
	
	// enable SO_REUSEADDR option on socket (let us re-bind addr without waiting)
	int	yes = 1;
	if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0)
		throw std::runtime_error("Error: setsockopt() failed");
	
	// Set server socket to non-blocking mode (accept()/recv()/send() must not block) 
	int	flags = fcntl(_server_fd, F_GETFL, 0);
	if (fcntl(_server_fd, F_SETFL, flags | O_NONBLOCK) < 0)
		throw std::runtime_error("Error: fcntl() failed");
	
	struct sockaddr_in addr;
	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET; //IPv4
	addr.sin_addr.s_addr = INADDR_ANY;	//listen on all network interfaces (0.0.0.0)
	addr.sin_port = htons(_port); // convert port from host byte order to network byte order
	
	// assign address `addr` to the socket `_server_fd`, without bind we can't accept connections on a specific port
	if (bind(_server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		throw std::runtime_error("Error: bind() failed");

	if (listen(_server_fd, SOMAXCONN) < 0)
		throw std::runtime_error("Error: listen() failed");

	// Add the server (listening) socket to poll() list
	struct pollfd	server_poll;
	server_poll.fd = _server_fd;
	server_poll.events = POLLIN; // set event to POLLIN for reading data
	server_poll.revents = 0;
	_poll_fds.push_back(server_poll);
	
	std::cout << "[INFO] Server listening on port " << _port << "." << std::endl;
}

void	Server::acceptClient()
{
	struct sockaddr_in	client_addr;
	socklen_t			client_len = sizeof(client_addr);

	int	client_fd = accept(_server_fd, (struct sockaddr *)&client_addr, &client_len);
	if (client_fd < 0)
		return ;
	
	// Set client socket to non-blocking mode
	fcntl(client_fd, F_SETFL, O_NONBLOCK);
	
	struct pollfd	client_poll;
	client_poll.fd = client_fd;
	client_poll.events = POLLIN;
	client_poll.revents = 0;
	_poll_fds.push_back(client_poll);

	_clients[client_fd] = "";

	std::cout << "[INFO] New client connected (fd=" << client_fd << ")" << std::endl;
}

void	Server::handlerClientData(size_t index)
{
	int	client_fd = _poll_fds[index].fd;
	char	buffer[BUFFER_SIZE];
	std::memset(buffer, 0, BUFFER_SIZE);

	ssize_t	bytes = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
	if (bytes <= 0)
	{
		std::cout << "[INFO] Client disconnected (fd=" << client_fd << ")" << std::endl;
		close(client_fd);
		// server::clearclient
		_poll_fds.erase(_poll_fds.begin() + index);
		_clients.erase(client_fd);
		return ;
	}

	// append received data to buffer
	_clients[client_fd] += buffer;

	// check for complete IRC messages (\r\n terminated) -> Konversation only \n
	size_t	pos;
	while ((pos = _clients[client_fd].find("\n")) != std::string::npos)
	{
		std::string	message = _clients[client_fd].substr(0, pos);
		_clients[client_fd].erase(0, pos + 2);

		std::cout << "[RECV] FD=" << client_fd << ": " << message << std::endl;

		// Echo message back to client
		std::string reply = ":ircserv ECHO: " + message + "\n";
		send(client_fd, reply.c_str(), reply.size(), 0);
	}
}
		
void	Server::run()
{
	while (true)
	{
		int	ready = poll(&_poll_fds[0], _poll_fds.size(), -1);
		if (ready < 0)
		{
			// if (errno == EINTR)
			// 	continue ;
			throw std::runtime_error("poll() failed");
		}
		for (size_t i = 0; i < _poll_fds.size(); ++i)
		{
			//-> check if there's data to read on fd
			if (_poll_fds[i].revents & POLLIN)
			{
				if (_poll_fds[i].fd == _server_fd)
					acceptClient();
				else
					handlerClientData(i);
				
			}
		}
	}
}
