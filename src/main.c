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
	
	if (argc >= 5 && argc <= 6)
	{
		if (check_args(++argv))
			return (ft_perror("Arg error"), 1);
		p_env = env_init(argv);
		philos_init(&p_env);
		// if (p_env->params[TME] != -1)
		// 	check_meals(&p_env);
		usleep(150);
		// sleep(1); // delay a bit to check segfault
		//create a thread for checker?
		init_checkers(&p_env);
	}
	else
		return (ft_perror("Arg error"), 1);
	pthread_exit(0);
	return (0);
}
