/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:56:47 by marihovh          #+#    #+#             */
/*   Updated: 2023/12/14 15:55:20 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	data_mutex_init(t_data *data)
{
	if (pthread_mutex_init(&data->_eat, NULL))
	{
		perror("Mutex initialization failed");
		return (1);
	}
	if (pthread_mutex_init(&data->_die, NULL) != 0)
	{
		perror("Mutex initialization failed");
		return (1);
	}
	if (pthread_mutex_init(&data->_print, NULL) != 0)
	{
		perror("Mutex initialization failed");
		return (1);
	}
	if (pthread_mutex_init(&data->_argument, NULL) != 0)
	{
		perror("Mutex initialization failed");
		return (1);
	}
	if (pthread_mutex_init(&data->_counting, NULL) != 0)
	{
		perror("Mutex initialization failed");
		return (1);
	}
	return (0);
}

int	init_idk(t_data *data)
{
	int	i;

	i = -1;
	if (data_mutex_init(data))
		return (1);
	data->die = 0;
	if (init_struct(data))
		return (1);
	while (++i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			perror("Mutex initialization failed");
			return (1);
		}
		usleep(100);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	data = NULL;
	data = malloc(sizeof(t_data));
	if (parcing(argc, argv))
	{
		printf("argument error\n");
		return (1);
	}
	if (init(argc, argv, data))
		return (1);
	if (init_idk(data))
		return (1);
	if (stimulation(data))
		return (1);
	return (0);
}
