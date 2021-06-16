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

typedef struct s_philo
{
	pthread_mutex_t		*lfork;
	pthread_mutex_t		*rfork;
	t_data				*data;
	int					id;
	int					is_dead;
	unsigned long long	die_time;
	int					eating;
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
	int					ntepme;
	int					nbphilo;
	int					ac;
	int					n;
	int					miam;

	pthread_mutex_t		died;
	pthread_mutex_t		mprintf;
}	t_data;

void				main_init_threads(t_data *d);
void				ft_fork(t_philo *philo);
void				eat(t_philo *philo);
void				ft_sleep(t_philo *philo);
unsigned long long	get_current_time(void);
void				write_message_lock(int msg, unsigned long long time,
						int id, t_philo *philo);
int					ft_atoi(const char *str);
int					ft_isdigit(char *c);

#endif