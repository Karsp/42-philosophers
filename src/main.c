/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <daviles-@student.madrid42.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:26:03 by daviles-          #+#    #+#             */
/*   Updated: 2024/04/16 20:26:06 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

int main(int argc, char **argv)
{
	t_data	*p_env;
	pthread_t	checker;

	if (argc >= 5 && argc <= 6)
	{
		if (check_args(++argv))
			return (ft_perror("Arg error"), 1);
		p_env = env_init(argv);
		philos_init(&p_env);
		 usleep(50);
		checker = (pthread_t)malloc (sizeof(pthread_t));
		if (!checker)
			return (ft_perror("Malloc error"), 1);
		if (pthread_create(&checker, NULL, &init_checkers, p_env))
			return (ft_perror("Thread create error"), 2);
		if (pthread_join(checker, NULL))
			return (ft_perror("Thread join error"), 2);
		// clean_exit(&p_env);
		
	}
	else
		return (ft_perror("Arg error"), 1);
	return (0);
}
