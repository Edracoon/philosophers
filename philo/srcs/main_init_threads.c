/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 11:00:35 by epfennig          #+#    #+#             */
/*   Updated: 2021/06/17 11:30:27 by epfennig         ###   ########.fr       */
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
	else if (msg == 6)
		printf("Each philosophers ate %i times\n", philo->data->ntepme);
	if ((msg != 5 && msg != 6))
		pthread_mutex_unlock(&philo->data->mprintf);
}

void	*launch_philo(void *phil)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)phil;
	philo->data->miam = 0;
	philo->die_time = get_current_time();
	while (1)
	{
		ft_fork(philo);
		eat(philo);
		i++;
		if (philo->data->ac == 6 && i == philo->data->ntepme)
		{
			philo->data->miam = 1;
			break ;
		}
		ft_sleep(philo);
	}
	return ((void *)0);
}

void	create_all_threads(pthread_t *isdead, pthread_t *philothread, t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->nbphilo)
	{
		if (i % 2 == 0)
		{
			pthread_create(&philothread[i], NULL, &launch_philo, &d->philo[i]);
			usleep(50);
			pthread_create(&isdead[i], NULL, &philo_dead, &d->philo[i]);
		}
	}
	usleep(100);
	i = -1;
	while (++i < d->nbphilo)
	{
		if ((i % 2 != 0))
		{
			pthread_create(&philothread[i], NULL, &launch_philo, &d->philo[i]);
			usleep(50);
			pthread_create(&isdead[i], NULL, &philo_dead, &d->philo[i]);
		}
	}
}

void	main_init_threads(t_data *d)
{
	pthread_t	*isdead;
	pthread_t	*philothread;

	isdead = malloc(sizeof(pthread_t) * d->nbphilo);
	philothread = malloc(sizeof(pthread_t) * d->nbphilo);
	pthread_mutex_lock(&d->died);
	create_all_threads(isdead, philothread, d);
	pthread_mutex_lock(&d->died);
	pthread_mutex_unlock(&d->died);
	usleep(100);
	free(isdead);
	free(philothread);
}
