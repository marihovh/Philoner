/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:56:47 by marihovh          #+#    #+#             */
/*   Updated: 2023/12/07 21:27:38 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int main(int argc, char *argv[])
{
	t_data *data;

	data = NULL;
	data = malloc(sizeof(t_data));
	if (parcing(argc, argv))
	{
		printf("argument error\n");
		return (1);
	}
	if (init(argc, argv, data))
		return (1);
	if (pthread_mutex_init(&data->havai, NULL) != 0) {
		perror("Mutex initialization failed");
		return (1);
	}
	if (pthread_mutex_init(&data->havai1, NULL) != 0) {
		perror("Mutex initialization failed");
		return (1);
	}
	if (pthread_mutex_init(&data->havai2, NULL) != 0) {
		perror("Mutex initialization failed");
		return (1);
	}
	data->die = 0;
	if (init_struct(data))
		return (1);
	// printf("%i\n", data->times[0]);
	// printf("%i\n", data->times[1]);
	// printf("%i\n", data->times[2]);
	if (init_threads(data))
		return (1);
	return (0);
}