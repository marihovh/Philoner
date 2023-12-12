/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:35:58 by marihovh          #+#    #+#             */
/*   Updated: 2023/12/12 21:20:28 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((long long)current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

int	ft_usleep(useconds_t time, t_philo *philo)
{
	u_int64_t	start;

	if (!philo)
		return (1);
	start = get_time();
	while (((get_time() - start) < time) && (trying(philo) != 1)
		&& philo->data->finished != philo->data->philo_count)
		usleep(time / 10);
	return (0);
}

void	exit_philo(t_data *data)
{
	int	i;

	i = -1;
	free(data->times);
	while (++i < data->philo_count)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->ids);
	free(data->forks);
	free(data->philos);
	pthread_mutex_destroy(&data->_eat);
	pthread_mutex_destroy(&data->_die);
	pthread_mutex_destroy(&data->_print);
	pthread_mutex_destroy(&data->_finish);
	pthread_mutex_destroy(&data->_counting);
	pthread_mutex_destroy(&data->_argument);
}

void	one_philo(t_data *data)
{
	printf("0 0 has taken a fork\n");
	ft_usleep(data->times[0], NULL);
	printf("%i 0 died\n", ++data->times[0]);
}

char	*no_zero(char *str)
{
	while (*str == '0' && *str)
		str++;
	return (str);
}
