/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 11:00:35 by epfennig          #+#    #+#             */
/*   Updated: 2021/06/16 11:22:30 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

unsigned long long get_current_time()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	write_message_lock(int msg, unsigned long long time, int id, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mprintf);
	if (msg == 1)
		printf("%llu\t%i has taken a fork\n", time, id);
	else if (msg == 2)
		printf("%llu\t%i is eating\n", time, id);
	else if (msg == 3)
		printf("%llu\t%i is sleeping\n", time, id);
	else if (msg == 4)
		printf("%llu\t%i is thinking\n", time, id);
	else if (msg == 5)
		printf("%llu\t%i died\n", time, id);
	pthread_mutex_unlock(&philo->data->mprintf);
}

void	*philo_died(void *phil)
{
	t_philo				*philo;
	unsigned long long	time;

	philo = (t_philo *)phil;
	pthread_mutex_lock(&philo->data->died);
	if (philo->is_dead == 1)
	{
		time = get_current_time();
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(philo->rfork);
		pthread_mutex_unlock(&philo->data->died);
		write_message_lock(5, (time - philo->data->timeofday), philo->id, philo);
		return (NULL);
	}
	return (NULL);
}

void	*launch_philo(void	*phil)
{
	t_philo				*philo;
	pthread_t			check_death;
	unsigned long long	time;
	
	philo = (t_philo *)phil;
	philo->die_time = get_current_time();
	pthread_create(&check_death, NULL, &philo_died, philo);
	while(1)
	{
		pthread_mutex_lock(philo->lfork);
		time = get_current_time();
		if (time - philo->die_time >= philo->data->ttd)
		{
			philo->is_dead = 1;
			// pthread_mutex_unlock(philo->lfork);
			pthread_mutex_unlock(&philo->data->died);
			// write_message_lock(5, (time - philo->data->timeofday), philo->id, philo);
			break ;
		}
		write_message_lock(1, (time - philo->data->timeofday), philo->id, philo);
		pthread_mutex_lock(philo->rfork);
		time = get_current_time();
		if (time - philo->die_time >= philo->data->ttd)
		{
			philo->is_dead = 1;
			// pthread_mutex_unlock(philo->lfork);
			// pthread_mutex_unlock(philo->rfork);
			pthread_mutex_unlock(&philo->data->died);
			// write_message_lock(5, (time - philo->data->timeofday), philo->id, philo);
			break ;
		}
		write_message_lock(1, (time - philo->data->timeofday), philo->id, philo);
		write_message_lock(2, (time - philo->data->timeofday), philo->id, philo);
		usleep(philo->data->tte * 1000);
		time = get_current_time();
		philo->die_time = time;
		write_message_lock(3, (time - philo->data->timeofday), philo->id, philo);
		pthread_mutex_unlock(philo->lfork);
		pthread_mutex_unlock(philo->rfork);
		usleep(philo->data->tts * 1000);
		time = get_current_time();
		if (time - philo->die_time >= philo->data->ttd)
		{
			philo->is_dead = 1;
			//write_message_lock(5, (time - philo->data->timeofday), philo->id, philo);
			pthread_mutex_unlock(&philo->data->died);
			break ;
		}
		write_message_lock(4, (time - philo->data->timeofday), philo->id, philo);
		//printf("%llu\t%i is thinking\n", (time - philo->data->timeofday), philo->id);
	}
	//write_message_lock(5, (time - philo->data->timeofday), philo->id, philo);
	//printf("%llu\t%i died\n", (time - philo->data->timeofday), philo->id);
	return ((void *)0);
}

void	main_init_threads(t_data *d)
{
	int i;

	i = 0;
	while (i < d->nbphilo)
	{
		pthread_create(&d->philo[i].thread, NULL, &launch_philo, (void *)&d->philo[i]);
		usleep(100);
		i++;
	}
	i = 0;
	while (i < d->nbphilo)
	{
		pthread_join(d->philo[i].thread, NULL);
		i++;
	}
	pthread_mutex_lock(&d->died);
	pthread_mutex_unlock(&d->died);
}
