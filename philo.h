/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:51:50 by marihovh          #+#    #+#             */
/*   Updated: 2023/12/07 21:31:54 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H
#include <pthread.h>
#include <stdio.h>
#include "./libft/libft.h"
#include <sys/time.h>
#include <pthread.h>
#define	DEAD 0
#define EAT 1
#define SLEEP 2
#define EATING 5

typedef struct	s_philo	t_philo;
typedef struct	s_data t_data;

struct s_philo
{
	t_data			*data;
	int				index;
	int				eat_times;
	long			last_eat;
	int				status;
	int				l_fork; 
	int				r_fork;
};

struct s_data
{
	pthread_t		check;
	int				philo_count;
	int				die;
	int		*times;
	// int				to_die;
	long			start_time;
	pthread_t		*ids;
	t_philo			*philos;
	int				nb;
	pthread_mutex_t	havai;
	pthread_mutex_t	havai1;
	pthread_mutex_t	havai2;
	pthread_mutex_t *forks;
};

int parcing(int argc, char *argv[]);
int init(int argc, char *argv[], t_data *data);
int init_struct(t_data *data);
void acting(long seconds, int index, char *action);
long get_time(void);
int	ft_usleep(useconds_t time, t_philo *philo);
int init_threads(t_data *data);
int i_am_alive(t_philo *philo);
void philo_print(t_philo *philo, char *action);

int trying(t_philo *philo);/////////////

#endif