/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup.c                                        :+:      :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: thmouty <thmouty@student.42.fr>             +#+  +:+      +#+        */
/*                                                 +#+#+#+#+#+  +#+           */
/*   Created: 2024/04/25 16:56:28 by thmouty           #+#    #+#             */
/*   Updated: 2024/04/25 16:56:28 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstdup_s(t_list *a)
{
	t_list	*new;
	t_list	*temp;
	char	*content;

	new = NULL;
	while (a)
	{
		content = ft_strdup(a->content);
		if (!content)
			return (ft_lstclear(&new, free), NULL);
		temp = ft_lstnew(content);
		if (!temp)
		{
			free(content);
			ft_lstclear(&new, free);
			return (NULL);
		}
		ft_lstadd_back(&new, temp);
		a = a->next;
	}
	return (new);
}

t_list	*ft_lstdup_d(t_list *a)
{
	t_list	*new;
	t_list	*temp;
	int		*content_int;

	new = NULL;
	while (a)
	{
		content_int = malloc(sizeof(int));
		if (!content_int)
		{
			ft_lstclear(&new, free);
			return (NULL);
		}
		*content_int = *((int *)a->content);
		temp = ft_lstnew(content_int);
		if (!temp)
		{
			free(content_int);
			ft_lstclear(&new, free);
			return (NULL);
		}
		ft_lstadd_back(&new, temp);
		a = a->next;
	}
	return (new);
}
