/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_libft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 17:37:58 by topiana-          #+#    #+#             */
/*   Updated: 2026/02/07 17:53:55 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "yft_libft.h"

/* TYPES */

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

/* MEMORY OPERATIONS */

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_c;

	s_c = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		s_c[i] = c;
		i++;
	}
	return (s);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_c;
	unsigned char	*src_c;

	if (!n)
		return (dest);
	dest_c = (unsigned char *)dest;
	src_c = (unsigned char *)src;
	if (dest_c > src_c)
	{
		while (n--)
			dest_c[n] = src_c[n];
	}
	else if (dest_c < src_c)
	{
		while (n--)
			*dest_c++ = *src_c++;
	}
	return (dest);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if (!(nmemb && size) || nmemb > SIZE_MAX / size)
	{
		nmemb = 1;
		size = 1;
	}
	mem = malloc(nmemb * size);
	if (mem == NULL)
		return (mem);
	else
		ft_bzero(mem, nmemb * size);
	return (mem);
}

/* STRINGS */

/* Should this segfault? */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	c = (unsigned char)c;
	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	if (s[i] == '\0' && c != '\0')
		return (NULL);
	return ((char *)(s + i));
}

/*check for the value 'c' in the string 's',
if found returns the pos (index + 1) of the first instance of 'c'*/
int	ft_strichr(const char *s, int c)
{
	unsigned int	i;

	c = (unsigned char)c;
	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	if (s[i] == '\0' && c != '\0')
		return (0);
	return (i + 1);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	j = 0;
	while (big[i] != '\0' && i < len)
	{
		if (little[j] == '\0')
			break ;
		j = 0;
		while (little[j] && big[i + j] == little[j])
			j++;
		i++;
	}
	if (little[j] == '\0' && (i + j - 1) <= len)
		return ((char *)(big + i - 1));
	return (NULL);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	len;
	unsigned int	i;

	len = ft_strlen(src);
	if (size > 0)
	{
		i = 0;
		while (src[i] != '\0' && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t			d_len;
	size_t			s_len;
	unsigned int	d;
	unsigned int	s;

	s_len = ft_strlen(src);
	d_len = ft_strlen(dst);
	if (size <= d_len)
		return (size + s_len);
	d = d_len;
	s = 0;
	while (src[s] && d + 1 < size)
	{
		dst[d] = src[s];
		d++;
		s++;
	}
	dst[d] = '\0';
	return (s_len + d_len);
}

/*if the third argument is set to '-1' size_t overflows
(taking the full string)*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	size;

	if (start >= ft_strlen(s))
		return ((char *)ft_calloc(1, sizeof(char)));
	else if ((start + len) < ft_strlen(s))
		size = len + 1;
	else
		size = (ft_strlen(s) - start) + 1;
	sub = (char *)ft_calloc(size, sizeof(char));
	if (!sub)
		return (NULL);
	if (start < ft_strlen(s))
		ft_strlcpy(sub, &s[start], size);
	return (sub);
}

/* like ft_strjoin, but with protections over
strlcat and strlcpy, and of course with a free on s1.
intended use: line = ft_strjoin_free(line, new_line). */
char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*twelve;
	size_t	size;

	size = 1;
	if (s1 != NULL)
		size += ft_strlen(s1);
	if (s2 != NULL)
		size += ft_strlen(s2);
	twelve = (char *)ft_calloc(size, sizeof(char));
	if (twelve == NULL)
		return (NULL);
	if (s1 != NULL)
		ft_strlcpy(twelve, s1, size);
	if (s2 != NULL)
		ft_strlcat(twelve, s2, size);
	free(s1);
	return (twelve);
}

/* CONVERSIONS */

int	ft_atoi(const char *nptr)
{
	int				sign;
	int				nb;
	unsigned char	*nptr_c;

	nptr_c = (unsigned char *)nptr;
	while (ft_strchr(" \f\n\r\t\v", (char)*nptr_c) && *nptr_c)
		nptr_c++;
	sign = 1;
	if (*nptr_c == '-')
	{
		sign = -1;
		nptr_c++;
	}
	else if (*nptr_c == '+')
		nptr_c++;
	nb = 0;
	while (*nptr_c >= '0' && *nptr_c <= '9')
	{
		nb = nb * 10 + (*nptr_c - '0');
		nptr_c++;
	}
	return (nb * sign);
}

/* converts a string into an int.
Skips all the blank spaces, then if the number starts with '0x'
then is treated as an hexadecimal number, if it isn't is treated as
a decimal number (ft_atoi(3)).
RETURNS: the number (int) obtained. */
int	ft_atohexi(const char *nptr)
{
	int			nb;
	const char	base[] = "0123456789abcdef";

	if (nptr == NULL)
		return (0);
	while (ft_strchr(" \f\n\r\t\v", (char)*nptr) && *nptr)
		nptr++;
	if (ft_strncmp("0x", nptr, 2) != 0)
		return (ft_atoi(nptr));
	nptr += 2;
	nb = 0;
	while ((*nptr >= '0' && *nptr <= '9')
		|| (*nptr >= 'a' && *nptr <= 'f'))
	{
		nb = nb * 16 + (ft_strichr(base, *nptr) - 1);
		nptr++;
	}
	return (nb);
}


/* ------------------- GET NEXT LINE ------------------- */

typedef struct s_list_fd
{
	int					fd;
	char				*content;
	struct s_list_fd	*next;
}			t_list_fd;

/*A fusion of ft_lstnew and ft_lstadd_back that returns
	NULL if the mallocation goes wrong,
	a pointer to the new element added if everything goes well.*/
static t_list_fd	*ft_lstnew_add_back_ptr(int fd, t_list_fd *lst, void *content)
{
	t_list_fd	*node;

	node = (void *)malloc(1 * sizeof(t_list_fd));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->content = content;
	node->next = NULL;
	if (!lst)
		return (node);
	else if (lst->next == NULL)
		lst->next = node;
	else
	{
		while (lst->next)
			lst = lst->next;
		lst->next = node;
	}
	return (node);
}

/*NOTE: you're expecting to find just one node for each fd
the functions looks for the first fd-node found
if not found leaves everything as it is*/
static void	ft_lstclear_fd(int fd, t_list_fd **lst, void (*del)(void*))
{
	t_list_fd	*temp;
	t_list_fd	*nose;
	t_list_fd	*tail;

	if (!lst || !(*lst) || !del)
		return ;
	tail = NULL;
	temp = *lst;
	while (temp && temp->fd != fd)
	{
		tail = temp;
		temp = temp->next;
	}
	if (!temp)
		return ;
	nose = temp->next;
	(*del)(temp->content);
	free(temp);
	if (tail)
		tail->next = nose;
	else
		*lst = nose;
}

static char	*his_sidekick(int fd, char *line, t_list_fd *trubbish,
				t_list_fd **leftovers);
static char	*the_magician(int fd, char *line, char *buff,
				t_list_fd **leftovers);
static char	*munchlax(int fd, t_list_fd *curr_lefties);

/*check if the_magiciasn actually did something:
if he didn't (we reached EOL or an error occured), returns NULL
if the trick (line) of the_magician doesn't contain a new_line,
	return the whole trick
if it does create a substr of the elements after the '\n',
clear/create curr_lefties content and assigne the substr pointer to it,
then returns a substr of the chars of line up to the '\n' (included)
than frees the line
trubbish is a temp_leftovers*/
static char	*his_sidekick(int fd, char *line, t_list_fd *trubbish,
				t_list_fd **leftovers)
{
	char	*new_line;

	if (!ft_strichr(line, '\n') || !line[ft_strichr(line, '\n')])
	{
		ft_lstclear_fd(fd, leftovers, &free);
		return (line);
	}
	while (trubbish && trubbish->next && trubbish->fd != fd)
		trubbish = trubbish->next;
	if (!trubbish || (!trubbish->next && trubbish->fd != fd))
		trubbish = ft_lstnew_add_back_ptr(fd, trubbish, NULL);
	else if (trubbish->fd == fd)
		free(trubbish->content);
	if (!trubbish)
	{
		free (line);
		return (NULL);
	}
	if (!(*leftovers))
		*leftovers = trubbish;
	trubbish->content = ft_substr(line, ft_strichr(line, '\n'),
			ft_strlen(line));
	new_line = ft_substr(line, 0, ft_strichr(line, '\n'));
	free(line);
	return (new_line);
}

/*reads up to '\n' and returns the string read
if BUFFER_SIZE > 1 the char found after '\n' aren't returned but
stored in leftovers*/
static char	*the_magician(int fd, char *line, char *buff, t_list_fd **leftovers)
{
	int	i;

	while (42)
	{
		i = 0;
		while (i <= BUFFER_SIZE)
			buff[i++] = '\0';
		i = read(fd, buff, BUFFER_SIZE);
		if (i <= 0)
			break ;
		if (line == (char *)42 || line == (char *)2)
			line = NULL;
		line = ft_strjoin_free(line, buff);
		if (!line)
			return (NULL);
		if (ft_strichr(buff, '\n'))
			break ;
	}
	if (i <= 0 && !(!i && (line != (char *)42 && line != (char *)2) && *line))
	{
		if (line != (char *)42 && line != (char *)2)
			free(line);
		return (NULL);
	}
	return (his_sidekick(fd, line, *leftovers, leftovers));
}

/*looks for a node with the current fd, if found
checks if there's a newline in the leftovers of the previous call
if so returns the line up to that point and updates leftovers,
if there isn't returns ((char *)42) and leaves leftovers as it is.
(all of this while moving the original leftover pointer)
If no node with curr fd is found returns ((char *)42)*/
static char	*munchlax(int fd, t_list_fd *curr_lefties)
{
	char		*new_lefties;
	char		*line;

	if (!curr_lefties)
		return ((char *)2);
	while (curr_lefties->next && curr_lefties->fd != fd)
		curr_lefties = curr_lefties->next;
	if (curr_lefties->fd != fd)
		return ((char *)42);
	if (!ft_strichr(curr_lefties->content, '\n'))
	{
		line = ft_substr(curr_lefties->content, 0,
				ft_strlen(curr_lefties->content));
		return (line);
	}
	line = ft_substr(curr_lefties->content, 0,
			ft_strichr(curr_lefties->content, '\n'));
	if (!line)
		return (NULL);
	new_lefties = ft_substr(curr_lefties->content,
			ft_strichr(curr_lefties->content, '\n'),
			ft_strlen(curr_lefties->content));
	free(curr_lefties->content);
	curr_lefties->content = new_lefties;
	return (line);
}

char	*get_next_line(int fd)
{
	static void			*leftovers;
	char				*line;
	char				buff[BUFFER_SIZE];

	line = munchlax(fd, (t_list_fd *)leftovers);
	if (line == NULL)
		return (NULL);
	else if ((line != (char *)42 && line != (char *)2)
		&& (ft_strichr(line, '\n')))
		return (line);
	line = the_magician(fd, line, buff, (t_list_fd **)&leftovers);
	if (!line)
		ft_lstclear_fd(fd, (t_list_fd **)&leftovers, &free);
	return (line);
}