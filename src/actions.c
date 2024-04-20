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

void	print_msg(t_philo **philo, char *msg)
{
	int	nop;

	nop = (* philo)->number;
	pthread_mutex_lock((* philo)->p_env->print_mtx);
	printf("%ld ms\t%d %s \n", get_currenttime((* philo)->p_env->start), nop, msg);
	pthread_mutex_unlock((* philo)->p_env->print_mtx);

}
void	take_nap(t_philo	**philo)
{
    print_msg(&(*philo), " is sleeping");
    usleep((* philo)->params[TTS]);
}

void	leave_forks(t_philo	**philo)
{
	pthread_mutex_unlock((* philo)->l_fork);
	print_msg(&(*philo), " has leave a fork");
	pthread_mutex_unlock((* philo)->r_fork);
	print_msg(&(*philo), "has leave a fork");

}

void	take_meal(t_philo	**philo)
{
    int i = 0;
	// (* philo)->last_meal = ft_get_time();
	print_msg(&(*philo), " is eating");
    while (ft_get_time() <= ((* philo)->last_meal + (* philo)->params[TTE]))
	{
        printf("I %d\n", ++i);
        printf("GET TIME %ld\n",ft_get_time());
        printf("Current TIME %ld\n",get_currenttime((* philo)->p_env->start));
	    printf("%ld endtime\n", ((* philo)->last_meal + (* philo)->params[TTE]));

		// usleep(10);
	}
    
    printf("AQUI\n");
	(* philo)->meals += 1;
	(* philo)->last_meal = ft_get_time();
}

void	take_forks(t_philo	**philo)
{
	pthread_mutex_lock((* philo)->l_fork);
	print_msg(&(*philo), " has taken a fork");
	if ((* philo)->params[NOP] == 1)
	{
		print_msg(&(* philo), " died");
		pthread_mutex_lock((* philo)->p_env->end_mtx);
		(* philo)->p_env->end = 1;
		pthread_mutex_unlock((* philo)->p_env->end_mtx);
		return ;
	}
	pthread_mutex_lock((* philo)->r_fork);
	print_msg(&(*philo), "has taken a fork");

}
