/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_lib.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <theo@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:55:54 by thmouty           #+#    #+#             */
/*   Updated: 2024/09/11 14:56:39 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	print_msg(t_phil *phil, char *msg, int dead)
{
	pthread_mutex_lock(&phil->tools->print);
	if (phil->tools->stop)
	{
		pthread_mutex_unlock(&phil->tools->print);
		return (1);
	}
	if (dead)
		phil->tools->stop = 1;
	printf(msg, get_time() - phil->tools->start, phil->id + 1);
	pthread_mutex_unlock(&phil->tools->print);
	return (0);
}

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

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*s;
	size_t	i;

	if (size && nmemb > (size_t)-1 / size)
		return (NULL);
	s = (void *)malloc(size * nmemb);
	if (!s)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
		((char *)s)[i++] = 0;
	return (s);
}

int	init_thread(t_tools *tools)
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
