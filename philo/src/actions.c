/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:46:13 by sinawara          #+#    #+#             */
/*   Updated: 2024/12/11 15:50:29 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void print_status(t_philo *philo, char *status)
{
    if (check_simulation_status(philo->table))
    {
        pthread_mutex_lock(&philo->table->print_mutex);
        printf("%ldms %d %s\n", get_timestamp(), philo->id, status);
        pthread_mutex_unlock(&philo->table->print_mutex);
    }
}

void *monitor_routine(void *arg)
{
    t_philo *philos;
    int i;
    struct timeval current_time;
    long time_since_last_meal;
    int all_ate_enough;

    philos = (t_philo *)arg;
    while (check_simulation_status(philos[0].table))
    {
        i = 0;
        all_ate_enough = 1;
        while (i < philos[0].table->num_philo)
        {
            pthread_mutex_lock(&philos[i].meal_mutex);
            gettimeofday(&current_time, NULL);
            time_since_last_meal = get_time_diff(&current_time, &philos[i].last_meal_time);
            
            if (time_since_last_meal > philos[0].table->time_to_die)
            {
                print_status(&philos[i], "died");
                stop_simulation(philos[0].table);
                pthread_mutex_unlock(&philos[i].meal_mutex);
                return (NULL);
            }
            
            if (philos[0].table->amount_to_eat != -1 && 
                philos[i].meals_eaten < philos[0].table->amount_to_eat)
                all_ate_enough = 0;
                
            pthread_mutex_unlock(&philos[i].meal_mutex);
            i++;
        }
        
        if (philos[0].table->amount_to_eat != -1 && all_ate_enough)
        {
            stop_simulation(philos[0].table);
            return (NULL);
        }
        usleep(1000);
    }
    return (NULL);
}

void cleanup_resources(t_table *table, t_philo *philo)
{
    int i;

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
	int status;

	pthread_mutex_lock(&table->simulation_mutex);
	status = table->simulation_running;
	pthread_mutex_unlock(&table->simulation_mutex);
	return (status);
}

void stop_simulation(t_table *table)
{
	pthread_mutex_lock(&table->simulation_mutex);
	table->simulation_running = 0;
	pthread_mutex_unlock(&table->simulation_mutex);
}
