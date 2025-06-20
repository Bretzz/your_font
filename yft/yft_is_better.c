/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_is_better.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 03:51:02 by totommi           #+#    #+#             */
/*   Updated: 2025/06/20 05:18:41 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"

int		yft_is_better(const char *path);

int		yft_is_better(const char *path)
{
	static	t_font	fonts[10];
	static int		index;
	char			**file;
	char			*monoline;

	if (index == 10)
		return (1);
	if (yft_parse_file(path) != 0)
		return (2);
	if (yft_read_file(path, &file) != 0)
		return (3);
	if (yft_strip_comments(file) != 0)
		return (free_mtx((void **)file), 4);
	if (yft_monoline_file(file, &monoline) != 0)
		return (free_mtx((void **)file), 5);
	free_mtx((void **)file);
	if (yft_fill_font(monoline, &fonts[index]) != 0)
		return (free(monoline), 6);
	free_mtx(monoline);
	index++;
	return (0)
}
