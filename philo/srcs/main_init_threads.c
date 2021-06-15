/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 11:00:35 by epfennig          #+#    #+#             */
/*   Updated: 2021/06/15 10:44:36 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

unsigned long long get_current_time()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	*launch_philo(void	*phil)
{
	t_philo				*philo;
	unsigned long long	time;
	
	philo = (t_philo *)phil;
	philo->die_time = get_current_time();
	while(1)
	{
		pthread_mutex_lock(philo->lfork);
		time = get_current_time();
		if (time - philo->die_time >= philo->data->ttd)
		{
			pthread_mutex_unlock(philo->lfork);
			break ;
		}
		printf("%llu %i has taken a fork\n", (time - philo->data->timeofday), philo->id);
		pthread_mutex_lock(philo->rfork);
		time = get_current_time();
		if (time - philo->die_time >= philo->data->ttd)
		{
			pthread_mutex_unlock(philo->rfork);
			break ;
		}
		printf("%llu %i has taken a fork\n", (time - philo->data->timeofday), philo->id);
		printf("%llu %i is eating\n", (time - philo->data->timeofday), philo->id);
		usleep(philo->data->tte * 1000);
		philo->die_time = time;
		time = get_current_time();
		printf("%llu %i started sleeping\n", (time - philo->data->timeofday), philo->id);
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(philo->rfork);
		usleep(philo->data->tts * 1000);
		time = get_current_time();
		if (time - philo->die_time >= philo->data->ttd)
		{
			break ;
		}
		printf("%llu %i is thinking\n", (time - philo->data->timeofday), philo->id);
	}
	printf("%llu %i died\n", (time - philo->data->timeofday), philo->id);
	return (NULL);
}

void	main_init_threads(t_data *d)
{
	int i;

	i = 0;
	while (i < d->nbphilo)
	{
		pthread_create(&d->philo[i].thread, NULL, &launch_philo, (void *)&d->philo[i]);
		i++;
	}
	i = -1;
	while (++i < d->nbphilo)
		pthread_join(d->philo[i].thread, NULL);
}
