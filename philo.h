/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:51:50 by marihovh          #+#    #+#             */
/*   Updated: 2023/12/12 21:14:48 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include "./libft/libft.h"
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# define DEAD 0
# define EAT 1
# define SLEEP 2
# define EATING 5

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

struct s_philo
{
	t_data			*data;
	int				index;
	int				eat_times;
	long			last_eat;
	int				status;
	char			finished;
	int				l_fork;
	int				r_fork;
};

struct s_data
{
	pthread_t		check;
	int				philo_count;
	int				die;
	int				*times;
	long			start_time;
	pthread_t		*ids;
	t_philo			*philos;
	int				nb;
	int				eat_count;
	int				finished;
	pthread_mutex_t	_eat;
	pthread_mutex_t	_print;
	pthread_mutex_t	_counting;
	pthread_mutex_t	_argument;
	pthread_mutex_t	_die;
	pthread_mutex_t	_finish;
	pthread_mutex_t	*forks;
};

int			parcing(int argc, char *argv[]);
int			init(int argc, char *argv[], t_data *data);
int			init_struct(t_data *data);
void		acting(long seconds, int index, char *action);
long		get_time(void);
int			ft_usleep(useconds_t time, t_philo *philo);
void		die(t_philo *philo);
int			stimulation(t_data *data);
int			i_am_alive(t_philo *philo);
void		philo_print(t_philo *philo, char *action);
int			trying(t_philo *philo);
int			i_am_alive(t_philo *philo);
void		exit_philo(t_data *data);
int			after_eat(t_philo *philo);
void		one_philo(t_data *data);
char		*no_zero(char *str);
long long	ft_long_atoi(const char *str);

#endif