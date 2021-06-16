/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:06:16 by epfennig          #+#    #+#             */
/*   Updated: 2021/06/16 17:06:39 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	right_fork(t_philo *philo)
{	
	pthread_mutex_lock(philo->rfork);
	if (get_current_time() - philo->die_time >= philo->data->ttd)
	{
		philo->is_dead = 1;
		pthread_mutex_unlock(&philo->data->died);
	}
	write_message_lock(1, (get_current_time() - philo->data->timeofday),
		philo->id, philo);
}

void	left_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	if (get_current_time() - philo->die_time >= philo->data->ttd)
	{
		philo->is_dead = 1;
		pthread_mutex_unlock(&philo->data->died);
	}
	write_message_lock(1, (get_current_time() - philo->data->timeofday),
		philo->id, philo);
}

void	eat(t_philo *philo)
{
	write_message_lock(2, (get_current_time() - philo->data->timeofday),
		philo->id, philo);
	usleep(philo->data->tte * 1000);
	philo->die_time = get_current_time();
	write_message_lock(3, (get_current_time() - philo->data->timeofday),
		philo->id, philo);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}

void	ft_sleep(t_philo *philo)
{
	usleep(philo->data->tts * 1000);
	if (get_current_time() - philo->die_time >= philo->data->ttd)
	{
		philo->is_dead = 1;
		pthread_mutex_unlock(&philo->data->died);
	}
	write_message_lock(4, (get_current_time() - philo->data->timeofday),
		philo->id, philo);
}
