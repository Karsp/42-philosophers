/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <daviles-@student.madrid42.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:24:50 by daviles-          #+#    #+#             */
/*   Updated: 2024/04/22 16:24:52 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

void	set_print_end(t_philo **philo, int state)
{
	pthread_mutex_lock((*philo)->p_env->end_mtx);
	(*philo)->p_env->end = 1;
	pthread_mutex_unlock((*philo)->p_env->end_mtx);	
	if (state == 1)
	{
		pthread_mutex_lock((* philo)->p_env->print_mtx);
		printf("%ld ms\tAll have eaten %ld times.\nEnding simulation.\n", get_currenttime((* philo)->p_env->start), (* philo)->params[TME]);
		pthread_mutex_unlock((* philo)->p_env->print_mtx);

	}
	else
		print_msg(philo, " died");
}

void	print_msg(t_philo **philo, char *msg)
{
	int	nop;

	nop = (* philo)->number;
	pthread_mutex_lock((* philo)->p_env->print_mtx);
	printf("%ld ms\t%d %s \n", get_currenttime((* philo)->p_env->start), nop, msg);
	pthread_mutex_unlock((* philo)->p_env->print_mtx);
}