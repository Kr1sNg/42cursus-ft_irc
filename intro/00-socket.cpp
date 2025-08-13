/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00-socket.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 08:53:54 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/08/13 08:56:17 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <stdio.h>

int	main(void)
{
	int	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		perror("socket");
	
	
}