/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 11:00:35 by epfennig          #+#    #+#             */
/*   Updated: 2021/06/14 12:16:40 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	*thread_test(void	*d)
{
	t_data	*data = (t_data *)d;
	
	printf("PHILO[%i] = %lu\n", data->n, (unsigned long)data->philo[data->n].thread);
	usleep(100000);
	return ((void *)0);
}

void	main_init_threads(t_data *d)
{
	d->n = 0;
	d->philo = malloc(sizeof(t_philo) * d->nbphilo);
	while (d->n < d->nbphilo)
	{
		pthread_create(&d->philo[d->n].thread, NULL, &thread_test, (void *)d);
		pthread_join(d->philo[d->n].thread, NULL);
		d->n++;
	}
}
