/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:35:58 by marihovh          #+#    #+#             */
/*   Updated: 2023/12/07 21:43:22 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long get_time(void)
{
	struct timeval current_time;
	
	gettimeofday(&current_time, NULL);
    return ((long long)current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

int	ft_usleep(useconds_t time, t_philo *philo)
{
	u_int64_t	start;
	// pthread_mutex_t another;
	
	// if (pthread_mutex_init(&another, NULL) != 0) {
	// 	perror("Mutex initialization failed");
		// return (1);
	// }
	// pthread_mutex_lock(&another);
	start = get_time();
	while (((get_time() - start) < time ) && (trying(philo) != 1))
	{
		/*philo->data->die != 1*/
		usleep(time / 10);
	}
	return(0);
}