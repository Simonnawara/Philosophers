/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:26:40 by sinawara          #+#    #+#             */
/*   Updated: 2024/12/11 15:49:38 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_timestamp(void)
{
	struct timeval			current_time;
	static struct timeval	start_time;
	static int				first_call = 1;
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	long					timestamp;

	if (first_call)
	{
		pthread_mutex_lock(&mutex);
		if (first_call)
		{
			gettimeofday(&start_time, NULL);
			first_call = 0;
		}
		pthread_mutex_unlock(&mutex);
	}
	gettimeofday(&current_time, NULL);
	timestamp = (current_time.tv_sec - start_time.tv_sec) * 1000
		+ (current_time.tv_usec - start_time.tv_usec) / 1000;
	return (timestamp);
}

void	smart_sleep(long duration)
{
	struct timeval	start;
	struct timeval	current;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(100);
		gettimeofday(&current, NULL);
		if (get_time_diff(&current, &start) >= duration)
			break ;
	}
}

long	get_time_diff(struct timeval *t1, struct timeval *t2)
{
	return ((t1->tv_sec - t2->tv_sec) * 1000 + (t1->tv_usec - t2->tv_usec)
		/ 1000);
}
