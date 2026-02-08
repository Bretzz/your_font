/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_fill_spacing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:50:50 by topiana-          #+#    #+#             */
/*   Updated: 2026/02/08 18:24:40 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"

void	fill_spacing(t_img *img,
	void (pixel_put)(t_img*, unsigned int, unsigned int, unsigned int),
	t_font *font, int *coord, int scale);

void	fill_spacing(t_img *img,
	void (pixel_put)(t_img*, unsigned int, unsigned int, unsigned int),
	t_font *font, int *coord, int scale)
{
	const int	start_x = coord[0] + (font->width * scale);
	int			my_x;
	int			my_y;
	int			i;
	int			j;

	if (font->table[0].color == VOID)
		return ;
	i = 0;
	while (i < font->space * scale)
	{
		j = 0;
		while (j < font->height * scale)
		{
			my_x = start_x + i;
			my_y = coord[1] + j;
			if (my_x >= 0 && my_x < img->width
				&& my_y >= 0 && my_y < img->height)
				(*pixel_put)(img, my_x, my_y, font->table[0].color);
			j++;
		}
		i++;
	}
}
