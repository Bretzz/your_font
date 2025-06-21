/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_string_put.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:19:47 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/21 17:56:05 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"

int	yft_string_put(void *img_ptr, int x, int y, const char *string);

static t_font	*get_any_font(void)
{
	t_font *const	fonts = yft_font_db(0);
	unsigned int	i;

	i = 0;
	while (i < 10)
	{
		if (fonts[i].name[0] != '\0')
			return (&fonts[i]);
		i++;
	}
	return (NULL);
}

static void	fill_spacing(t_my_img *img, t_font *font, int x, int scale)
{
	int	my_x;
	int	my_y;
	int	i;

	i = 0;
	while (i < font->space * scale)
	{
		my_y = 0;
		while (my_y < font->heigth * scale)
		{
			my_x = x + i;
			if (my_x < img->width && my_y < img->heigth)
				*(unsigned int *)(img->addr + ((my_y * img->line_length)
							+ (my_x * img->bpp))) = font->table[0].color;
			my_y++;
		}
		i++;
	}
}

/* font is arbitrairly choosen for now... */
/* data is formatted like this:
	data[0] = x,
	data[1] = y,
	data[2] = img width
	data[3] = img heigth */
/* right now scale is 1 */
int	yft_string_put(void *img_ptr, int x, int y, const char *string)
{
	t_font *const	font = get_any_font();
	t_my_img		my_img;
	size_t			i;
	const int		scale = 3;
	int				coord[2];

	if (font == NULL)
	{
		ft_printfd(2, "yft: No font found\n");
		return (1);
	}
	coord[0] = x;
	coord[1] = y;
	i = 0;
	img_get_data(img_ptr, &my_img);
	while (string[i] != '\0')
	{
		yft_draw_ascii(&my_img, &font->ascii_table[(int)string[i]],
			coord, scale);
		if (string[i++ + 1] != '\0')
			fill_spacing(&my_img, font, (coord[0] + font->width)
				* scale, scale);
		coord[0] = coord[0] + font->width + font->space;
	}
	return (0);
}
