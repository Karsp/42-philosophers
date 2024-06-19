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
// typedef struct timeval	t_time;
typedef struct s_philo	t_philo;

# define NOP 0
# define TTD 1
# define TTE 2
# define TTS 3
# define TME 4 //Times Must Eat

# define FORK "\x1b[1;33mhas taken a fork\x1b[0m"
# define EAT "\x1b[1;32mis eating\x1b[0m"
# define SLEEP "\x1b[1;34mis sleeping\x1b[0m"
# define THINK "\x1b[1;35mis thinking\x1b[0m"
# define DIED "died\x1b[0m"

typedef struct s_data
{
	long			start;
	long			*params;
	t_mutex			*forks;
	t_philo			**philo_list;
	t_mutex			*print_mtx;
	t_mutex			*end_mtx;
	t_mutex			*alt_mtx;
	pthread_attr_t	det_attr;
	long			end;
}	t_data;

typedef struct s_philo
{
	pthread_t	tid;
	int			number;
	long		*params;
	t_mutex		*l_fork;
	t_mutex		*r_fork;
	long		last_meal;
	long		meals;
	t_data		*p_env;
}	t_philo;

//env_init
t_data	*env_init(char **argv);
void	fill_params(t_data **p_env, char **argv);
int		make_forks(t_data **p_env);
int		init_mutex(t_data *p_env);
//time_utils
long	ft_get_time(void);
long	get_currenttime(long start);
void	ft_usleep(long wait);
//philo_init
void	philos_init(t_data **p_env);
void	philos_join(t_data **p_env, t_philo ***philos);
t_philo	*make_philo(t_data ***p_env, int i);
//parse
int		check_args(char **argv);
long	ft_atol(const char *str);
int		ft_isdigit(int c);
//clean_exit
void	ft_perror(char *msg);
void	ft_putstr_fd(char *s, int fd);
void	clean_exit(t_data **p_env);
void	free_mutexdestroy(t_data ***p_env);
void	clean_mtx(t_data **p_env, int m);
//routines
void	*routine(void *arg);
int		check_end(t_philo *philo, int *end);
void	*init_checkers(void *arg);
int		check_death(t_philo **philo);
void	check_meals(t_philo **philo, int *meals);
//actions
int		take_forks(t_philo	**philo);
int		take_forks_three(t_philo	**philo);
void	take_meal(t_philo	**philo);
void	leave_forks(t_philo	**philo);
int		take_nap_think(t_philo	**philo);
//print_utils
void	print_msg(t_philo **philo, char *msg);
void	set_print_end(t_philo *philo, t_data **p_env, int state);

#endif
