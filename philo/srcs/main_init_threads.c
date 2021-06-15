/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 11:00:35 by epfennig          #+#    #+#             */
/*   Updated: 2021/06/15 20:40:24 by epfennig         ###   ########.fr       */
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
	pthread_t			philo_alive;
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
			pthread_mutex_unlock(&philo->data->dead);
			break ;
		}
		printf("%llu\t%i has taken a fork\n", (time - philo->data->timeofday), philo->id);
		pthread_mutex_lock(philo->rfork);
		time = get_current_time();
		if (time - philo->die_time >= philo->data->ttd)
		{
			pthread_mutex_unlock(philo->rfork);
			pthread_mutex_unlock(&philo->data->dead);
			break ;
		}
		printf("%llu\t%i has taken a fork\n", (time - philo->data->timeofday), philo->id);
		printf("%llu\t%i is eating\n", (time - philo->data->timeofday), philo->id);
		usleep(philo->data->tte * 1000);
		time = get_current_time();
		philo->die_time = time;
		printf("%llu\t%i is sleeping\n", (time - philo->data->timeofday), philo->id);
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(philo->rfork);
		usleep(philo->data->tts * 1000);
		time = get_current_time();
		if (time - philo->die_time >= philo->data->ttd)
		{
			pthread_mutex_unlock(&philo->data->dead);
			break ;
		}
		printf("%llu\t%i is thinking\n", (time - philo->data->timeofday), philo->id);
	}
	printf("%llu\t%i died\n", (time - philo->data->timeofday), philo->id);
	philo->data->n = 0;
	return ((void *)0);
}

void	main_init_threads(t_data *d)
{
	int i;

	d->philo->data->n = 0;
	i = 0;
	while (i < d->nbphilo)
	{
		if (i % 2)
		{
			pthread_create(&d->philo[i].thread, NULL, &launch_philo, (void *)&d->philo[i]);
			usleep(10);
		}
		i++;
	}
	i = 0;
	while (i < d->nbphilo)
	{
		if (!(i % 2))
			pthread_create(&d->philo[i].thread, NULL, &launch_philo, (void *)&d->philo[i]);
		i++;
	}
	i = -1;
	pthread_mutex_lock(&d->dead);
	pthread_mutex_unlock(&d->dead);
}
