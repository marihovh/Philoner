/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:32:52 by marihovh          #+#    #+#             */
/*   Updated: 2023/12/14 16:23:29 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_len(char **argv, int argc)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (++i < argc)
	{
		len = ft_strlen(no_zero(argv[i]));
		if (len >= 10)
			return (0);
	}
	return (1);
}

int	init(int argc, char *argv[], t_data *data)
{
	data->times = malloc(sizeof(int) * 3);
	data->philo_count = ft_atoi(argv[1]);
	if (data->philo_count > 200)
	{
		printf("Wrong count of philos\n");
		return (1);
	}
	// if (!check_len(argv, argc))
	// {
	// 	ft_putstr_fd("one of the arguments is wrong\n", 2);
	// 	return (1);
	// }
	data->times[0] = ft_atoi(argv[2]);
	data->times[1] = ft_atoi(argv[3]);
	data->times[2] = ft_atoi(argv[4]);
	if (argc == 6)
		data->eat_count = ft_atoi(argv[5]);
	else
		data->eat_count = -1;
	data->finished = 0;
	return (0);
}

int	parcing(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 0;
	if (argc < 5 || argc > 6)
	{
		printf("Usage: :number_of_philosophers time_to_");
		printf("time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]");
		return (1);
	}
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if ((argv[i][j] < '0' || argv[i][j] > '9') && argv[i][j] != '+' && argv[i][j] != ' ')
				return (1);
			if (argv[i][j] == '+' && ((argv[i][j - 1] && argv[i][j - 1] != ' ') || j != 0))
				return (1);
		}
	}
	return (0);
}

int	trying(t_philo *philo)
{
	int	brr;

	pthread_mutex_lock(&philo->data->_die);
	brr = philo->data->die;
	pthread_mutex_unlock(&philo->data->_die);
	return (brr);
}
