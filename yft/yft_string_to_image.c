/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_string_to_image.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:47:52 by totommi           #+#    #+#             */
/*   Updated: 2025/06/21 02:20:34 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"

void	*yft_string_to_image(void *mlx_ptr, const char *font_name, const char *string, int scale);

static t_font *get_font_by_name(const char *font)
{
	t_font *const	fonts = yft_font_db(0);
	unsigned int	i;

	i = 0;
	while (i < 10)
	{
		if (!ft_strcmp(font, fonts[i].name))
			return (&fonts[i]);
		i++;
	}
	return (NULL);
}

static void	fill_spacing(t_img *img, t_font *font, int x)
{
	int	my_x;
	int	my_y;
	int	i;

	i = 0;
	while (i < font->space)
	{
		my_y = 0;
		while (my_y < font->heigth)
		{
			my_x = x + i;
			*(unsigned int *)(img->addr + ((my_y * img->line_length)
				+ (my_x * img->bpp))) = font->table[0].color;
			my_y++;
		}
		i++;
	}
}

/* font:string */
void	*yft_string_to_image(void *mlx_ptr, const char *font_name, const char *string, int scale)
{
	t_font *const	font = get_font_by_name(font_name);
	t_img			img;
	size_t			i;
	int				x;

	if (font == NULL)
	{
		ft_printfd(2, "yft: Invalid font\n");
		return (NULL);
	}
	img = yft_img_init(mlx_ptr, ft_strlen(string)
			* (font->width + font->space) * scale,
		font->heigth * scale);
	if (img.img == NULL)
		return (NULL);
	x = 0;
	i = 0;
	while (string[i] != '\0')
	{
		yft_draw_ascii(&img, &font->ascii_table[(int)string[i]], x, scale);	//need to sort array or fill gaps (DONE)
		if (string[i + 1] != '\0')
			fill_spacing(&img, font, (x + font->width) * scale);
		x = x + font->width + font->space;
		i++;
	}
	return (img.img);
}
