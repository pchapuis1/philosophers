/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:26:54 by pchapuis          #+#    #+#             */
/*   Updated: 2023/05/05 13:51:31 by pchapuis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_input(void)
{
	write(2, "usage: ./philo [number_of_philosopher] [time_to_die] ", 54);
	write(2, "[time_to_eat] [time_to_sleep] ", 31);
	write(2, "[number_of_times_each_philosopher_must_eat](optional)\n", 55);
	return (1);
}

int	error_negative_input(void)
{
	write(2, "Values can't be negative or superior to 2147483647\n", 51);
	return (1);
}

int	error_no_philosophers(void)
{
	write(2, "There must be at least one philosopher\n", 40);
	return (1);
}
