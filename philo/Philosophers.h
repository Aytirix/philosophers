/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <theo@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:55:54 by thmouty           #+#    #+#             */
/*   Updated: 2024/09/11 14:56:39 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MSG_FORK 	"%lld %d has taken a fork\n"
# define MSG_EAT 	"%lld %d is eating\n"
# define MSG_SLEEP	"%lld %d is sleeping\n"
# define MSG_THINK	"%lld %d is thinking\n"
# define MSG_DEAD	"%lld %d died\n"

typedef struct s_tools
{
	int				nb_phil;
	long long		start;
	long long		stop;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				nb_must_eat;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	struct s_phil	*phils;
	pthread_t		check;
	pthread_t		check_death;
}					t_tools;

typedef struct s_phil
{
	pthread_t		thread;
	int				id;
	int				eat_count;
	long long		last_eat;
	t_tools			*tools;
}					t_phil;

// Philosophers.c
void				*check_thread(void *ptr);

// mini_lib.c
long long			get_time(void);
int					print_msg(t_phil *phil, char *msg, int dead);
int					ft_atoi(const char *nptr);
void				*ft_calloc(size_t nmemb, size_t size);
int					init_thread(t_tools *tools);

// tools.c
int					phil_init(int ac, char **av, t_tools *tools);
int					phil_create(t_tools *tools);
void				phil_free(t_tools *tools);
int					ft_usleep(long long time, t_phil *phil);
void				*check_dead(void *ptr);

#endif