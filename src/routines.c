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

// void	*check_meals(void *arg)
// {
// 	t_philo	*p;
// 	p = arg;

// 	while (!p->p_env->end)
// 	{
// 		if (ft_get_time() <= (p->last_meal + p->params[TTD]))
// 			{
// 			print_msg(&p, " died");
// 			pthread_mutex_lock(p->p_env->end_mtx);
// 			p->p_env->end = 1;
// 			pthread_mutex_unlock(p->p_env->end_mtx);
// 		}
// 		usleep(10);
// 	}
// 	return (NULL);
// }

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
			// printf("AQUI\n");
			p = p_env->philo_list[i];
			// printf("ME %ld\n", p->last_meal);
			// printf("LM %ld\n", p->last_meal);
			// printf("NOW %ld  DEATH %ld\n", ft_get_time(), (p->last_meal + p->params[TTD]));
			if (ft_get_time() >= (p->last_meal + p->params[TTD]))
			{
				set_print_end(&p[i], 2);
				return (NULL);
			}
			if (p->params[TME] != -1 && p->meals >= p->params[TME])
				meals++;
			// printf("Meals %d\n", meals);
		}
		if (meals == p->params[TME])
		{
			set_print_end(&p[0], 1);
			return (NULL);
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
	// philo->last_meal = ft_get_time();
	if ((philo->number % 2) == 0)
		usleep(100);
	while (1)
	{
		if (take_forks(&philo))
			return (NULL);
		if (check_end(philo))
			break ;
		take_meal(&philo);
		leave_forks(&philo);
		if (take_nap_think(&philo))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
