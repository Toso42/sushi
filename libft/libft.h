/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdi-leo <tcorax42@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:49:44 by tdi-leo           #+#    #+#             */
/*   Updated: 2022/12/30 17:01:54 by tdi-leo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void	ft_printftypestring(va_list args, char *ss, int sum);
int		ft_printftypestring_fd(va_list args, char *ss, int sum, int fd);
int		ft_printbits(int bits, int toprint);
int		ft_putchar(char c);
int		ft_putstring(char *astring, int Sum);
int		ft_putnmbu(unsigned int n, int Sum);
int		ft_putnmb(int n, int Sum);
int		ft_putnmbcx(unsigned int n, int Sum, char *base);
int		ft_putnmbx(unsigned int n, int Sum, char *base);
int		ft_putp(unsigned long long int n, int Sum, char *base);
int		ft_pad(unsigned long long int n, int Sum, char *base);
int		type(va_list args, const char *string, int Sum, int x);
int		ft_printf(const char *string, ...);
int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
char	*ft_itoa(int n);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
int		ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_putstr_fd(char *s, int fd);
char	**ft_split(const char *s, char c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
void	ft_striteri(char *s, void (*f) (unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	**ft_saradd_back(char **base, char *toadd);
void	ft_sarfree(char **sar, int y);
int		ft_sarprint(char **sar);
int		ft_sarsize(char **tocount);
char	*ft_strintertrim(char *totrim, char c);
char	*ft_strjoinfree(char *s1, char *s2);
char	*ft_strnstr_precision(const char *haystack, const char *needle, \
				size_t len, char terminator);
int		ft_printd(int flag, const char *string, ...);
char	**ft_sarcopy(char **str);
int		ft_printfd(int fd, const char *string, ...);
int		ft_strcmp(const char *X, const char *Y);
char	**ft_sardel(char **sar, int todel);
int		ft_strcmp_precision(const char *x, const char *y);
char	*ft_char_to_str(char c);
int		ft_atoicheck(char *str);
void	ft_free(char *tofree);

#endif
