/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 11:00:35 by epfennig          #+#    #+#             */
/*   Updated: 2021/06/16 18:27:48 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

unsigned long long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	write_message_lock(int msg, unsigned long long time,
							 int id, t_philo *philo)
{
	(void)time;
	(void)id;
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
	if (msg != 5)
		pthread_mutex_unlock(&philo->data->mprintf);
}

void	*philo_dead(void *phil)
{
	t_philo				*philo;

	philo = (t_philo *)phil;
	while (1)
	{
		if (philo->is_dead == 1)
		{
			pthread_mutex_unlock(philo->lfork);
			pthread_mutex_unlock(philo->rfork);
			pthread_mutex_unlock(&philo->data->died);
			write_message_lock(5, (get_current_time() - philo->data->timeofday),
				philo->id, philo);
			pthread_mutex_lock(&philo->data->mprintf);
			return (NULL);
		}
	}
	return (NULL);
}

void	*launch_philo(void *phil)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)phil;
	philo->die_time = get_current_time();
	while (1)
	{
		if (philo->data->ac == 6 && i >= philo->data->ntepme)
		{
			pthread_mutex_unlock(&philo->data->died);
			break ;
		}
		left_fork(philo);
		right_fork(philo);
		eat(philo);
		ft_sleep(philo);
		i++;
	}
	return ((void *)0);
}

void	main_init_threads(t_data *d)
{
	int			i;
	pthread_t	*isdead;
	pthread_t	*philothread;

	isdead = malloc(sizeof(pthread_t) * d->nbphilo);
	philothread = malloc(sizeof(pthread_t) * d->nbphilo);
	pthread_mutex_lock(&d->died);
	i = 0;
	while (i < d->nbphilo)
	{
		pthread_create(&philothread[i], NULL, &launch_philo, &d->philo[i]);
		usleep(100);
		pthread_create(&isdead[i], NULL, &philo_dead, &d->philo[i]);
		i++;
	}
	pthread_mutex_lock(&d->died);
	pthread_mutex_unlock(&d->died);
	free(isdead);
	free(philothread);
	usleep(100000);
}
