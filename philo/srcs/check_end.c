/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:25:22 by pchapuis          #+#    #+#             */
/*   Updated: 2023/05/30 13:27:18 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	end(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->writing_mutex);
	if (philo->rules->end_prog == 1)
	{
		pthread_mutex_unlock(&philo->rules->writing_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->rules->writing_mutex);
	return (0);
}

static int	check_death(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_lock(&rules->writing_mutex);
		if (rules->philo[i].time_of_death < get_time(rules->start_time))
		{
			rules->end_prog = 1;
			printf("%ld %d died\n", get_time(rules->start_time), i + 1);
			pthread_mutex_unlock(&rules->writing_mutex);
			return (1);
		}
		pthread_mutex_unlock(&rules->writing_mutex);
		i ++;
	}
	return (0);
}

static int	check_meal(t_rules *rules)
{
	int	i;

	if (rules->must_eat == -1)
		return (0);
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_lock(&rules->writing_mutex);
		if (rules->philo[i].nb_meal < rules->must_eat)
		{
			pthread_mutex_unlock(&rules->writing_mutex);
			return (0);
		}
		pthread_mutex_unlock(&rules->writing_mutex);
		i ++;
	}
	pthread_mutex_lock(&rules->writing_mutex);
	rules->end_prog = 1;
	printf("all philosophers have eat %d meals\n", rules->must_eat);
	pthread_mutex_unlock(&rules->writing_mutex);
	return (1);
}

void	check_end(t_rules *rules)
{
	int	i;

	rules->start_time = get_time(0);
	i = 0;
	while (i < rules->nb_philo)
	{
		rules->philo[i].time_of_death = rules->time_to_die;
		i ++;
	}
	pthread_mutex_unlock(&rules->start_mutex);
	while (1)
	{
		if (check_death(rules) == 1)
			return ;
		if (check_meal(rules) == 1)
			return ;
	}
}
