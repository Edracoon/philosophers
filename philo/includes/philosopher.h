/* ************************************************************************** */
/*	*/
/*	:::	  ::::::::   */
/*   philosopher.h	  :+:	  :+:	:+:   */
/*	+:+ +:+	 +:+	 */
/*   By: epfennig <epfennig@student.42.fr>	  +#+  +:+	   +#+	*/
/*	+#+#+#+#+#+   +#+	   */
/*   Created: 2021/06/13 15:12:00 by epfennig	  #+#	#+#	 */
/*   Updated: 2021/06/14 09:04:25 by epfennig	 ###   ########.fr	   */
/*	*/
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct	s_philo
{
	pthread_t			thread;
	pthread_mutex_t		*lfork;
	pthread_mutex_t		*rfork;

	t_data				*data;
	int					id;
	int					died;
	unsigned long long	die_time;
}	t_philo;

typedef struct s_data
{
	pthread_mutex_t		*forks;
	t_philo				*philo;

	unsigned long long	timeofday;
	unsigned long long	tts;
	unsigned long long	tte;
	unsigned long long	ttd;
	unsigned long long	nme;
	unsigned long long	ntepme;
	int					nbphilo;
	int					ac;
	int					n;
	pthread_mutex_t		dead;
}	t_data;

void				main_init_threads(t_data *d);
int					ft_atoi(const char *str);
unsigned long long	get_current_time();

#endif