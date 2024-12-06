/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:29:44 by sinawara          #+#    #+#             */
/*   Updated: 2024/12/06 15:42:18 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_sign(int num, int min_count, int max_count)
{
	if (min_count == 1)
		num = -num;
	if ((min_count > 0 && max_count > 0) || min_count > 1 || max_count > 1)
		num = 0;
	return (num);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	min_count;
	int	max_count;
	int	num;

	i = 0;
	min_count = 0;
	max_count = 0;
	num = 0;
	while ((str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) && str[i])
		i++;
	while ((str[i] == '+' || str[i] == '-') && str[i])
	{
		if (str[i] == '-')
			min_count++;
		if (str[i] == '+')
			max_count++;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
		num = (num * 10) + (str[i++] - 48);
	num = ft_sign(num, min_count, max_count);
	return (num);
}


void	ft_putnbr_fd(int n, int fd)
{
	char	nb_char;

	nb_char = n + 48;
	if (n == -2147483648)
	{
		write (fd, "-", 1);
		write (fd, "2", 1);
		ft_putnbr_fd(147483648, fd);
	}
	else if (n < 0)
	{
		write (fd, "-", 1);
		n = -n;
		ft_putnbr_fd(n, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd((n / 10), fd);
		ft_putnbr_fd((n % 10), fd);
	}
	else
		write (fd, &nb_char, 1);
}