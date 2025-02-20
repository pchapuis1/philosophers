/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:34:43 by pchapuis          #+#    #+#             */
/*   Updated: 2023/05/24 15:29:55 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_rules	t_rules;

typedef struct s_timeval {
	time_t		tv_sec;
	suseconds_t	tv_usec;
}	t_timeval;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	left_fork_mutex;
	pthread_mutex_t	*right_fork_mutex;
	int				nb_meal;
	long int		time_of_death;
	t_rules			*rules;
}	t_philo;

typedef struct s_rules
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long int		start_time;
	int				end_prog;
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	writing_mutex;
	pthread_mutex_t	thread_create_mutex;
	t_philo			*philo;
}	t_rules;

int			ft_atoi(const char *str);
long int	get_time(long int start_time);
int			initialize_thread(int argc, char **argv, t_rules *rules);

int			error_input(void);
int			error_negative_input(void);
int			error_no_philosophers(void);

void		ft_sleep(t_philo *philo);
void		ft_think(t_philo *philo);
void		ft_eat(t_philo *philo);

void		ft_usleep(t_philo *philo, int time);
void		check_end(t_rules *rules);
int			end(t_philo *philo);
void		ft_print_action(t_philo *philo, char *action);

#endif