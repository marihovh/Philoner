/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:32:52 by marihovh          #+#    #+#             */
/*   Updated: 2023/12/07 20:11:40 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int init(int argc, char *argv[], t_data *data)
{
	// int i = 1;

	data->times = malloc(sizeof(int) * (argc - 2));
	data->philo_count = ft_atoi(argv[1]);
	if (data->philo_count > 200)
	{
		printf("Wrong count of philos\n");
		return (1);
	}
	data->times[0] = ft_atoi(argv[2]); // die
	data->times[1] = ft_atoi(argv[3]); // eat
	data->times[2] = ft_atoi(argv[4]); // sleep
	return (0);
}

int parcing(int argc, char *argv[])
{
	(void)argc;
	int i;
	int j;

	i = 0;
	if (argc < 5 || argc > 6)
	{
		printf("Usage: :number_of_philosophers time_to_ time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]");
		return (1);
	}
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if ((argv[i][j] < '0' || argv[i][j] > '9') && argv[i][j] != '+' && argv[i][j] != ' ')
				return (1);
			if (argv[i][j] == '+' &&( (argv[i][j - 1] && argv[i][j - 1] != ' ') || j != 0))
				return (1);
		}
	}
	return (0);
}
