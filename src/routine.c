/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <daviles-@student.madrid42.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:39:10 by daviles-          #+#    #+#             */
/*   Updated: 2024/04/19 22:39:13 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

void	*ft_check_death(void *arg)
{
	int	end;
	int	i;
	t_philo	*p;
	p = arg;

	while (!p->p_env->end)
	{
		if (get_time() <= (p->last_meal + p->params[TTD]))
			{
			print_msg(&p, " died");
			pthread_mutex_lock(&p->p_env->end_mtx);
			end = p->p_env->end;
			pthread_mutex_unlock(&p->p_env->end_mtx);
		}
		usleep(10);
	}
	return (NULL);
}

int	check_end(t_philo *philo)
{
	int	end;

	pthread_mutex_lock(&philo->p_env->end_mtx);
	end = philo->p_env->end;
	pthread_mutex_unlock(&philo->p_env->end_mtx);
	if (end == 1)
		return (1);
	return (0);
}

void	print_msg(t_philo **philo, char *msg)
{
	int	nop;

	nop = (* philo)->number;
	pthread_mutex_lock(&(* philo)->p_env->print_mtx);
	printf("%ld %d %s \n", get_time(), nop, msg);
	pthread_mutex_unlock(&(* philo)->p_env->print_mtx);

}
void	leave_forks(t_philo	**philo)
{
	pthread_mutex_unlock(&(* philo)->l_fork);
	print_msg(&(*philo), " has leave a fork");
	pthread_mutex_unlock(&(* philo)->r_fork);
	print_msg(&(*philo), "has leave a fork");

}

void	take_meal(t_philo	**philo)
{
	(* philo)->last_meal = get_time();
	print_msg(&(*philo), " is eating");
	while (get_time() <= (* philo)->last_meal + (* philo)->params[TTE])
	{
		usleep(10);
	}
	(* philo)->meals += 1;
	(* philo)->last_meal = get_time();
}

void	take_forks(t_philo	**philo)
{
	pthread_mutex_lock(&(* philo)->l_fork);
	print_msg(&(*philo), " has taken a fork");
	if ((* philo)->number == 1)
	{
		print_msg(&(* philo), " died");
		pthread_mutex_lock(&(* philo)->p_env->end_mtx);
		(* philo)->p_env->end = 1;
		pthread_mutex_unlock(&(* philo)->p_env->end_mtx);
		return ;
	}
	pthread_mutex_lock(&(* philo)->r_fork);
	print_msg(&(*philo), "has taken a fork");

}

void    *routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_time();
	if ((philo->number % 2) == 0)
		usleep(200);
	while (!philo->p_env->end)
	{
		if (check_end(philo))
			break ;
		take_forks(&philo);
		take_meal(&philo);
		leave_forks(&philo);
		// if (check_end(philo))
		// 	return (NULL);

	}
	return (NULL);
}
