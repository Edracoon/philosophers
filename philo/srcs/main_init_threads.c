/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 11:00:35 by epfennig          #+#    #+#             */
/*   Updated: 2021/06/14 19:18:09 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

unsigned long long have_day_time()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_usec);
}

void	*launch_philo(void	*phil)
{
	t_philo	*philo;
	unsigned long long	time;
	
	philo = (t_philo *)phil;
	if (philo->lfork && philo->rfork)
	{
		while(1)
		{
			pthread_mutex_lock(philo->lfork);
			time = have_day_time();
			if ((time - philo->data->timeofday) > philo->data->ttd * 1000)
			{
				time = have_day_time();
				printf("%llu %i died\n", (time - philo->data->timeofday) / 1000, philo->id);
				return ((void *)0);
			}
			printf("%llu %i has taken a fork\n", (time - philo->data->timeofday) / 1000, philo->id);
			pthread_mutex_lock(philo->rfork);
			time = have_day_time();
			printf("%llu %i has taken a fork\n", (time - philo->data->timeofday) / 1000, philo->id);
			//printf("time = %llu ttd = %llu\n", (time - philo->data->timeofday), philo->data->ttd * 1000);
			time = have_day_time();
			printf("%llu %i is eating\n", (time - philo->data->timeofday) / 1000, philo->id);
			usleep(philo->data->tte);
			//philo->data->timeofday = time;
			time = have_day_time();
			printf("%llu %i started sleeping\n", (time - philo->data->timeofday) / 1000, philo->id);
			pthread_mutex_unlock(philo->lfork);
			pthread_mutex_unlock(philo->rfork);
			usleep(philo->data->tts);
			time = have_day_time();
			printf("%llu %i is thinking\n", (time - philo->data->timeofday) / 1000, philo->id);
		}
	}
	return ((void *)0);
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
