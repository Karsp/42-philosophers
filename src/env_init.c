/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <daviles-@student.madrid42.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 22:32:15 by daviles-          #+#    #+#             */
/*   Updated: 2024/04/16 22:32:19 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

int	make_forks(t_data **p_env)
{
	int	i;

	i = 0;
	(*p_env)->forks = (t_mutex *)
		malloc((*p_env)->params[NOP] * sizeof(t_mutex));
	if (!(*p_env)->forks)
		return (ft_perror("Malloc error"), 1);
	while (i < (*p_env)->params[NOP])
	{
		if (pthread_mutex_init((*p_env)->forks + i, NULL))
			return (ft_perror("Mutex init error"), 2);
		i++;
	}
	return (0);
}

int	init_mutex(t_data *p_env)
{
	p_env->print_mtx = malloc(sizeof(t_mutex));
	if (!p_env->print_mtx)
		return (ft_perror("Malloc error"), free(p_env), 1);
	if (pthread_mutex_init(p_env->print_mtx, NULL))
		return (ft_perror("Mutex init error"), free(p_env), 1);
	p_env->end_mtx = malloc(sizeof(t_mutex));
	if (!p_env->end_mtx)
		return (ft_perror("Malloc error"), free(p_env), 1);
	if (pthread_mutex_init(p_env->end_mtx, NULL))
		return (ft_perror("Mutex init error"), clean_mtx(&p_env, 1), 1);
	p_env->alt_mtx = malloc(sizeof(t_mutex));
	if (!p_env->alt_mtx)
		return (ft_perror("Malloc error"), free(p_env), 1);
	if (pthread_mutex_init(p_env->alt_mtx, NULL))
		return (ft_perror("Mutex init error"), clean_mtx(&p_env, 1), 1);
	return (0);
}

t_data	*env_init(char **argv)
{
	t_data	*p_env;

	p_env = malloc(sizeof(t_data));
	if (!p_env)
		return (ft_perror("Malloc error"), NULL);
	p_env->params = malloc(6 * sizeof(long));
	if (!p_env->params)
		return (ft_perror("Malloc error"), free(p_env), NULL);
	fill_params(&p_env, argv);
	if (init_mutex(&(*p_env)))
		return (ft_perror("Mutex error"), free(p_env), NULL);
	if (make_forks(&p_env))
		return (ft_perror("Forks init error"), clean_mtx(&p_env, 2), NULL);
	p_env->start = ft_get_time();
	return (p_env);
}

void	fill_params(t_data **p_env, char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		(*p_env)->params[i] = ft_atol((const char *)argv[i]);
		i++;
	}
	if (i == 4)
		(*p_env)->params[i] = -1;
}
