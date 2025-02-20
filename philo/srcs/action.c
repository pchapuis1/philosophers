/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:27:17 by pchapuis          #+#    #+#             */
/*   Updated: 2023/05/30 13:28:30 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_philo *philo)
{
	ft_print_action(philo, "is sleeping");
	ft_usleep(philo, philo->rules->time_to_sleep * 1000);
}

void	ft_think(t_philo *philo)
{
	ft_print_action(philo, "is thinking");
}

static void	ft_took_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->left_fork_mutex));
	ft_print_action(philo, "has taken left fork");
	if (philo->rules->nb_philo == 1)
	{
		pthread_mutex_unlock(&(philo->left_fork_mutex));
		return ;
	}
	pthread_mutex_lock(philo->right_fork_mutex);
	ft_print_action(philo, "has taken right fork");
}

void	ft_eat(t_philo *philo)
{
	ft_took_fork(philo);
	if (philo->rules->nb_philo == 1)
		return ;
	ft_print_action(philo, "is eating");
	ft_usleep(philo, philo->rules->time_to_eat * 1000);
	pthread_mutex_lock(&philo->rules->writing_mutex);
	philo->time_of_death = get_time(philo->rules->start_time)
		+ philo->rules->time_to_die;
	philo->nb_meal ++;
	pthread_mutex_unlock(&philo->rules->writing_mutex);
	pthread_mutex_unlock(&(philo->left_fork_mutex));
	pthread_mutex_unlock(philo->right_fork_mutex);
}
