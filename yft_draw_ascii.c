/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_draw_ascii.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:26:01 by topiana-          #+#    #+#             */
/*   Updated: 2026/02/08 19:16:19 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"

void	yft_draw_ascii(t_img *img,
	void (pixel_put)(t_img*, unsigned int, unsigned int, unsigned int),
	t_draw_map *map, int *coord, int scale);

// #todo i want scaling to be int so i can do flip things, for now just casting it is fine
void	draw_scaled_pixel(
	t_img *img,
	void (pixel_put)(t_img*, unsigned int, unsigned int, unsigned int),
	unsigned int *pixel, unsigned int color, int scale)
{
	unsigned int	t;
	unsigned int	s;

	t = 0;
	while (t < (unsigned int)scale)
	{
		s = 0;
		while (s < (unsigned int)scale)
		{
			if (pixel[0] + t < img->width && pixel[1] + s < img->height)
				(*pixel_put)(img, pixel[0] + t, pixel[1] + s, color);
			s++;
		}
		t++;
	}
}

void	yft_draw_ascii(
	t_img *img,
	void (pixel_put)(t_img*, unsigned int, unsigned int, unsigned int),
	t_draw_map *map, int *coord, int scale)
{
	unsigned int	pixel[2];
	int				i;

	if (map->what == '\0')
		return ;
	i = 0;
	while (map->map[i][0] != -1)
	{
		pixel[0] = coord[0] + (map->map[i][0]) * scale;
		pixel[1] = coord[1] + (map->map[i][1]) * scale;
		if (pixel[0] >= 0 && pixel[0] < img->width
			&& pixel[1] >= 0 && pixel[1] < img->height
			&& map->map[i][2] != VOID)
			draw_scaled_pixel(img, pixel_put, pixel, map->map[i][2], scale);
		i++;
	}
}
