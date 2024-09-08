#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define msg_fork "%lld %d has taken a fork\n"
# define msg_eat "%lld %d is eating\n"
# define msg_sleep "%lld %d is sleeping\n"
# define msg_think "%lld %d is thinking\n"
# define msg_dead "%lld %d died\n"

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
}					t_tools;

typedef struct s_phil
{
	pthread_t		thread;
	int				running;
	int				id;
	int				eat_count;
	long long		last_eat;
	t_tools			*tools;
}					t_phil;

// Philosophers.c
void				stop_all_threads(t_tools *tools);
void				*phil_life(void *ptr);

// mini_lib.c
int					ft_atoi(const char *nptr);

// tools.c
int					phil_init(int ac, char **av, t_tools *tools);
int					phil_create(t_tools *tools);
void				phil_free(t_tools *tools);

#endif