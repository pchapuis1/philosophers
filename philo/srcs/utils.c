/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:05:14 by pchapuis          #+#    #+#             */
/*   Updated: 2023/05/24 15:17:10 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(long int start_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000
		+ current_time.tv_usec / 1000 - start_time);
}

void	ft_usleep(t_philo *philo, int time)
{
	long long int	end_time;

	pthread_mutex_lock(&philo->rules->writing_mutex);
	if (philo->rules->end_prog != 1)
	{
		pthread_mutex_unlock(&philo->rules->writing_mutex);
		end_time = get_time(0);
		usleep(time * 0.9);
		while (get_time(0) - end_time < time / 1000)
			usleep (100);
	}
	else
		pthread_mutex_unlock(&philo->rules->writing_mutex);
}

void	ft_print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->rules->writing_mutex);
	if (philo->rules->end_prog != 1)
	{
		printf("%ld %d %s\n",
			get_time(philo->rules->start_time), philo->id, action);
	}
	pthread_mutex_unlock(&philo->rules->writing_mutex);
}
