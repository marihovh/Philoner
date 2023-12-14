/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 19:18:09 by marihovh          #+#    #+#             */
/*   Updated: 2023/12/14 16:25:29 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


void *thread_function(void *philos)
{
	t_philo *philo;

	philo = (t_philo *)philos;
	if ((philo->index % 2))
		ft_usleep((philo->data->times[1] / 2), philo);
	while(trying(philo) != 1 && (philo->data->finished != philo->data->philo_count))
	{	
		pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
		philo_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
		philo_print(philo, "has taken a fork");
		philo_print(philo, "is eating");
		ft_usleep(philo->data->times[1], philo);
		pthread_mutex_lock(&philo->data->_eat);
		philo->last_eat = get_time();
		pthread_mutex_unlock(&philo->data->_eat);
		pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
		pthread_mutex_lock(&philo->data->_eat);
		philo->eat_times++;
		pthread_mutex_unlock(&philo->data->_eat);
		philo_print(philo, "is sleeping");
		ft_usleep(philo->data->times[2], philo);
		philo_print(philo, "is thinking");
	}
	return (NULL);
}

int	init_struct(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	data->ids = malloc(sizeof(pthread_t) * data->philo_count);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0) {
        	perror("Mutex initialization failed");
        	return (1);
    	}
	}
	i = -1;
	while (++i < data->philo_count)
	{
		data->philos[i].index = i;
		data->philos[i].eat_times = 0;
		data->philos[i].last_eat = get_time();
		data->philos[i].data = data;
		data->philos[i].finished = 'n';
		data->philos[i].r_fork = i;
		if (i == 0)
			data->philos[i].l_fork = data->philo_count - 1;
		else
			data->philos[i].l_fork = i - 1;
	}
	return (0);
}

void	create_me(t_data *data)
{
	t_philo	*arg;
	int		i;

	i = -1;
	while (++i < data->philo_count)
	{
		pthread_mutex_lock (&data->_argument);
		arg = &data->philos[i];
		pthread_mutex_unlock (&data->_argument);
		if (pthread_create(&data->ids[i], NULL, thread_function, (void *)arg) != 0)
			return ;
	}
}

int stimulation(t_data *data)
{
	int i = -1;

	i = -1;
	data->start_time = get_time();
	if (data->philo_count == 1)
	{
		one_philo(data);
		exit_philo(data);
		return (0);
	}
	create_me(data);
	while (1)
	{
		i = -1;
		while (++i < data->philo_count)
		{
			if (!i_am_alive(&data->philos[i]))
			{
				exit_philo(data);
				return (1);
			}
		}
	}
	return (0);
}
