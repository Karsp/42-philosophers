/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daviles- <daviles-@student.madrid42.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:54:48 by daviles-          #+#    #+#             */
/*   Updated: 2024/04/16 19:59:56 by daviles-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_data
{
	long    start;
	long    *params;
	t_mutex	*forks;
	t_philo **philo_list;
	t_mutex	*print_mtx;
	long	end;
}   t_data;

typedef struct s_philo
{
	pthread_t	tid;
	int			p_number;
	long		*params;
	t_mutex		*l_fork;
	t_mutex		*r_fork;
	long		last_meal;
	long		meal_time;
	t_data		*p_env;
}   t_philo;

#endif
