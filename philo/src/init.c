/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:33:16 by sinawara          #+#    #+#             */
/*   Updated: 2024/12/13 11:39:30 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

static int	allocate_resources(t_table *table, int num_philo)
{
	table->philosophers = malloc(sizeof(pthread_t) * num_philo);
	if (!table->philosophers)
		return (0);
	table->forks = malloc(sizeof(pthread_mutex_t) * num_philo);
	if (!table->forks)
	{
		free(table->philosophers);
		return (0);
	}
	return (1);
}

static void	initialize_table_contents(t_table *table, int argc, char **argv)
{
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->simulation_mutex, NULL);
	gettimeofday(&table->simulation_start_time, NULL);
	table->simulation_running = 1;
	table->num_philo = ft_atoi(argv[1]);
	table->num_fork = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->amount_to_eat = ft_atoi(argv[5]);
	else
		table->amount_to_eat = -1;
}

// Initiates my t_table structure with all the necessary values
t_table	*init_table(int argc, char **argv)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	if (!allocate_resources(table, ft_atoi(argv[1])))
	{
		free(table);
		return (NULL);
	}
	initialize_table_contents(table, argc, argv);
	if (!init_forks(table))
	{
		free(table->philosophers);
		free(table->forks);
		free(table);
		return (NULL);
	}
	return (table);
}

// Initiates my t_philo structure with add the necessary vales
t_philo	*init_philo(t_table *table)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * table->num_philo);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < table->num_philo)
	{
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].table = table;
		gettimeofday(&philo[i].last_meal_time, NULL);
		pthread_mutex_init(&philo[i].meal_mutex, NULL);
		i++;
	}
	return (philo);
}
