/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:50:36 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/09/10 12:06:08 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ircserv.h"
#include "includes/Server.hpp"

int	main(int ac, char *av[])
{
	try
	{
		if (ac != 3)
			throw std::length_error("Usage: ./ircserv <port> <password>");
		
		int	port = atoi(av[1]);
		std::string password = av[2];
		
		Server	ircserv(port, password);

		ircserv.run();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	catch (...)
	{
		std::cerr << "Error: Unexpected Error" << std::endl;
		return (1);
	}
	return (0);
}