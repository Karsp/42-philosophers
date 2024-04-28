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

	void	set_print_end(t_philo *philo, t_data **p_env, int state)
	{
		pthread_mutex_lock((*p_env)->end_mtx);
		(*p_env)->end = 1;
		pthread_mutex_unlock((*p_env)->end_mtx);	
		if (state == 1)
		{
			pthread_mutex_lock((*p_env)->print_mtx);
			printf("%ld ms\tAll have eaten %ld times.\nEnding simulation.\n",
					get_currenttime((*p_env)->start), philo->params[TME]);
			// pthread_mutex_unlock((*p_env)->print_mtx);

		}
		else
		{
			pthread_mutex_lock((*p_env)->print_mtx);
			printf("%ld ms\t%d %s \n", get_currenttime((*p_env)->start), philo->number, "died");
			// pthread_mutex_unlock((*p_env)->print_mtx);
		}
	}

	void	 print_msg(t_philo **philo, char *msg)
	{
		int		nop;
		// int		end;
		long	current_time;

		current_time = get_currenttime((* philo)->p_env->start);
		nop = (* philo)->number;
		// end = 0;
		// pthread_mutex_lock((* philo)->p_env->end_mtx);
		// end = (*philo)->p_env->end;
		// pthread_mutex_unlock((* philo)->p_env->end_mtx);

		pthread_mutex_lock((* philo)->p_env->print_mtx);
		// if (!end)
		printf("%ld ms\t%d %s \n", current_time, nop, msg);
		pthread_mutex_unlock((* philo)->p_env->print_mtx);
	}