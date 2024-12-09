/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:46:13 by sinawara          #+#    #+#             */
/*   Updated: 2024/12/09 11:30:08 by sinawara         ###   ########.fr       */
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

void waiting(int time)
{
	usleep(time);
}
