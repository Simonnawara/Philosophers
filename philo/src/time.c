/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:26:40 by sinawara          #+#    #+#             */
/*   Updated: 2024/12/10 13:50:42 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long get_timestamp(void)
{
    struct timeval current_time;
    static struct timeval start_time;
    static int first_call = 1;
    long timestamp;

    if (first_call)
    {
        gettimeofday(&start_time, NULL);
        first_call = 0;
    }
    gettimeofday(&current_time, NULL);
    timestamp = (current_time.tv_sec - start_time.tv_sec) * 1000 +
                (current_time.tv_usec - start_time.tv_usec) / 1000;
    return (timestamp);
}
