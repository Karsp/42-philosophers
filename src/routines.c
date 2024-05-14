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

int	check_death(t_philo **philo)
{
	long	last_meal;

	pthread_mutex_lock((*philo)->p_env->print_mtx);
	last_meal = (*philo)->last_meal + 8;
	pthread_mutex_unlock((*philo)->p_env->print_mtx);
	if (ft_get_time() >= (last_meal + (*philo)->params[TTD]))
		return (1);
	return (0);
}

void	check_meals(t_philo **philo, int *meals)
{
	pthread_mutex_lock((*philo)->p_env->print_mtx);
	if ((*philo)->params[TME] != -1 && (*philo)->meals >= (*philo)->params[TME])
	{
		*meals = *meals + 1;
	}
	pthread_mutex_unlock((*philo)->p_env->print_mtx);
}

void	*init_checkers(void *arg)
{
	t_philo	*p;
	t_data	*p_env;
	int		i;
	int		meals;

	p_env = (t_data *)arg;
	p = p_env->philo_list[0];
	while (42)
	{
		i = -1;
		meals = 0;
		while (++i < p_env->params[NOP])
		{
			p = p_env->philo_list[i];
			if (check_death(&p))
				return (set_print_end(p, &p_env, 2), NULL);
			check_meals (&p, &meals);
		}
		if (meals == p->params[NOP])
			return (set_print_end(&p[0], &p_env, 1), NULL);
	}
	return (NULL);
}

int	check_end(t_philo *philo, int *end)
{
	pthread_mutex_lock(philo->p_env->print_mtx);
	*end = philo->p_env->end;
	pthread_mutex_unlock(philo->p_env->print_mtx);
	return (*end);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		end;

	philo = (t_philo *)arg;
	if ((philo->number % 2) == 0)
		ft_usleep(150);
	end = 0;
	while (!end)
	{
		if (take_forks(&philo))
			return (NULL);
		if (check_end(philo, &end))
			return (leave_forks(&philo), NULL);
		take_meal(&philo);
		leave_forks(&philo);
		if (take_nap_think(&philo))
			return (NULL);
	}
	return (NULL);
}
