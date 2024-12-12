/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:13:24 by sinawara          #+#    #+#             */
/*   Updated: 2024/12/12 17:14:33 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	take_forks(t_philo *philo, pthread_mutex_t **first_fork,
						pthread_mutex_t **second_fork)
{
	if (philo->id % 2 == 0)
	{
		*first_fork = &philo->table->forks[philo->id - 1];
		*second_fork = &philo->table->forks[philo->id
			% philo->table->num_philo];
	}
	else
	{
		*first_fork = &philo->table->forks[philo->id
			% philo->table->num_philo];
		*second_fork = &philo->table->forks[philo->id - 1];
	}
	pthread_mutex_lock(*first_fork);
	print_status(philo, "Has taken a fork");
	pthread_mutex_lock(*second_fork);
	print_status(philo, "Has taken a fork");
}

static void	put_down_forks(pthread_mutex_t *first_fork,
							pthread_mutex_t *second_fork)
{
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

static void	eat_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	gettimeofday(&philo->last_meal_time, NULL);
	pthread_mutex_unlock(&philo->meal_mutex);
	print_status(philo, "is eating");
	smart_sleep(philo->table->time_to_eat);
	philo->meals_eaten++;
}

void	*philo_routine(void *arg)
{
	t_philo			*philo;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	philo = (t_philo *)arg;
	while (check_simulation_status(philo->table))
	{
		print_status(philo, "is thinking");
		usleep(1000);
		if (!check_simulation_status(philo->table))
			break ;
		take_forks(philo, &first_fork, &second_fork);
		eat_meal(philo);
		put_down_forks(first_fork, second_fork);
		print_status(philo, "is sleeping");
		smart_sleep(philo->table->time_to_sleep);
	}
	return (NULL);
}
