/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_read_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 03:57:24 by totommi           #+#    #+#             */
/*   Updated: 2025/06/20 05:15:55 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"
#include <fcntl.h>

int		yft_read_file(const char *path, char ***file);

static void	print_file(char **file)
{
	unsigned int	i;

	i = 0;
	while (file[i] != NULL)
	{
		ft_printf("%s", file[i]);
		i++;
	}
}

/* reads the whole file into a matrix of strings */
int		yft_read_file(const char *path, char ***file)
{
	char			**my_temp_file;
	unsigned int	size;
	int				fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (3);
	size = 2;
	(*file) = (char **)malloc(size * sizeof(char *));
	if ((*file) == NULL)
		return (close(fd), 2);
	(*file)[0] = get_next_line(fd);
	(*file)[1] = NULL;
	while ((*file)[size - 2] != NULL)
	{
		my_temp_file = ft_realloc((*file), size * sizeof(char *), (size + 1) * sizeof(char *));
		if (my_temp_file == NULL)
			return (close(fd), free_mtx((void **)(*file)), 2);
		(*file) = my_temp_file;
		(*file)[size - 1] = get_next_line(fd);
		(*file)[size] = NULL;
		size++;
	}
	return (close(fd), 0);
}

int main(void)
{
	char	**file;
	char	*monoline;
	
	yft_read_file("my_cool_font.yft", &file);

	print_file(file);
	yft_strip_comments(file);
	print_file(file);
	yft_monoline_file(file, &monoline);
	ft_printf("monoline '%s'\n", monoline);
	free_mtx((void **)file);
	free(monoline);
	return (0);
}
