/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:18:08 by sinawara          #+#    #+#             */
/*   Updated: 2024/12/13 11:38:29 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Handles the event of only one philosopher present
void	one_philo(t_table *table)
{
	usleep(table->time_to_die * 1000);
	printf("%dms 1 has died\n", table->time_to_die);
	exit(EXIT_SUCCESS);
}

// creates the threads responsible for the handling of the philosophers
// calls philo_routine in a loop to account for all the philos
// when we're done with the simulation we wait for all the threads to terminate
// then we leave and free everything in the main
static int	create_philo_threads(t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_create(&table->philosophers[i], NULL, philo_routine,
				&philo[i]) != 0)
		{
			stop_simulation(table);
			while (--i >= 0)
				pthread_join(table->philosophers[i], NULL);
			return (0);
		}
		usleep(1000);
		i++;
	}
	return (1);
}

// same function as create_philo_threads
static int	create_monitor_thread(t_table *table, pthread_t *monitor,
								t_philo *philo)
{
	int	i;

	if (pthread_create(monitor, NULL, monitor_routine, philo) != 0)
	{
		stop_simulation(table);
		i = 0;
		while (i < table->num_philo)
			pthread_join(table->philosophers[i++], NULL);
		return (0);
	}
	return (1);
}

// Stops the simulation at the end of the main
// Cleans up everything
static void	join_all_threads(t_table *table, pthread_t monitor)
{
	int	i;

	pthread_join(monitor, NULL);
	stop_simulation(table);
	i = 0;
	while (i < table->num_philo)
	{
		pthread_join(table->philosophers[i], NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_table		*table;
	t_philo		*philo;
	pthread_t	monitor;

	validate_inputs(argc, argv);
	table = init_table(argc, argv);
	if (!table)
		exit(EXIT_FAILURE);
	philo = init_philo(table);
	if (!philo)
	{
		cleanup_resources(table, NULL);
		exit(EXIT_FAILURE);
	}
	if (table->num_philo == 1)
		one_philo(table);
	if (!create_philo_threads(table, philo)
		|| !create_monitor_thread(table, &monitor, philo))
	{
		cleanup_resources(table, philo);
		exit(EXIT_FAILURE);
	}
	join_all_threads(table, monitor);
	cleanup_resources(table, philo);
	return (0);
}
