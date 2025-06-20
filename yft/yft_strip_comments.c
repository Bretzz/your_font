/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_strip_comments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 04:25:00 by totommi           #+#    #+#             */
/*   Updated: 2025/06/20 04:51:54 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"

int		yft_strip_comments(char **file);

static int	is_white(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/* passed a pointer to the beginning of the comment */
static int	clear_wierd_comment(char *line)
{
	size_t	i;

	i = 1;
	while ((line[i] != '*' || line[i + 1] != '/'))
	{
		if (line[i] == '\0')
		{
			line[i] = '\0';
			return (1);
		}
		i++;
	}
	ft_memmove(line, &line[i + 2], ft_strlen(&line[i + 2]) + 1);
	return (0);
}

/* both '/ *' and '//' comments handled */
static void	strip_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '/' && line[i + 1] == '/')
		{
			line[i] = '\0';
			return ;
		}
		if (line[i] == '/' && line[i + 1] == '*')
		{
			if (clear_wierd_comment(&line[i]) != 0)
				return ;
		}
		i++;
	}
}

int		yft_strip_comments(char **file)
{
	unsigned int	i;

	if (file == NULL)
		return (1);
	i = 0;
	while (file[i] != NULL)
	{
		strip_line(file[i]);
		if (is_white(file[i]))
		{
			free(file[i]);
			ft_memmove(&file[i], &file[i + 1],
				(ft_mtxlen((void **)&file[i + 1]) + 1) * sizeof(char *));
			i--;
		}
		i++;
	}
	return (0);
}

// int main(void)
// {
// 	char	line[] = "line to strip /* properly  */, gotchu? // fr man";

// 	strip_line(line);
// 	ft_printf("'%s'\n", line);
// 	return (0);
// }