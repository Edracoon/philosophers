/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 15:11:15 by epfennig          #+#    #+#             */
/*   Updated: 2021/06/14 11:33:49 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	check_args(t_data *d)
{
	if (d->ac == 6)
	{
		if (d->ttd > 0 && d->tte > 0 && d->tts > 0 && d->ntepme > 0)
			return (1);
		else
			return (0);
	}
	else
	{
		if (d->ttd > 0 && d->tte > 0 && d->tts > 0)
			return (1);
		else
			return (0);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data			d;
	struct timeval	time;

	if (ac != 5 && ac != 6)
		return (printf("Error\nNumber of arguments\n"));
	d.nbphilo = ft_atoi(av[1]);
	if (d.nbphilo < 2 || d.nbphilo > 1024)
		return (printf("Error\nNumber of philosophers invalid\n"));
	gettimeofday(&time, NULL);
	d.timeofday = time.tv_sec;
	d.ttd = ft_atoi(av[2]);
	d.tte = ft_atoi(av[3]);
	d.tts = ft_atoi(av[4]);
	d.ac = ac;
	if (ac == 6)
		d.ntepme = ft_atoi(av[5]);
	if (!check_args(&d))
		return (printf("Error\nInvalid arguments\n"));
	printf("nb philo = %i \nttd = %llu \ntte = %llu \ntts = %llu \ntimeofday = %llu \n",
		 d.nbphilo, d.ttd, d.tte, d.tts, d.timeofday);
	main_init_threads(&d);
	return (1);
}
