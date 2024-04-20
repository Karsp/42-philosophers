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

void	*check_death(void *arg)
{
	t_philo	*p;
	p = arg;

	while (!p->p_env->end)
	{
		if (ft_get_time() <= (p->last_meal + p->params[TTD]))
			{
			print_msg(&p, " died");
			pthread_mutex_lock(p->p_env->end_mtx);
			p->p_env->end = 1;
			pthread_mutex_unlock(p->p_env->end_mtx);
		}
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
	philo->last_meal = ft_get_time();
	if ((philo->number % 2) == 0)
		usleep(20);
	while (!philo->p_env->end)
	{
		// if (check_end(philo))
		// 	break ;
		// printf("TIME: %ld\n", ft_get_time());
		take_forks(&philo);
		take_meal(&philo);
		leave_forks(&philo);
		take_nap(&philo);
		// if (check_end(philo))
		// 	return (NULL);
		// usleep(10);
		// printf("END %ld\n", philo->p_env->end);
	}
	return (NULL);
}
