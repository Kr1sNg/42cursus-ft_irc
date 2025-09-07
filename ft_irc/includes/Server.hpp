/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:59:34 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/09/05 19:03:38 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SERVER_
# define _SERVER_

#include <iostream>
#include <exception>
#include <vector>

class Server
{
	private:
		Server(void);
		Server(Server const &src);
		Server	&operator=(Server const &rhs);

		std::string	port;
		int			serverSocket;
		std::string	password;
		
		std::vector<Client>	clients;
		
	public:
		Server(int ac, char *av[]);
		~Server();
		
};




#endif