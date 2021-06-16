/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 15:11:15 by epfennig          #+#    #+#             */
/*   Updated: 2021/06/16 18:21:17 by epfennig         ###   ########.fr       */
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

void	init_struct(t_data *d)
{
	int	i;

	i = 0;
	d->forks = malloc(sizeof(pthread_mutex_t) * d->nbphilo);
	d->philo = malloc(sizeof(t_philo) * d->nbphilo);
	while (i < d->nbphilo)
	{
		d->philo[i].id = i + 1;
		d->philo[i].is_dead = 0;
		pthread_mutex_init(&d->forks[i], NULL);
		d->philo[i].data = d;
		i++;
	}
	i = 0;
	while (i < d->nbphilo)
	{
		if (i - 1 < 0)
			d->philo[i].lfork = &d->forks[d->nbphilo - 1];
		else
			d->philo[i].lfork = &d->forks[i - 1];
		d->philo[i].rfork = &d->forks[i];
		i++;
	}
}

int	verif_args_atoi(int ac, char **av, t_data *d)
{
	if (!ft_isdigit(av[1]))
		return (0);
	d->nbphilo = ft_atoi(av[1]);
	if (d->nbphilo < 2 || d->nbphilo > 200)
		return (0);
	d->timeofday = get_current_time();
	if (!ft_isdigit(av[2]) || !ft_isdigit(av[3]) || !ft_isdigit(av[4]))
		return (0);
	d->ttd = ft_atoi(av[2]);
	d->tte = ft_atoi(av[3]);
	d->tts = ft_atoi(av[4]);
	d->ac = ac;
	if (ac == 6 && !ft_isdigit(av[5]))
		return (0);
	if (ac == 6)
		d->ntepme = ft_atoi(av[5]);
	return (1);
}

int	main(int ac, char **av)
{
	t_data			d;

	if (ac != 5 && ac != 6)
		return (printf("Error\nNumber of arguments\n"));
	if (!verif_args_atoi(ac, av, &d))
		return (printf("Error\nArguments invalid\n"));
	if (!check_args(&d))
		return (printf("Error\nInvalid arguments\n"));
	pthread_mutex_init(&d.mprintf, NULL);
	pthread_mutex_init(&d.died, NULL);
	init_struct(&d);
	main_init_threads(&d);
	if (ac == 6)
		printf("Each philosophers ate %i times\n", d.ntepme);
	return (1);
}
