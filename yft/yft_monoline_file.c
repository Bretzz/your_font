/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_monoline_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 05:07:07 by totommi           #+#    #+#             */
/*   Updated: 2025/06/20 05:14:12 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"

int	yft_monoline_file(char **file, char **monoline);

static unsigned int	get_full_length(char **file)
{
	unsigned int	len;
	unsigned int	i;

	len = 0;
	i = 0;
	while (file[i] != NULL)
	{
		len += ft_strlen(file[i]);
		i++;
	}
	return (len);
}
int	yft_monoline_file(char **file, char **monoline)
{
	unsigned int	total;
	unsigned int	line;
	size_t			i;
	size_t			s;

	if (!file || !monoline)
		return (1);
	total = get_full_length(file);
	(*monoline) = (char *)malloc((total + 1) * sizeof(char));
	if ((*monoline) == NULL)
		return (2);
	line = 0;
	s = 0;
	while (file[line] != NULL)
	{
		i = 0;
		while (file[line][i] != '\0')
		{
			if (!ft_isspace(file[line][i]))
				(*monoline)[s++] = file[line][i];
			i++;
		}
		line++;
	}
	return (0);
}
