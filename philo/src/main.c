/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:18:08 by sinawara          #+#    #+#             */
/*   Updated: 2024/12/10 15:08:38 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
argv[0] = program name
argv[1] = number_of_philosophers
argv[2] = time_to_die
argv[3] = time_to_eat
argv[4] = time_to_sleep
argv[5] = [number_of_times_each_philosopher_must_eat]
*/

void	validate_inputs(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		ft_putendl_fd("Invalid number of arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	if (ft_atoi(argv[1]) < 1)
	{
		ft_putendl_fd("Not enough philosophers\n", 2);
		exit(EXIT_FAILURE);
	}
	if (ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0)
	{
		ft_putendl_fd("Error: Time values cannot be negative", 2);
		exit(EXIT_FAILURE);
	}
	if (argc == 6 && ft_atoi(argv[5]) < 1)
	{
		ft_putendl_fd("Error: Number of times to eat must be positive", 2);
		exit(EXIT_FAILURE);
	}
}

t_table	*init_table(int argc, char **argv)
{
	t_table	*table;
	int		i;

	table = (t_table *)malloc(sizeof(t_table));
	table->philosophers = malloc(sizeof(pthread_t) * ft_atoi(argv[1])); // ft_atoi(argv[1]) = num_philo
	if (!table || !table->philosophers)
		return (NULL);
	pthread_mutex_init(&table->print_mutex, NULL);
	table->simulation_running = 1;
	table->num_philo = ft_atoi(argv[1]);
	table->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	table->num_fork = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->amount_to_eat = ft_atoi(argv[5]);
	else
		table->amount_to_eat = -1;
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	return (table);
}

t_philo	*init_philo(t_table *table, char **argv)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philo)
		return (NULL);
	while (i < ft_atoi(argv[1]))
	{
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].table = table;
		//gettimeofday(&philo[i].last_meal_time, NULL);
		i++;
	}
	return (philo);
}

void *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (philo->table->simulation_running)
    {
        philo_think(philo->id, philo);
        
        if (philo->id % 2 == 0)
        {
			pthread_mutex_lock(&philo->table->forks[philo->id - 1]);
            pthread_mutex_lock(&philo->table->forks[philo->id % philo->table->num_philo]);
        	pthread_mutex_lock(&philo->table->print_mutex);
            printf("%ldms Philo no %d has taken left fork\n", get_timestamp(), philo->id);
			printf("%ldms Philo no %d has taken right fork\n", get_timestamp(), philo->id);
			pthread_mutex_unlock(&philo->table->print_mutex);
		}
        else
        {
			pthread_mutex_lock(&philo->table->forks[philo->id % philo->table->num_philo]);
			pthread_mutex_lock(&philo->table->forks[philo->id - 1]);
			pthread_mutex_lock(&philo->table->print_mutex);
            printf("%ldms Philo no %d has taken right fork\n", get_timestamp(), philo->id);
			printf("%ldms Philo no %d has taken left fork\n", get_timestamp(), philo->id);
			pthread_mutex_unlock(&philo->table->print_mutex);
        }
        
        philo_eat(philo->id, philo->table->time_to_eat, philo);
        philo->meals_eaten++;		
		gettimeofday(&philo->last_meal_time, NULL);

        
        pthread_mutex_unlock(&philo->table->forks[philo->id % philo->table->num_philo]);
        pthread_mutex_unlock(&philo->table->forks[philo->id - 1]);

        philo_sleep(philo->id, philo->table->time_to_sleep, philo);
    }
	return(NULL);
}

int	main(int argc, char **argv)
{
	t_table	*table;
	t_philo *philo;
	pthread_t monitor;
	int	i;
	
	validate_inputs(argc, argv);   // checks if all inputs are correct before proceeding
	table = init_table(argc, argv); // initiates table structre
	if (!table)
		exit(EXIT_FAILURE);
	philo = init_philo(table, argv); // initiate philosophers structure
	if (!philo)
	{
		free(table->philosophers);
		free(table->forks);
		free(table);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_create(&table->philosophers[i], NULL, philo_routine, &philo[i]) != 0) //creates a thread per philosophers
		{
			perror("Failed to create thread, Exiting\n");
			free(philo);
			free(table->philosophers);
			free(table->forks);
			free(table);
			exit(EXIT_FAILURE);
		}
		usleep(1000); // prevents deadlocks by staggering philosophers's start time
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, philo) != 0)
		return (1);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < table->num_philo)
	{
		pthread_detach(table->philosophers[i]);
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(philo);
	free(table->philosophers);
	free(table->forks);
	free(table);
	return (0);
}
