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
	int	end;

	end = 0;
	if (check_end(*philo, &end))
		return (1);
	print_msg(philo, SLEEP);
	ft_usleep((*philo)->params[TTS]);
	if (check_end(*philo, &end))
		return (1);
	print_msg(philo, THINK);
	return (0);
}

void	leave_forks(t_philo	**philo)
{
	pthread_mutex_unlock((*philo)->l_fork);
	pthread_mutex_unlock((*philo)->r_fork);
}

void	take_meal(t_philo	**philo)
{
	print_msg(philo, EAT);
	pthread_mutex_lock((*philo)->p_env->print_mtx);
	(*philo)->last_meal = ft_get_time();
	(*philo)->meals += 1;
	pthread_mutex_unlock((*philo)->p_env->print_mtx);
	ft_usleep((*philo)->params[TTE]);
}

int	take_forks(t_philo	**philo)
{
	if ((*philo)->params[NOP] == 1)
	{
		print_msg(philo, FORK);
		return (1);
	}
	else if ((*philo)->params[NOP] == 3)
	{
		take_forks_three(&(*philo));
		return (0);
	}
	if ((*philo)->number % 2 == 0)
	{
		pthread_mutex_lock((*philo)->r_fork);
		print_msg(philo, FORK);
		pthread_mutex_lock((*philo)->l_fork);
		print_msg(philo, FORK);
	}
	else
	{
		pthread_mutex_lock((*philo)->l_fork);
		print_msg(philo, FORK);
		pthread_mutex_lock((*philo)->r_fork);
		print_msg(philo, FORK);
	}
	return (0);
}

int	take_forks_three(t_philo	**philo)
{
	if ((*philo)->number % 2 == 0)
	{
		pthread_mutex_lock((*philo)->p_env->alt_mtx);
		pthread_mutex_lock((*philo)->r_fork);
		print_msg(philo, FORK);
		pthread_mutex_lock((*philo)->l_fork);
		pthread_mutex_unlock((*philo)->p_env->alt_mtx);
		print_msg(philo, FORK);
	}
	else
	{
		pthread_mutex_lock((*philo)->p_env->alt_mtx);
		pthread_mutex_lock((*philo)->l_fork);
		print_msg(philo, FORK);
		pthread_mutex_lock((*philo)->r_fork);
		pthread_mutex_unlock((*philo)->p_env->alt_mtx);
		print_msg(philo, FORK);
	}
	return (0);
}
