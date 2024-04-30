/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <daviles-@student.madrid42.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:52:20 by daviles-          #+#    #+#             */
/*   Updated: 2024/04/22 12:52:23 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

long	get_currenttime(long start)
{
	return (ft_get_time() - start);
}

void	ft_usleep(long wait)
{
	long	start;

	start = ft_get_time();
	while (42)
	{
		if (ft_get_time() - start > wait)
			break ;
		usleep(40);
	}
}

long	ft_get_time(void)
{
	struct timeval	time;
	long			res;

	gettimeofday(&time, NULL);
	res = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (res);
}
