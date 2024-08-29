/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstupdate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:56:28 by thmouty           #+#    #+#             */
/*   Updated: 2024/04/25 16:56:28 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstupdate(t_list **lst)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = *lst;
	while (lst && tmp)
	{
		tmp->index = i++;
		if (tmp->next)
			tmp->next->prev = tmp;
		tmp = tmp->next;
	}
}
