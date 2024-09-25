/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <theo@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:55:54 by thmouty           #+#    #+#             */
/*   Updated: 2024/09/11 14:56:39 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	phil_init(int ac, char **av, t_tools *tools)
{
	tools->forks = NULL;
	tools->phils = NULL;
	if (ac != 5 && ac != 6)
	{
		printf("Nombre d'arguments incorrect\n");
		return (3);
	}
	tools->nb_phil = ft_atoi(av[1]);
	tools->time_to_die = ft_atoi(av[2]);
	tools->time_to_eat = ft_atoi(av[3]);
	tools->time_to_sleep = ft_atoi(av[4]);
	tools->stop = 0;
	if (ac == 6)
		tools->nb_must_eat = ft_atoi(av[5]);
	if (ac == 6 && tools->nb_must_eat <= 0)
		return (2);
	if (ac == 5)
		tools->nb_must_eat = -1;
	if (pthread_mutex_init(&tools->print, NULL) != 0)
		return (1);
	if (tools->nb_phil <= 0 || tools->time_to_die <= 0
		|| tools->time_to_eat <= 0 || tools->time_to_sleep <= 0)
		return (1);
	return (phil_create(tools));
}

int	phil_create(t_tools *tools)
{
	int	i;

	tools->forks = ft_calloc(sizeof(pthread_mutex_t), tools->nb_phil);
	if (!tools->forks)
		return (1);
	i = -1;
	while (++i < tools->nb_phil)
		if (pthread_mutex_init(&tools->forks[i], NULL) != 0)
			return (1);
	tools->phils = ft_calloc(sizeof(t_phil), tools->nb_phil);
	if (!tools->phils)
		return (1);
	i = -1;
	while (++i < tools->nb_phil)
	{
		tools->phils[i].id = i;
		tools->phils[i].eat_count = 0;
		tools->phils[i].last_eat = 0;
		tools->phils[i].tools = tools;
	}
	return (0);
}

void	phil_free(t_tools *tools)
{
	int	i;

	i = 0;
	while (i < tools->nb_phil && tools->forks)
	{
		pthread_mutex_destroy(&tools->forks[i]);
		i++;
	}
	i = 0;
	free(tools->forks);
	free(tools->phils);
	pthread_mutex_destroy(&tools->print);
}

int	ft_usleep(long long time, t_phil *phil)
{
	long long	timee;
	long long	wait;
	long long	tmp;

	wait = get_time() + time;
	tmp = get_time();
	while (tmp < wait)
	{
		timee = tmp - phil->last_eat - phil->tools->time_to_die;
		if (phil->tools->stop)
			return (1);
		else if (timee > 0)
		{
			print_msg(phil, MSG_DEAD, 1);
			return (1);
		}
		usleep(100);
		tmp = get_time();
	}
	return (0);
}

void	*check_dead(void *ptr)
{
	int		i;
	t_tools	*tools;

	tools = (t_tools *)ptr;
	while (!tools->stop)
	{
		i = -1;
		while (++i < tools->nb_phil && !tools->stop)
		{
			if (get_time() - tools->phils[i].last_eat > tools->time_to_die)
			{
				print_msg(tools->phils, MSG_DEAD, 1);
				tools->stop = 1;
			}
			usleep(100);
		}
	}
	return (NULL);
}
