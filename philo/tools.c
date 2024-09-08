#include "Philosophers.h"

int	ft_atoi(const char *nptr)
{
	int			i;
	int			sign;
	long long	result;

	result = 0;
	i = 0;
	sign = 1;
	while (((*nptr >= 9 && *nptr <= 13) || *nptr == 32))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -sign;
		nptr++;
	}
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
		result = result * 10 + nptr[i++] - '0';
	if (((i > 10 || result > INT_MAX) && sign == 1) || ((i > 10
				|| result > ((INT_MIN) * -1LL)) && sign == -1))
		return (0);
	return (sign * result);
}

int	phil_init(int ac, char **av, t_tools *tools)
{
	if (ac != 5 && ac != 6)
		return (1);
	tools->nb_phil = ft_atoi(av[1]);
	tools->time_to_die = ft_atoi(av[2]);
	tools->time_to_eat = ft_atoi(av[3]);
	tools->time_to_sleep = ft_atoi(av[4]);
	tools->nb_must_eat = INT_MAX;
	tools->stop = 0;
	if (ac == 6)
		tools->nb_must_eat = ft_atoi(av[5]);
	if (tools->nb_phil <= 0 || tools->time_to_die <= 0
		|| tools->time_to_eat <= 0 || tools->time_to_sleep <= 0)
		return (1);
	if (pthread_mutex_init(&tools->print, NULL) != 0)
		return (1);
	return (phil_create(tools));
}

int	phil_create(t_tools *tools)
{
	int	i;

	tools->forks = malloc(sizeof(pthread_mutex_t) * tools->nb_phil);
	if (!tools->forks)
		return (1);
	i = 0;
	while (i < tools->nb_phil)
	{
		if (pthread_mutex_init(&tools->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	tools->phils = malloc(sizeof(t_phil) * tools->nb_phil);
	if (!tools->phils)
		return (1);
	i = 0;
	while (i < tools->nb_phil)
	{
		tools->phils[i].id = i;
		tools->phils[i].eat_count = 0;
		tools->phils[i].last_eat = 0;
		tools->phils[i].tools = tools;
		tools->phils[i].running = 1;
		i++;
	}
	return (0);
}

void	phil_free(t_tools *tools)
{
	int i;

	i = 0;
	while (i < tools->nb_phil)
	{
		pthread_mutex_destroy(&tools->forks[i]);
		i++;
	}
	i = 0;
	free(tools->forks);
	free(tools->phils);
	pthread_mutex_destroy(&tools->print);
}