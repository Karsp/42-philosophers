/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <daviles-@student.madrid42.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:13:01 by daviles-          #+#    #+#             */
/*   Updated: 2024/04/20 21:13:04 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

int	take_nap_think(t_philo	**philo)
{
	if (check_end(*philo))
		return (1);
	print_msg(philo, "is sleeping");
	ft_usleep((*philo)->params[TTS]);
	if (check_end(*philo))
		return (1);
	print_msg(philo, "is thinking");
	return (0);
}

void	leave_forks(t_philo	**philo)
{
	pthread_mutex_unlock((*philo)->l_fork);
	pthread_mutex_unlock((*philo)->r_fork);
}

void	take_meal(t_philo	**philo)
{
	print_msg(philo, "is eating");
	(*philo)->last_meal = ft_get_time();
	(*philo)->meals += 1;
	ft_usleep((*philo)->params[TTE]);
}

int	take_forks(t_philo	**philo)
{
	if (check_end(*philo))
		return (1);
	if ((*philo)->params[NOP] == 1)
	{
		print_msg(philo, "has taken a fork");
		return (1);
	}
	if ((*philo)->r_fork > (*philo)->l_fork)
	{
		pthread_mutex_lock((*philo)->r_fork);
		print_msg(philo, "has taken a fork");
		pthread_mutex_lock((*philo)->l_fork);
		print_msg(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock((*philo)->l_fork);
		print_msg(philo, "has taken a fork");
		pthread_mutex_lock((*philo)->r_fork);
		print_msg(philo, "has taken a fork");
	}
	return (0);
}
