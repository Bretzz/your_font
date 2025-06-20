/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_string_to_image.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:47:52 by totommi           #+#    #+#             */
/*   Updated: 2025/06/20 14:38:44 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"

void	*yft_string_to_image(void *mlx_ptr, const char *string, int scale);

static t_font *get_font_by_name(const char *string)
{
	const size_t	len = ft_strichr(string, ':') - 1;
	t_font *const	fonts = yft_font_db(0);
	unsigned int	i;

	i = 0;
	while (i < 10)
	{
		if (!ft_strncmp(string, fonts[i].name, len))
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
void	*yft_string_to_image(void *mlx_ptr, const char *string, int scale)
{
	t_font *const	font = get_font_by_name(string);
	t_img			img;
	size_t			i;
	int				x;

	if (font == NULL)
	{
		ft_printfd(2, "yft: Invalid font\n");
		return (NULL);
	}
	img = yft_img_init(mlx_ptr, font, ft_strlen(string) * font->width,
			font->heigth);
	if (img.img == NULL)
		return (NULL);
	i = ft_strichr(string, ':');
	x = 0;
	while (string[i] != '\0')
	{
		yft_draw_ascii(&img, &font->ascii_table[string[i]], x);	//need to sort array or fill gaps (DONE)
		if (string[i + 1] != '\0')
			fill_spacing(&img, font, x + font->width);
		x += font->width + font->space;
		i++;
	}
	return (img.img);
}
