/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <theo@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:55:54 by thmouty           #+#    #+#             */
/*   Updated: 2024/09/11 14:56:39 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static int	choose_fork(t_phil *phil)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	if (phil->id == phil->tools->nb_phil - 1 && phil->tools->nb_phil % 2 == 0)
	{
		right_fork = &phil->tools->forks[phil->id];
		left_fork = &phil->tools->forks[(phil->id + 1) % phil->tools->nb_phil];
	}
	else
	{
		right_fork = &phil->tools->forks[(phil->id + 1) % phil->tools->nb_phil];
		left_fork = &phil->tools->forks[phil->id];
	}
	if (pthread_mutex_lock(left_fork) != 0
		|| pthread_mutex_lock(right_fork) != 0)
		return (1);
	return (0);
}

static void	*phil_life(void *ptr)
{
	t_phil	*phil;

	phil = (t_phil *)ptr;
	phil->last_eat = get_time();
	while (!phil->tools->stop)
	{
		print_msg(phil, MSG_THINK, 0);
		if (phil->tools->stop || choose_fork(phil))
			break ;
		print_msg(phil, MSG_EAT, 0);
		phil->last_eat = get_time();
		if (ft_usleep(phil->tools->time_to_eat, phil))
			break ;
		phil->eat_count++;
		pthread_mutex_unlock(&phil->tools->forks[phil->id]);
		pthread_mutex_unlock(&phil->tools->forks[(phil->id + 1)
			% phil->tools->nb_phil]);
		if (phil->tools->stop)
			break ;
		print_msg(phil, MSG_SLEEP, 0);
		if (ft_usleep(phil->tools->time_to_sleep, phil))
			break ;
	}
	return (NULL);
}

void	*check_thread(void *ptr)

{
	t_tools	*tools;
	int		i;

	tools = (t_tools *)ptr;
	while (!tools->stop)
	{
		usleep(100);
		i = 0;
		while (i < tools->nb_phil && !tools->stop)
		{
			if (tools->phils[i].eat_count < tools->nb_must_eat)
				break ;
			i++;
		}
		if (i == tools->nb_phil)
			tools->stop = 1;
	}
	return (NULL);
}

static void	create_threads(t_tools *tools, int tmp)
{
	int	i;

	i = tmp;
	while (i < tools->nb_phil)
	{
		if (pthread_create(&tools->phils[i].thread, NULL, phil_life,
				&tools->phils[i]) != 0)
		{
			printf("Erreur lors de la création des threads\n");
			return ;
		}
		usleep(100);
		i += 2;
	}
	if (tmp == 0)
		create_threads(tools, 1);
}

int	main(int ac, char **av)
{
	t_tools	tools;
	int		i;

	i = phil_init(ac, av, &tools);
	if (i)
	{
		if (i == 1)
			printf("Erreur lors de l'initialisation des philosophes\n");
		phil_free(&tools);
		return (1);
	}
	tools.start = get_time();
	create_threads(&tools, 0);
	init_thread(&tools);
	i = -1;
	while (!tools.stop)
		usleep(10000);
	while (++i < tools.nb_phil)
		pthread_detach(tools.phils[i].thread);
	if (tools.nb_must_eat > 0)
		pthread_join(tools.check, NULL);
	pthread_join(tools.check_death, NULL);
	phil_free(&tools);
	return (0);
}
