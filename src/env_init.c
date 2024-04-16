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

t_data	*init_env(int argc, char *argv)
{
	t_data	*p_env;

	p_env = malloc(sizeof(t_data));
	if (!p_env)
		return (ft_perror("Malloc error"));
	p_env->params = malloc(5 * sizeof(long));
	if (!p_env->params)
		return (ft_perror("Malloc error"));
	fill_params(&p_env, argv);
	p_env->start = get_time();
	return (p_env);
}

long	get_time()
{
	t_time	*time;
	long	res;

	gettimeofday(&time, NULL);
	res = (time->tv_sec * 1000) + (time->tv_usec * 1000);
	return (res);
}
