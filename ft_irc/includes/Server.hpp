/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:59:34 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/09/14 22:41:12 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SERVER_
# define _SERVER_

#include "ircserv.h"

class Server
{
	private:
		int			_port;
		std::string	_password;
		int			_server_fd;
		
		std::vector<struct pollfd>	_poll_fds;
		std::map<int, std::string>	_clients;

		Server(void);
		Server(Server const &src);
		Server	&operator=(Server const &rhs);

		void	initServerSocket(void);
		void	acceptClient(void);
		void	handlerClientData(size_t index);
		
	public:
		Server(char *port, char *password);
		~Server();
		
		// std::map<std::string, Channel>	_channels;
		
		void	run(void);
		
		//getter
		int					getSocket(void);
		std::string const	&getPassword(void);
		// Client	*getClientByNick(const std::string &nick);
		
		void	handlerCommand(Client &client, std::string const &line);
};

#endif