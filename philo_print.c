/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odib <odib@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:16:15 by odib              #+#    #+#             */
/*   Updated: 2024/09/12 10:44:16 by odib             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_sim_info(t_philosopher *philo, char action)
{
	size_t	current;
	size_t	time_spent;

	current = current_time();
	time_spent = current - philo->sim_info->simulation_start;
	pthread_mutex_lock(&philo->sim_info->print_lock);
	if (action == 'F')
		printf(FORK_LOG, time_spent, philo->id);
	else if (action == 'E')
		printf(FORK_LOG FORK_LOG EAT_LOG, time_spent, \
					philo->id, time_spent, philo->id, \
					time_spent, philo->id);
	else if (action == 'S')
		printf(SLEEP_LOG, time_spent, philo->id);
	else if (action == 'D')
		printf(DEATH_LOG, time_spent, philo->id);
	else if (action == 'T')
		printf(THINK_LOG, time_spent, philo->id);
	pthread_mutex_unlock(&philo->sim_info->print_lock);
	return (current);
}
