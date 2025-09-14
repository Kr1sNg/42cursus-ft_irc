/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:59:07 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/09/14 22:47:16 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CLIENT_
# define _CLIENT_

#include "ircserv.h"

class Client
{
	private:
		int			_client_fd;
		std::string	_nick;
		std::string	_user;
		std::string	_name;
		bool		_passGiven;
		bool		_registered;

		Client(void);
		Client(Client const &src);
		Client	&operator=(Client const &rhs);
		
	public:
		Client(int fd);
		~Client();
		
		int					getSocket(void) const;
		std::string const	&getNick(void) const;
		std::string const	&getUser(void) const;
		bool				isRegistered(void) const;
		
		void	setNick(std::string const &nick);
		void	setUser(std::string const &user);
		void	setName(std::string const &name);
		void	setPassGiven(bool v);
		
		void	tryRegister(void);
		
};

#endif