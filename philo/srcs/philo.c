/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:40:38 by pchapuis          #+#    #+#             */
/*   Updated: 2023/05/24 15:17:24 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->rules->start_mutex);
	pthread_mutex_unlock(&philo->rules->start_mutex);
	if (philo->id % 2 == 0)
		usleep(philo->rules->time_to_eat * 1000 / 2);
	while (1)
	{
		if (end(philo) == 1)
			return (0);
		ft_eat(philo);
		if (philo->rules->nb_philo == 1)
			return (0);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (0);
}

static int	launch_simulation(t_rules *rules)
{
	int			i;

	i = 0;
	pthread_mutex_lock(&rules->start_mutex);
	while (i < rules->nb_philo)
	{
		if (pthread_create(&rules->philo[i].thread, NULL,
				(void *)&philo, &rules->philo[i]) != 0)
			return (perror("Failed to create thread"), 1);
		i ++;
	}
	check_end(rules);
	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_join(rules->philo[i].thread, NULL) != 0)
			return (perror("Failed to join thread"), 1);
		i ++;
	}
	return (0);
}

void	mutex_destroy(t_rules *rules)
{
	int	i;

	pthread_mutex_destroy(&rules->writing_mutex);
	pthread_mutex_destroy(&rules->thread_create_mutex);
	pthread_mutex_destroy(&rules->start_mutex);
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_destroy(&rules->philo[i].left_fork_mutex);
		i ++;
	}
}

int	main(int argc, char **argv)
{
	t_rules	*rules;

	if (argc < 5 || argc > 6)
		return (error_input());
	rules = malloc(sizeof(t_rules));
	if (!rules)
		return (1);
	if (initialize_thread(argc, argv, rules) == 1)
		return (1);
	if (launch_simulation(rules) == 1)
		return (1);
	mutex_destroy(rules);
	free(rules->philo);
	free(rules);
	return (0);
}
