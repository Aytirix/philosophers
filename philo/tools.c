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
	if (pthread_mutex_init(&tools->print, NULL) != 0)
		return (1);
	if (ac != 5 && ac != 6)
	{
		printf("Nombre d'arguments incorrect\n");
		return (3);
	}
	tools->nb_phil = ft_atoi(av[1]);
	tools->time_to_die = ft_atoi(av[2]);
	tools->time_to_eat = ft_atoi(av[3]);
	tools->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		tools->nb_must_eat = ft_atoi(av[5]);
	if (ac == 6 && tools->nb_must_eat <= 0)
		return (2);
	if (ac == 5)
		tools->nb_must_eat = -1;
	if (tools->nb_phil <= 0 || tools->time_to_die <= 0
		|| tools->time_to_eat <= 0 || tools->time_to_sleep <= 0)
		return (1);
	return (phil_create(tools));
}

static int	init_struct_phil(t_tools *tools, int i)
{
	if (pthread_mutex_init(&tools->forks[i], NULL) != 0
		|| pthread_mutex_init(&tools->phils[i].m_eat_count, NULL) != 0
		|| pthread_mutex_init(&tools->phils[i].m_last_eat, NULL) != 0
		|| pthread_mutex_init(&tools->phils[i].m_stop, NULL) != 0)
		return (1);
	tools->phils[i].stop = 0;
	tools->phils[i].id = i;
	tools->phils[i].eat_count = 0;
	tools->phils[i].last_eat = get_time();
	if (i % 2 == 0)
	{
		tools->phils[i].fork_left = &tools->forks[(i + 1) % tools->nb_phil];
		tools->phils[i].fork_right = &tools->forks[i];
	}
	else
	{
		tools->phils[i].fork_left = &tools->forks[i];
		tools->phils[i].fork_right = &tools->forks[(i + 1) % tools->nb_phil];
	}
	tools->phils[i].tools = tools;
	return (0);
}

int	phil_create(t_tools *tools)
{
	int	i;

	tools->forks = ft_calloc(sizeof(pthread_mutex_t), tools->nb_phil);
	if (!tools->forks)
		return (1);
	tools->phils = ft_calloc(sizeof(t_phil), tools->nb_phil);
	if (!tools->phils)
		return (1);
	i = -1;
	while (++i < tools->nb_phil)
		if (init_struct_phil(tools, i))
			return (1);
	return (0);
}

int	init_thread_check(t_tools *tools)
{
	if (tools->nb_must_eat != -1 && pthread_create(&tools->check, NULL,
			check_thread, tools) != 0)
	{
		printf("Erreur lors de la création du thread de vérification\n");
		phil_free(tools);
		return (1);
	}
	if (pthread_create(&tools->check_death, NULL, check_dead, tools) != 0)
	{
		printf("Erreur lors de la création du thread de vérification\n");
		phil_free(tools);
		return (1);
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
		pthread_mutex_destroy(&tools->phils[i].m_eat_count);
		pthread_mutex_destroy(&tools->phils[i].m_last_eat);
		pthread_mutex_destroy(&tools->phils[i].m_stop);
		i++;
	}
	i = 0;
	free(tools->forks);
	free(tools->phils);
	pthread_mutex_destroy(&tools->print);
}
