/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 11:00:35 by epfennig          #+#    #+#             */
/*   Updated: 2021/06/14 16:08:54 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	*launch_philo(void	*data)
{
	t_data	*d;
	
	d = (t_data *)data;
	if (d->philo[d->n].lfork && d->philo[d->n].rfork)
	{
		pthread_mutex_lock(d->philo[d->n].lfork);
		pthread_mutex_lock(d->philo[d->n].rfork);
		d->philo[d->n].is_eating = 1;
	}
	printf("philo[%i] | is_eating[%i] | %lu\n", d->n, d->philo[d->n].is_eating, (unsigned long)d->philo[d->n].thread);
	usleep(100000);
	return ((void *)0);
}

void	main_init_threads(t_data *d)
{
	d->n = 0;
	while (d->n < d->nbphilo)
	{
		pthread_create(&d->philo[d->n].thread, NULL, &launch_philo, (void *)d);
		pthread_join(d->philo[d->n].thread, NULL);
		d->n++;
	}
}
