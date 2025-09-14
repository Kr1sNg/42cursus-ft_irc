/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:59:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/09/14 22:47:06 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ircserv.h"
#include "../includes/Client.hpp"

Client::Client(int fd): _client_fd(fd), _passGiven(false), _registered(false)
{
	
};

Client::~Client()
{
	
};
		
int	Client::getSocket(void) const
{
	return (_client_fd);
}

std::string const	&Client::getNick(void) const
{
	return (_nick);
}

std::string const	&Client::getUser(void) const
{
	return (_user);
}

bool	Client::isRegistered(void) const
{
	return (_registered);
}
		
void	Client::setNick(std::string const &nick)
{
	_nick = nick;
}

void	Client::setUser(std::string const &user)
{
	_user = user;
};

void	Client::setName(std::string const &name)
{
	_name = name;
}

void	Client::setPassGiven(bool v)
{
	_passGiven = v;
}
		
void	Client::tryRegister(void)
{
	if (_registered || !_passGiven || _nick.empty() || _user.empty())
		return ;
	_registered = true;
	std::string welcome = 
        ":ircserv 001 " + _nick + " :Welcome to the IRC server, " + _nick + "\r\n"
        ":ircserv 002 " + _nick + " :Your host is ircserv\r\n"
        ":ircserv 003 " + _nick + " :This server was created today\r\n"
        ":ircserv 004 " + _nick + " ircserv v1.0 o o\r\n";
	
	send(_client_fd, welcome.c_str(), welcome.size(), 0);
}