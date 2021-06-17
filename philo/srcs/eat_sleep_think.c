/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:06:16 by epfennig          #+#    #+#             */
/*   Updated: 2021/06/17 11:30:06 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	ft_fork(t_philo *philo)
{	
	pthread_mutex_lock(philo->lfork);
	write_message_lock(1, (get_current_time() - philo->data->timeofday),
		philo->id, philo);
	pthread_mutex_lock(philo->rfork);
	write_message_lock(1, (get_current_time() - philo->data->timeofday),
		philo->id, philo);
}

void	eat(t_philo *philo)
{
	philo->eating = 1;
	write_message_lock(2, (get_current_time() - philo->data->timeofday),
		philo->id, philo);
	philo->die_time = get_current_time();
	usleep(philo->data->tte * 1000);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	philo->eating = 0;
}

void	ft_sleep(t_philo *philo)
{
	write_message_lock(3, (get_current_time() - philo->data->timeofday),
		philo->id, philo);
	usleep(philo->data->tts * 1000);
	write_message_lock(4, (get_current_time() - philo->data->timeofday),
		philo->id, philo);
}

void	*philo_dead(void *phil)
{
	t_philo				*philo;

	philo = (t_philo *)phil;
	while (1)
	{
		if ((philo->eating == 0 && get_current_time() - \
			philo->die_time >= philo->data->ttd) || philo->data->miam == 1)
		{
			if (philo->data->miam == 1)
			{
				pthread_mutex_unlock(&philo->data->died);
				write_message_lock(6, (get_current_time() \
					- philo->data->timeofday), philo->id, philo);
				break ;
			}
			write_message_lock(5, (get_current_time() - philo->data->timeofday),
				philo->id, philo);
			pthread_mutex_unlock(&philo->data->died);
			return (NULL);
		}
		usleep(2000);
	}
	return (NULL);
}
