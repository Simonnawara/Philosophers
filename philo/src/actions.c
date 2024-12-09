/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:46:13 by sinawara          #+#    #+#             */
/*   Updated: 2024/12/09 16:22:24 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void eat(int num_philo)
{
	write(1, "Philo no ", 8);
	ft_putnbr_fd(num_philo, 1);
	write(1, "is eating\n", 10);
}

void think(int num_philo)
{
	write(1, "Philo no ", 8);
	ft_putnbr_fd(num_philo, 1);
	write(1, "is thinking\n", 12);
}

void sleeping(int num_philo)
{
	write(1, "Philo no ", 8);
	ft_putnbr_fd(num_philo, 1);
	write(1, "is sleeping\n", 12);
}

void die(int num_philo)
{
	write(1, "Philo no ", 8);
	ft_putnbr_fd(num_philo, 1);
	write(1, "has died\n", 9);
}

int check_death(t_philo *philo)
{
    struct timeval current_time;
    long time_diff;

    gettimeofday(&current_time, NULL);
    time_diff = (current_time.tv_sec - philo->last_meal_time.tv_sec) * 1000 +
                (current_time.tv_usec - philo->last_meal_time.tv_usec) / 1000;
    
    if (time_diff > philo->table->time_to_die)
    {
        die(philo->id);
        return (1);
    }
    return (0);
}

void *monitor_routine(void *arg)
{
    t_philo *philos;
    int i;
    int all_ate;

    philos = (t_philo *)arg;
    while (1)
    {
        i = 0;
        all_ate = 1;
        while (i < philos->table->num_philo)
        {
            if (check_death(&philos[i]))
                return (NULL);
            if (philos->table->amount_to_eat != -1 &&
                philos[i].meals_eaten < philos->table->amount_to_eat)
                all_ate = 0;
            i++;
        }
        if (philos->table->amount_to_eat != -1 && all_ate)
            return (NULL);
        usleep(1000);
    }
}