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
		p_env = env_init(argc, argv);
		philos_init(&p_env);
	}
	else
		return (ft_perror("Arg error"), 1);
	return (0);
}
