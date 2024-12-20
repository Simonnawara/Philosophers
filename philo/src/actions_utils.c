/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:39:12 by sinawara          #+#    #+#             */
/*   Updated: 2024/12/13 11:49:08 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Checks if a philo has died by comparing the time since their last meal
// with the maximum time allowed (time_to_die).
// If a philosopher has died, the simulation stops
// and returns 1; otherwise, it returns 0.
static int	check_philo_death(t_philo *philo)
{
	struct timeval	current_time;
	long			time_since_last_meal;

	pthread_mutex_lock(&philo->meal_mutex);
	gettimeofday(&current_time, NULL);
	time_since_last_meal = get_time_diff(&current_time, &philo->last_meal_time);
	if (time_since_last_meal > philo->table->time_to_die)
	{
		print_status(philo, "died");
		stop_simulation(philo->table);
		pthread_mutex_unlock(&philo->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}

// Checks if all philosophers have eaten at least the required number of meals.
// If no such requirement exists (amount_to_eat == -1), this always returns 0.
static int	check_all_ate_enough(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos[0].table->num_philo)
	{
		if (philos[0].table->amount_to_eat != -1
			&& philos[i].meals_eaten < philos[0].table->amount_to_eat)
			return (0);
	}
	return (1);
}

// Monitors the simulation, checks for philo deaths or if all have eaten enough
// If a death happens, or all have eaten sufficiently, it stops the simulation
// It runs in its own thread and exits when the simulation ends.
void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)arg;
	while (check_simulation_status(philos[0].table))
	{
		i = -1;
		while (++i < philos[0].table->num_philo)
		{
			if (check_philo_death(&philos[i]))
				return (NULL);
		}
		if (philos[0].table->amount_to_eat != -1
			&& check_all_ate_enough(philos))
			return (stop_simulation(philos[0].table), NULL);
		usleep(1000);
	}
	return (NULL);
}
