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
	(*p_env)->forks =(t_mutex *) malloc((*p_env)->params[NOP] * sizeof(t_mutex));
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

t_data	*env_init(int argc, char **argv)
{
	t_data	*p_env;

	(void)argc;
	p_env = malloc(sizeof(t_data));
	if (!p_env)
		return (ft_perror("Malloc error"), NULL);
	p_env->params = malloc(6 * sizeof(long));
	if (!p_env->params)
		return (ft_perror("Malloc error"), NULL); //free everything?
	fill_params(&p_env, argv);
	p_env->print_mtx = malloc(sizeof(t_mutex));
	if (!p_env->print_mtx)
		return (ft_perror("Malloc error"), NULL); //free everything
	if (pthread_mutex_init(p_env->print_mtx, NULL))
		return (ft_perror("Mutex init error"), NULL); //free everything
	p_env->end_mtx = malloc(sizeof(t_mutex));
	if (!p_env->end_mtx)
		return (ft_perror("Malloc error"), NULL); //free everything
	if (pthread_mutex_init(p_env->end_mtx, NULL))
		return (ft_perror("Mutex init error"), NULL); //free everything
	if (make_forks(&p_env))
		return (ft_perror("Forks init error"), NULL); //free everything
	p_env->start = ft_get_time();
	printf("NOW: %ld\n", p_env->start);
	return (p_env);
}

void	fill_params(t_data **p_env, char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		(*p_env)->params[i] = ft_atol((const char*)argv[i]);
		i++;
	}
	if (i == 5)
		(*p_env)->params[i] = -1;
}
long	get_currenttime(long start)
{
	return (ft_get_time() - start);
}

long	ft_get_time()
{
	// struct t_time	time;
	struct timeval	time;
	long	res;

	gettimeofday(&time, NULL);
	res = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (res);
}
