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
			if (ft_get_time() >= (p->last_meal + p->params[TTD]))
				return (set_print_end(&p[i], 2), NULL);
			if (p->params[TME] != -1 && p->meals >= p->params[TME])
				meals++;
		}
		if (meals == p->params[TME])
			return (set_print_end(&p[0], 1), NULL);
		usleep(10);
	}
	return (NULL);
}

int	check_end(t_philo *philo)
{
	int	end;

	pthread_mutex_lock(philo->p_env->end_mtx);
	end = philo->p_env->end;
	pthread_mutex_unlock(philo->p_env->end_mtx);
	return (end);
}

void    *routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if ((philo->number % 2) == 0)
		usleep(150);
	while (1)
	{
		if (take_forks(&philo))
			return (NULL);
		// if (check_end(philo))
		// 	break ;
		take_meal(&philo);
		leave_forks(&philo);
		if (take_nap_think(&philo))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
