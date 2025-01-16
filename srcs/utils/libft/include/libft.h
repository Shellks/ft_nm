/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:32:19 by acarlott          #+#    #+#             */
/*   Updated: 2025/01/16 18:14:43 by acarlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdint.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>
# include <fcntl.h>
# include <stdarg.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// PRINTF function
int				ft_putchar(char s);
int				ft_putstr(char *str);
int				ft_putnbr_int(int n);
int				ft_print_memory(unsigned long nbr);
int				ft_printf(const char *format, ...);
int				ft_putnbr_unsigned(unsigned int n);
int				ft_check_convert(char str, va_list ap);
int				ft_putnbr_base(unsigned int nbr, char str);
// LIBFT function
char			*ft_itoa(int n);
int				ft_tolower(int c);
int				ft_toupper(int c);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_lstsize(t_list *lst);
long long int	ft_atoi(const char *str);
t_list			*ft_lstlast(t_list *lst);
size_t			ft_strlen(const char *c);
char			*ft_strdup(const char *s);
t_list			*ft_lstnew(void *content);
void			ft_bzero(void *s, size_t n);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
char			*ft_strchr(const char *s, int c);
char			**ft_split(char const *s, char c);
char			*ft_strrchr(const char *s, int c);
void			*ft_calloc(size_t nmemb, size_t size);
void			*ft_memset(void *b, int c, size_t len);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(void *));
void			*ft_memchr(const void *s, int c, size_t n);
void			ft_lstadd_front(t_list **lst, t_list *new);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			*ft_memcpy(void *dst, const void *src, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_substr(char const *s, unsigned int start, size_t len);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), \
				void (*del)(void *));
char			*ft_strnstr(const char *haystack, \
				const char *needle, size_t len);

#endif
