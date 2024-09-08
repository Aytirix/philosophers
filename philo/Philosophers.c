
#include "Philosophers.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_msg(t_phil *phil, char *msg)
{
	pthread_mutex_lock(&phil->tools->print);
	if (phil->tools->stop)
		return ;
	if (msg == msg_dead)
		phil->tools->stop = 1;
	printf(msg, get_time() - phil->tools->start, phil->id + 1);
	pthread_mutex_unlock(&phil->tools->print);
}

void	ft_usleep(long long time, t_phil *phil)
{
	long long timee = get_time() - phil->last_eat;
	while (0 < time)
	{
		if (!phil->tools->stop && timee > phil->tools->time_to_die)
		{
			printf("diff %lld\n", timee);
			print_msg(phil, msg_dead);
			return ;
		}
		usleep(100);
		time -= 100;
	}
}
void	*phil_life(void *ptr)
{
	t_phil	*phil;

	phil = (t_phil *)ptr;
	phil->last_eat = get_time();
	while (!phil->tools->stop)
	{
		print_msg(phil, msg_think);
		ft_usleep(phil->tools->time_to_sleep * 1000, phil);
		if (phil->tools->stop)
			break ;
		pthread_mutex_lock(&phil->tools->forks[phil->id]);
		print_msg(phil, msg_fork);
		pthread_mutex_lock(&phil->tools->forks[(phil->id + 1)
			% phil->tools->nb_phil]);
		print_msg(phil, msg_fork);
		print_msg(phil, msg_eat);
		phil->last_eat = get_time();
		ft_usleep(phil->tools->time_to_eat * 1000, phil);
		phil->eat_count++;
		pthread_mutex_unlock(&phil->tools->forks[phil->id]);
		pthread_mutex_unlock(&phil->tools->forks[(phil->id + 1)
			% phil->tools->nb_phil]);
		if (phil->tools->stop)
			break ;
		print_msg(phil, msg_sleep);
		ft_usleep(phil->tools->time_to_sleep * 1000, phil);
	}
	return (NULL);
}

void	create_threads(t_tools *tools)
{
	int			i;
	pthread_t	death_thread;

	i = 0;
	while (i < tools->nb_phil)
	{
		if (pthread_create(&tools->phils[i].thread, NULL, phil_life,
				&tools->phils[i]) != 0)
		{
			printf("Erreur lors de la création des threads\n");
			return ;
		}
		else
			usleep(25 * 1000);
		i++;
	}
	i = 0;
}

int	main(int ac, char **av)
{
	t_tools	tools;
	int i;

	if (phil_init(ac, av, &tools))
	{
		printf("Erreur lors de l'initialisation des philosophes\n");
		phil_free(&tools);
		return (1);
	}
	tools.start = get_time();
	create_threads(&tools);
	i = 0;
	while (i < tools.nb_phil)
	{
		pthread_join(tools.phils[i].thread, NULL);
		i++;
	}
	phil_free(&tools);
	return (0);
}
