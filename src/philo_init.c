/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <daviles-@student.madrid42.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 20:14:53 by daviles-          #+#    #+#             */
/*   Updated: 2024/04/19 20:14:55 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

t_philo	*make_philo(t_data ***p_env, int i)
{
	t_philo *philo;
	int		nop;

	nop = (**p_env)->params[NOP];
	philo = malloc (sizeof(t_philo));
	if (!philo)
		return (ft_perror("Malloc error"), NULL);
	philo->number = i + 1;
	philo->l_fork = &(**p_env)->forks[(i + nop -1) % nop];
	philo->r_fork = &(**p_env)->forks[i];
	philo->params = (**p_env)->params;
	philo->p_env = (**p_env);
	philo->last_meal= ft_get_time();
	philo->meals = 0;
	return (philo);
}

void    philos_init(t_data **p_env)
{
	t_philo **philos;
	int     i;
	
	i = 0;
	philos = malloc((*p_env)->params[NOP] * sizeof(t_philo *));
	if (!philos)
		return (ft_perror("Malloc error"));
	pthread_attr_init(&(*p_env)->det_attr);
	pthread_attr_setdetachstate(&(*p_env)->det_attr, PTHREAD_CREATE_DETACHED);
	while (i < (* p_env)->params[NOP])
	{
		philos[i] = make_philo(&p_env, i);
		if (!philos[i])
			return (ft_perror("Malloc error"));
		if (pthread_create(&philos[i]->tid, &(*p_env)->det_attr, &routine, philos[i]))
			return (ft_perror("Thread error"));
		i++;
	}
	(*p_env)->philo_list = philos;

}
