/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifelong.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:43:08 by marihovh          #+#    #+#             */
/*   Updated: 2023/12/14 16:26:00 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	die(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->data->_die);
	philo->data->die = 1;
	pthread_mutex_unlock(&philo->data->_die);
	printf ("%li %i died\n", (get_time() - philo->data->start_time), philo->index);
	i = -1;
	while (++i < philo->data->philo_count)
	{
		if (pthread_join(philo->data->ids[i], NULL))
			return ;
		printf("Thread %d has finished\n", i);
	}
}

int	i_am_alive(t_philo *philo)
{
	int	i;
	int	time;

	i = -1;
	pthread_mutex_lock(&philo->data->_eat);
	time = get_time() - philo->last_eat;
	// printf("aa%i\n", time);
	pthread_mutex_unlock(&philo->data->_eat);
	if (time > philo->data->times[0])
	{
		die(philo);
		return (0);
	}
	else if (philo->data->eat_count != -1)
		return (after_eat(philo));
	return (1);
}

void	philo_print(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->data->_print);
	if (trying(philo) != 1 && (philo->data->finished != philo->data->philo_count))
	{
		printf("%li %i %s\n", (get_time() - philo->data->start_time), philo->index, action);
	}
	pthread_mutex_unlock(&philo->data->_print);
}

int	after_eat(t_philo *philo)
{
	int	count;
	int	i;

	pthread_mutex_lock(&philo->data->_eat);
	count = philo->eat_times;
	pthread_mutex_unlock(&philo->data->_eat);
	pthread_mutex_lock(&philo->data->_finish);
	if (count == philo->data->eat_count && philo->finished != 'y')
	{
		philo->finished = 'y';
		pthread_mutex_lock(&philo->data->_counting);
		philo->data->finished++;
		pthread_mutex_unlock(&philo->data->_counting);
	}
	pthread_mutex_unlock(&philo->data->_finish);
	if (philo->data->finished == philo->data->philo_count)
	{
		i = -1;
		while (++i < philo->data->philo_count)
			if (pthread_join(philo->data->ids[i], NULL))
				return (-1);
		return (0);
	}
	return (1);
}
