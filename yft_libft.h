/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_libft.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 17:37:58 by topiana-          #+#    #+#             */
/*   Updated: 2026/02/10 16:19:34 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stddef.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

/* TYPES */

int		ft_isspace(int c);

/* MEMORY OPERATIONS */

void	*ft_memset(void *s, int c, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

/* STRINGS */

/* Should this segfault? */
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
int		ft_strichr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin_free(char *s1, char *s2);
int		ft_strset(const char *str, const char *set);
int		starts_with(char *tocheck, char *tosearch);

/* CONVERSIONS */

int		ft_atoi(const char *nptr);
int		ft_atohexi(const char *nptr);

/* MISCELLANEOUS */
char	**ft_split(char const *s, char c);
void	ft_free_mtx(void **mtx);
char	*get_next_line(int fd);
