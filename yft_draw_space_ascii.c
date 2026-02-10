/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_draw_space_ascii.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 19:00:37 by topiana-          #+#    #+#             */
/*   Updated: 2026/02/10 15:59:07 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"

void	yft_draw_space_ascii(t_img *img,
			void (pixel_put)(t_img*, unsigned int, unsigned int, unsigned int),
			t_font *font, int *coord, int scale);

void	yft_draw_space_ascii(t_img *img,
		void (pixel_put)(t_img*, unsigned int, unsigned int, unsigned int),
		t_font *font, int *coord, int scale)
{
	const unsigned int	background = font->table[0].color;
	unsigned int		pixel[2];
	int					y;
	int					x;

	if (background == VOID)
		return ;

	y = 0;
	while (y < font->height)
	{
		x = 0;
		while (x < font->width)
		{
			pixel[0] = coord[0] + x * scale;
			pixel[1] = coord[1] + y * scale;
			if (pixel[0] >= 0 && pixel[0] < img->width
				&& pixel[1] >= 0 && pixel[1] < img->height)
				draw_scaled_pixel(img, pixel_put, pixel, background, scale);
			++x;
		}
		++y;
	}
}