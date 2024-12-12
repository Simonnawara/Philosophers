/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:46:13 by sinawara          #+#    #+#             */
/*   Updated: 2024/12/12 16:39:09 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_status(t_philo *philo, char *status)
{
	if (check_simulation_status(philo->table))
	{
		pthread_mutex_lock(&philo->table->print_mutex);
		printf("%ldms %d %s\n", get_timestamp(), philo->id, status);
		pthread_mutex_unlock(&philo->table->print_mutex);
	}
}

void	cleanup_resources(t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&philo[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->simulation_mutex);
	free(philo);
	free(table->philosophers);
	free(table->forks);
	free(table);
}

int	check_simulation_status(t_table *table)
{
	int	status;

	pthread_mutex_lock(&table->simulation_mutex);
	status = table->simulation_running;
	pthread_mutex_unlock(&table->simulation_mutex);
	return (status);
}

void	stop_simulation(t_table *table)
{
	pthread_mutex_lock(&table->simulation_mutex);
	table->simulation_running = 0;
	pthread_mutex_unlock(&table->simulation_mutex);
}
