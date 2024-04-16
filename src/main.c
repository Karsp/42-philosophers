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
#include "include/philo.h"

t_data	*init_env(int argc, char *argv)
{
	t_data	*p_env;

	p_env = (t_data) malloc(sizeof(t_data));
	if (!p_env)
		return (ft_perror("Malloc error"));
	return (p_env);
}

int	check_args(char *argv)
{

}

int main(int argc, char *argv)
{
	t_data	*p_env;
	
	if (argc >= 5 && argc <= 6)
	{
		if (check_args(argv + 1))
			return (ft_perror("Arg error"));
		p_env = init_env(argc, argv);
	}

}
