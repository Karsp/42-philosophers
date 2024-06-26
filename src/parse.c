/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <daviles-@student.madrid42.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 22:27:49 by daviles-          #+#    #+#             */
/*   Updated: 2024/04/16 22:28:25 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

int	check_args(char **argv)
{
	long	nb;
	int		i;
	int		j;

	i = 0;
	while (argv[i])
	{
		j = -1;
		while (argv[i][++j])
			if (!ft_isdigit(argv[i][j]))
				return (1);
		nb = ft_atol((const char *)argv[i]);
		if (nb == '\0' || nb < 0)
			return (1);
		argv++;
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

long	ft_atol(const char *str)
{
	int		c;
	long	r;
	long	s;

	c = 0;
	r = 0;
	s = 1;
	while ((str[c] > 8 && str[c] < 14) || str[c] == 32)
		c++;
	if (str[c] == '+' || str[c] == '-')
	{
		if (str[c] == '-')
			s = -1;
		c++;
	}
	while (str[c] != '\0' && (str[c] >= '0' && str[c] <= '9'))
	{
		r = r * 10 + (str[c] - 48);
		c++;
	}
	return (r * s);
}
