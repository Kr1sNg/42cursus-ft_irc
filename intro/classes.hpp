/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classes.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 08:53:54 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/09/05 22:57:25 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

class Client
{
	private:
		int			_Fd; // client fd
		std::string	_IpAdd;	// client ip address
	
	public:
		Client(void) { };
		~Client() { };
		
		int		GetFd() { return _Fd; }
		void	SetFd(int fd) { _Fd = fd; }
		void	SetIpAdd(std::string ipadd)	{ _IpAdd = ipadd; }
		
};

class Server
{
	private:
		int	_Port; //server post
		int	_SerSocketFd; // server Socket fd
		static bool	_Signal; // static bool for signal -> class variable (shared by all objects)
		std::vector<Client> _clients; // -> vector of storing clients
		std::vector<struct pollfd> _fds; // vector of pollfd  <std struct in poll.h>

	public:
		Server() { _SerSocketFd = -1; } // default constructor
		~Server() {};
		
		void	ServerInit(); //server initialization
		void	SerSocket();	//server socket creation
		void	AcceptNewClient(); // accept new client
		void	ReceiveNewData(int fd); //receive new data from a registered client
		
		static void	SignalHandler(int signum); //signal handler
		
		void	CloseFds(); // close fds
		void	ClearClients(int fd) // clear clients
		{
			for (size_t i = 0; i < _fds.size(); ++i)
			{
				if (_fds[i].fd == fd)
				{
					_fds.erase(_fds.begin() + i);
					break;
				}
			}
			for (size_t i = 0; i < _clients.size(); ++i)
			{
				if (_clients[i].GetFd() == fd)
				{
					_clients.erase(_clients.begin() + i);
					break;
				}
			}
		}
};



