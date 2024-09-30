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

int	print_msg(t_phil *phil, char *msg, int dead)
{
	pthread_mutex_lock(&phil->tools->print);
	pthread_mutex_lock(&phil->m_stop);
	if (phil->stop)
	{
		pthread_mutex_unlock(&phil->tools->print);
		pthread_mutex_unlock(&phil->m_stop);
		return (1);
	}
	pthread_mutex_unlock(&phil->m_stop);
	printf(msg, get_time() - phil->tools->start, phil->id + 1);
	if (dead)
	{
		update_death(phil->tools);
		pthread_mutex_unlock(&phil->tools->print);
		return (1);
	}
	pthread_mutex_unlock(&phil->tools->print);
	return (0);
}

int	choose_fork(t_phil *phil)
{
	if (pthread_mutex_lock(phil->fork_right) != 0)
		return (1);
	if (phil->fork_left == phil->fork_right
		|| pthread_mutex_lock(phil->fork_left) != 0)
	{
		pthread_mutex_unlock(phil->fork_right);
		return (1);
	}
	return (0);
}

int	my_fork(t_phil *phil)
{
	if (choose_fork(phil))
		return (1);
	print_msg(phil, MSG_EAT, 0);
	pthread_mutex_lock(&phil->m_last_eat);
	phil->last_eat = get_time();
	pthread_mutex_unlock(&phil->m_last_eat);
	if (ft_usleep(phil->tools->time_to_eat, phil))
	{
		pthread_mutex_unlock(phil->fork_left);
		pthread_mutex_unlock(phil->fork_right);
		return (1);
	}
	pthread_mutex_unlock(phil->fork_left);
	pthread_mutex_unlock(phil->fork_right);
	return (0);
}

void	*check_dead(void *ptr)
{
	t_tools		*tools;
	static int	i = -1;

	tools = (t_tools *)ptr;
	while (1 && (usleep(100) || 1))
	{
		if (++i >= tools->nb_phil)
			i = 0;
		pthread_mutex_lock(&tools->phils[i].m_last_eat);
		if (get_time() - tools->phils[i].last_eat > tools->time_to_die)
		{
			print_msg(&tools->phils[i], MSG_DEAD, 1);
			pthread_mutex_unlock(&tools->phils[i].m_last_eat);
			break ;
		}
		pthread_mutex_unlock(&tools->phils[i].m_last_eat);
		pthread_mutex_lock(&tools->phils[i].m_stop);
		if (tools->phils[i].stop)
		{
			pthread_mutex_unlock(&tools->phils[i].m_stop);
			return (NULL);
		}
		pthread_mutex_unlock(&tools->phils[i].m_stop);
	}
	return (update_death(tools));
}

void	*check_thread(void *ptr)
{
	t_tools	*tools;
	int		i;
	int		all_philos_ate;

	tools = (t_tools *)ptr;
	while (1 && (usleep(100) || 1))
	{
		all_philos_ate = 1;
		i = -1;
		while (++i < tools->nb_phil)
		{
			pthread_mutex_lock(&tools->phils[i].m_eat_count);
			if (tools->phils[i].eat_count < tools->nb_must_eat)
				all_philos_ate = 0;
			pthread_mutex_unlock(&tools->phils[i].m_eat_count);
			pthread_mutex_lock(&tools->phils[i].m_stop);
			if (tools->phils[i].stop
				&& pthread_mutex_unlock(&tools->phils[i].m_stop) == 0)
				return (NULL);
			pthread_mutex_unlock(&tools->phils[i].m_stop);
		}
		if (all_philos_ate)
			return (update_death(tools));
	}
	return (NULL);
}
