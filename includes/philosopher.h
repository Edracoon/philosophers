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

typedef struct	s_philo
{
	pthread_t			thread;
	int					pos;
	int					is_eating;
	int					is_sleeping;
	int					is_thinking;
	int					died;
	unsigned long long	limit;
	unsigned long long	last_eat;
}	t_philo;

typedef struct s_data
{
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
}	t_data;

void	main_init_threads(t_data *d);
int		ft_atoi(const char *str);
void	ft_putnbr_fd(int nb, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);

#endif