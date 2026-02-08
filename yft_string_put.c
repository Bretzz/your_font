/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_string_put.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:19:47 by topiana-          #+#    #+#             */
/*   Updated: 2026/02/08 19:09:07 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"

int	yft_string_put(t_img *img_ptr,
	void (pixel_put)(t_img*, unsigned int, unsigned int, unsigned int),
	unsigned int x, unsigned int y, const char *string, const char *font_name);

static t_font	*get_any_font(const char *font_name)
{
	t_font *const	fonts = yft_font_db(0);
	unsigned int	i;

	i = 0;
	while (i < 10)
	{
		if (fonts[i].name[0] != '\0'
			&& (font_name == NULL || ft_strcmp(font_name, fonts[i].name) == 0))
			return (&fonts[i]);
		i++;
	}
	return (NULL);
}

int	yft_string_put(t_img *img,
	void (pixel_put)(t_img*, unsigned int, unsigned int, unsigned int),
	unsigned int x, unsigned int y, const char *string, const char *font_name)
{
	t_font *const	font = get_any_font(font_name);
	size_t			i;
	const int		scale = 2;
	int				coord[2];

	if (font == NULL)
	{
		write(2, "yft: Font not found\n", 21);
		return (1);
	}
	coord[0] = x;
	coord[1] = y;
	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == ' ') yft_draw_space(img, pixel_put, font, coord, scale);
		else yft_draw_ascii(img, pixel_put, &font->ascii_table[(int)string[i]], coord, scale);
		if (string[i + 1] != '\0')
			fill_spacing(img, pixel_put, font, coord, scale);
		coord[0] = coord[0] + (font->width + font->space) * scale;
		++i;
	}
	return (0);
}
