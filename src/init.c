/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 19:18:09 by marihovh          #+#    #+#             */
/*   Updated: 2023/12/07 21:40:40 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int trying(t_philo *philo)
{
	int brr;

	pthread_mutex_lock(&philo->data->havai1);
	brr = philo->data->die;
	pthread_mutex_unlock(&philo->data->havai1);

	return(brr);
}

void die(t_philo *philo)
{
	int i;
	pthread_mutex_lock(&philo->data->havai1);
	philo->data->die = 1;
	pthread_mutex_unlock(&philo->data->havai1);
 	pthread_mutex_unlock(&philo->data->havai2);
	printf("%li %i died\n", (get_time() - philo->data->start_time), philo->index);
	i = -1;
	while (++i < philo->data->philo_count)
	{
		if (pthread_join(philo->data->ids[i], NULL))
			return ;
		printf("Thread %d has finished\n", i);
	}
// pthread_mutex_unlock(&philo->data->havai2);
}

int i_am_alive(t_philo *philo)
{
	int i;
	
	i = -1;
	if (philo->eat_times == 0)
	{
		if ((get_time() - philo->data->start_time) > philo->data->times[0])
		{
			die(philo);
			return (0);
		}
	}
	else if ((get_time() - philo->last_eat) > philo->data->times[0])
	{
		die(philo);
		return (0);
	}
	return (1);
}

void init_mutex(pthread_mutex_t *forks, int cnt)
{
	int i = -1;
	forks = malloc(sizeof(pthread_mutex_t) * cnt);
	while (++i < cnt)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0) {
        	perror("Mutex initialization failed");
        	return ;
    	}
	}
}

void philo_print(t_philo *philo, char *action)
{
	pthread_mutex_t another;
	
	if (pthread_mutex_init(&another, NULL) != 0) {
		perror("Mutex initialization failed");
		return ;
	}
	pthread_mutex_lock(&another);
	// if (philo->data->die != 1)
	if(trying(philo) != 1)
	
		printf("%li %i %s\n", (get_time() - philo->data->start_time), philo->index, action);
	pthread_mutex_unlock(&another);
}

void *thread_function(void *philos)
{
	t_philo *philo = (t_philo *)philos;

	if ((philo->index % 2))
		ft_usleep((philo->data->times[1] / 2), philo);
	// while (philo->data->die != 1)
	while(trying(philo) != 1)
	{
		pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
		philo_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
		philo_print(philo, "has taken a fork");
		philo_print(philo, "is eating");
		ft_usleep(philo->data->times[1], philo);
		pthread_mutex_lock(&philo->data->havai);
		philo->eat_times++;
		philo->last_eat = get_time();
		pthread_mutex_unlock(&philo->data->havai);
		pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
		philo_print(philo, "is sleeping");
		ft_usleep(philo->data->times[2], philo);
		philo_print(philo, "is thinking");
		// usleep(1000);
	}
	return (NULL);	
}

int init_struct(t_data *data)
{
	int i;

	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	data->ids = malloc(sizeof(pthread_t) * data->philo_count);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	i= -1;
	while (++i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0) {
        	perror("Mutex initialization failed");
        	return (1);
    	}
		usleep(100);
	}
	i = -1;
	while (++i < data->philo_count)
	{
		data->philos[i].index = i;
		data->philos[i].eat_times = 0;
		data->philos[i].last_eat = get_time();
		data->philos[i].r_fork = i;
		data->philos[i].data = data;
		if (i == 0)
			data->philos[i].l_fork = data->philo_count - 1;
		else
			data->philos[i].l_fork = i - 1;
	}
	return (0);
}

void one_philo(t_data *data)
{
	(void)data;
	printf("died\n");
}

int init_threads(t_data *data)
{
	int i = -1;
	t_philo	*arg;

    data->start_time = get_time();
	if (data->philo_count == 1)
	{
		one_philo(data);
		return (0);
	}
	while (++i < data->philo_count)
	{
		pthread_mutex_lock (&data->havai);
		arg = &data->philos[i];
		pthread_mutex_unlock (&data->havai);
		if (pthread_create(&data->ids[i], NULL, thread_function, (void *)arg) != 0)
        	return (1);
		// usleep(100);
	}
	while (1)
	{
		i = -1;
		while (++i < data->philo_count)
		{
			if (!i_am_alive(&data->philos[i]))
				return (1);
		}
	}
	return (0);
}
