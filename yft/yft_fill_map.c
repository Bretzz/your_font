/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_fill_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 05:02:12 by totommi           #+#    #+#             */
/*   Updated: 2025/06/20 14:26:28 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"

int		yft_fill_map(char *miniline, t_font *font);

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
static int	get_row_pixels(char *row, const int y, t_font *font, int what)
{
	static int	pixel_count;
	int			color;
	size_t	i;

	if (y == 0)
		pixel_count = 0;
	i = 1;
	while (row[i] != '"')
	{
		if (row[i] == '\0')
			return (1);
		color = get_pointer_color(row[i], font);
		ft_printf("%c has color %x\n", row[i], color);
		if (color != 0x000000)
		{
			font->ascii_table[what].map[pixel_count][0] = i - 1;
			font->ascii_table[what].map[pixel_count][1] = y;
			font->ascii_table[what].map[pixel_count][2] = color;
			// ft_printf("added {%d,%d}\n", i - 1, y);
			pixel_count++;
		}
		i++;
	}
	if (y == font->heigth - 1)
	{
		font->ascii_table[what].map[pixel_count][0] = -1;
		font->ascii_table[what].map[pixel_count][1] = -1;
		// ft_printf("terminated\n");
	}
	return (0);
}

// {ascii=66,{"#######..","#......#.","#######..","#......#.","#######..",}}
int		yft_fill_map(char *miniline, t_font *font)
{
	const int	what = ft_atoi(&miniline[7]);
	int		y;
	size_t	i;
	
	// ft_printf("filling map %s, got what=%d\n", miniline, what);
	font->ascii_table[what].what = what;
	i = 1;
	while (miniline[i] && miniline[i] != '{')
		i++;
	i = i + 1;
	ft_printf("colors starts here %s\n", &miniline[i]);
	// exit(0);
	y = 0;
	while(miniline[i] != '\0' && y < font->heigth
		&& (miniline[i] != '}' || miniline[i + 1] != '}'))
	{
		get_row_pixels(&miniline[i], y, font, what);
		// exit(0);
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
