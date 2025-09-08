/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 22:57:44 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/09/08 10:40:59 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes.hpp"

bool	Server::_Signal = false; //-> initialize the static class variable

void	Server::SignalHandler(int signum)
{
	(void)signum;
	std::cout << std::endl << "Signal Received!" << std::endl;
	Server::_Signal = true; // -> when there's a signal comes, set static class variable to true to stop the server
}

void	Server::CloseFds(void)
{
	for (size_t i = 0; i < _clients.size(); ++i)
	{
		std::cout << "Client <" << _clients[i].GetFd() << "> disconnected" << std::endl;
		close(_clients[i].GetFd());
	}
	if (_SerSocketFd != -1) //-> close server socket
	{
		std::cout << "Server <" << _SerSocketFd << "> disconnected" << std::endl;
		close(_SerSocketFd);
	}
}

void	Server::SerSocket(void)
{
	struct sockaddr_in	add; // std struct contains info about server address (IPv4)
	struct pollfd		NewPoll; // used for monitoring fds for I/O events.
	// its commonly employed with poll() system call to perform multiplexed I/O
	// allowing progr to wait for events on multiple fds simultanouesly without having to resort to blocking I/O operations 
	
	add.sin_family = AF_INET; //-> set the address family to IPv4
	add.sin_port = htons(this->_Port); //->convert 16bit unsigned short int from host byte order to network byte order
	add.sin_addr.s_addr = INADDR_ANY; //-> represent any IP add, meaning socket will be bound to all available network interfaces on the host.
	
	_SerSocketFd = socket(AF_INET, SOCK_STREAM, 0); //-> create server socket
	if (_SerSocketFd == -1)
		throw std::runtime_error("fail to create socket");
	
	int en = 1;
	// set the socket option (SO_REUSEADD) to reuse the address
	if (setsockopt(_SerSocketFd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1)
		throw std::runtime_error("failed to set option (SO_REUSEADDR) on socket");
	// set the socket option (O_Nonblock) for non-blocking socket
	if (fcntl(_SerSocketFd, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("failed to set option (O_NONBLOCK) on socket");
	// bind the socket to address
	if (bind(_SerSocketFd, (struct sockaddr *)&add, sizeof(add)) == -1)
		throw std::runtime_error("failed to bind socket");
	// listen for incomming connections and making the socket a passive socket
	if (listen(_SerSocketFd, SOMAXCONN) == -1)
		throw std::runtime_error("listen() failed");
	
	
	
}

void	Server::ServerInit()
{
	this->_Port = 4444;
	SerSocket(); // create server socket
	
	std::cout << "Server <" << _SerSocketFd << "> connected" << std::endl;
	std::cout << "Waiting to accept a connection...\n";
}

int	main(void)
{
	Server	ser;
	std::cout << "---- Server ----" << std::endl;
	try
	{
		signal(SIGINT, Server::SignalHandler); //-> catch the ctrl-C
		signal(SIGQUIT, Server::SignalHandler); //-> catch the ctrl-\'
		ser.ServerInit(); //-> initialize the server
	}
	catch(const std::exception& e)
	{
		ser.CloseFds(); //->close fd
		std::cerr << e.what() << '\n';
	}
	std::cout << "The server closed!" << std::endl;
	return (0);
}