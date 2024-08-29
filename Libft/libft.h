/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:26:58 by thmouty           #+#    #+#             */
/*   Updated: 2024/04/22 10:26:58 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "get_next_line/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>

typedef struct s_list
{
	int				index;
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

// String functions
char	**ft_split(char const *s, char c);
char	**free_all_split(char **tab);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(char *str);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2, int s_free);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);

// Memory functions
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);

// Conversion functions
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);
void	*ft_calloc(size_t nmemb, size_t size);

// Character functions
void	ft_bzero(void *s, size_t n);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int nb);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

// chained list functions
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
t_list	*ft_lstdup_s(t_list *a);
t_list	*ft_lstdup_d(t_list *a);
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
t_list	*ft_lstprev(t_list *lst);
int		ft_lstsize(t_list *lst);
void	ft_lstswap(t_list **a, t_list **b);
void	ft_lstupdate(t_list **lst);

// Output functions
int		ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_putstr_fd(char *s, int fd);

//  Printf
int		ft_printf(const char *str, ...);
int		ft_putnbr_base_fd(long long nb, char *base, int fd);
int		ft_putunbr_base_fd(unsigned long long nb, char *base, int fd);
int		ft_putaddress(unsigned long long address, int fd);

// Math functions
int		ft_power(int nb, int power);
int		ft_abs(int n);

#endif