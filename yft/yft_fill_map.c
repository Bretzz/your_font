/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_fill_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 05:02:12 by totommi           #+#    #+#             */
/*   Updated: 2025/06/20 06:24:33 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"

int		yft_fill_map(char *miniline, t_font *font, int ascii);

unsigned int	get_pointer_color(char pointer, t_font *font)
{
	unsigned int	i;

	i = 0;
	while (font->table[i].pointer != '\0')
	{
		if (font->table[i].pointer == pointer)
			return (font->table[i].color);
		i++;
	}
	return (0x000000);
}

// "#......#."
static int	get_row_pixels(char *row, const int y, t_font *font, int ascii)
{
	static int	pixel_count;
	size_t	i;

	if (y == 0)
		pixel_count = 0;
	i = 1;
	while (row[i] != '"')
	{
		if (row[i] == '\0')
			return (1);
		if (get_pointer_color(row[i]) != 0x000000)
			font->ascii_table[ascii].map[pixel_count] = {i - 1, y};
		i++;
	}
	if (y == font->heigth - 1)
		font->ascii_table[ascii].map[pixel_count] = {-1, -1};
	return (0);
}

// {ascii=66,{"#######..","#......#.","#######..","#......#.","#######..",}}
int		yft_fill_map(char *miniline, t_font *font, int ascii)
{
	int		y;
	size_t	i;

	font->ascii_table[ascii].what = ft_atoi(&miniline[7]);
	i = 0;
	while (miniline[i] && miniline[i] != '{')
		i++;
	i = i + 1;
	y = 0;
	while(miniline[i] != '\0'
		&& (monoline[i] != '}' || monoline[i + 1] != '}'))
	{
		get_row_pixels(&miniline[i], y, font, ascii);
		while (miniline[i++] != ',')
		{
			if (miniline[i] == '\0')
				return (1);
		}
		y++;
	}
	if (miniline[i] == '\0')
		return (1);
	return (0);
}
