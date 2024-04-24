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
	// if (check_end(*philo))
	// 	return (1);
    print_msg(philo, "is sleeping");
    ft_usleep((*philo)->params[TTS]);
    print_msg(philo, "is thinking");
	// if (check_end(*philo))
	// 	return (1);
	return (0);
}

void	leave_forks(t_philo	**philo)
{
	pthread_mutex_unlock((* philo)->l_fork);
	print_msg(philo, "has leave a fork");
	pthread_mutex_unlock((* philo)->r_fork);
	print_msg(philo, "has leave a fork");

}

void	take_meal(t_philo	**philo)
{
	print_msg(philo, "is eating");
	ft_usleep((* philo)->params[TTE]);
	(* philo)->meals += 1;
	(* philo)->last_meal = ft_get_time();
}

int	take_forks(t_philo	**philo)
{
	// if (check_end(*philo))
	// 	return (1);
	pthread_mutex_lock((* philo)->l_fork);
	print_msg(philo, "has taken a fork");
	if ((* philo)->params[NOP] == 1)
	{
		print_msg(philo, "died");
		pthread_mutex_lock((* philo)->p_env->end_mtx);
		(* philo)->p_env->end = 1;
		pthread_mutex_unlock((* philo)->p_env->end_mtx);
		return (1);
	}
	pthread_mutex_lock((* philo)->r_fork);
	print_msg(philo, "has taken a fork");
	return (0);
}
