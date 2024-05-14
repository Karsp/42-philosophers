/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <daviles-@student.madrid42.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:09:15 by daviles-          #+#    #+#             */
/*   Updated: 2024/04/17 14:09:17 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

/*@brief Used to return error message and free everything before exit*/
void	ft_perror(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (write (fd, &s[i], 1) == -1)
			return ;
		i++;
	}
}

void	clean_exit(t_data **p_env)
{
	int		i;
	t_philo	*p;

	i = 0;
	while (i < (*p_env)->params[NOP])
	{
		p = (*p_env)->philo_list[i];
		free(p);
		i++;
	}
	free((*p_env)->philo_list);
	free_mutexdestroy(&p_env);
	free((*p_env)->params);
	free ((*p_env));
}

void	free_mutexdestroy(t_data ***p_env)
{
	int	i;

	i = -1;
	while (++i < (**p_env)->params[NOP])
		pthread_mutex_destroy(&(**p_env)->forks[i]);
	free((**p_env)->forks);
	pthread_mutex_destroy((**p_env)->print_mtx);
	free((**p_env)->print_mtx);
	pthread_mutex_destroy((**p_env)->end_mtx);
	free((**p_env)->end_mtx);
}

void	clean_mtx(t_data **p_env, int m)
{
	if (m >= 1)
	{
		pthread_mutex_destroy((*p_env)->print_mtx);
		free((*p_env)->print_mtx);
	}
	if (m >= 2)
	{
		pthread_mutex_destroy((*p_env)->end_mtx);
		free((*p_env)->end_mtx);
	}
	free((*p_env));
}
