/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:08:27 by pchapuis          #+#    #+#             */
/*   Updated: 2023/05/24 15:30:19 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_possible(t_rules *rules, char argc)
{
	if (rules->nb_philo <= 0)
		return (2);
	if (rules->nb_philo <= 0 || rules->nb_philo > 2147483647
		|| rules->time_to_die < 0 || rules->time_to_die > 2147483647
		|| rules->time_to_eat < 0 || rules->time_to_eat > 2147483647
		|| rules->time_to_sleep < 0 || rules->time_to_sleep > 2147483647)
		return (0);
	if (argc > 5)
		if (rules->must_eat < 0)
			return (0);
	return (1);
}

static void	init_neighbor(t_rules *rules)
{
	int	i;
	int	id;

	i = 0;
	while (i < rules->nb_philo)
	{
		id = i + 2;
		if (id > rules->nb_philo)
			id = 1;
		rules->philo[i].right_fork_mutex
			= &rules->philo[id - 1].left_fork_mutex;
		i ++;
	}
}

static void	initialize_philosopher(t_rules *rules)
{
	int	i;

	pthread_mutex_init(&rules->writing_mutex, NULL);
	pthread_mutex_init(&rules->start_mutex, NULL);
	pthread_mutex_init(&rules->thread_create_mutex, NULL);
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_init(&rules->philo[i].left_fork_mutex, NULL);
		rules->philo[i].nb_meal = 0;
		rules->philo[i].id = i + 1;
		rules->philo[i].rules = rules;
		i ++;
	}
}

int	initialize_thread(int argc, char **argv, t_rules *rules)
{
	int	status;

	rules->nb_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->must_eat = -1;
	rules->end_prog = 0;
	if (argc > 5)
		rules->must_eat = ft_atoi(argv[5]);
	status = check_possible(rules, argc);
	if (status == 0)
		return (free(rules), error_negative_input());
	if (status == 2)
		return (free(rules), error_no_philosophers());
	rules->philo = malloc(sizeof(t_philo) * rules->nb_philo);
	if (!rules->philo)
		return (free(rules), write(2, "malloc fails\n", 13), 1);
	initialize_philosopher(rules);
	init_neighbor(rules);
	return (0);
}
