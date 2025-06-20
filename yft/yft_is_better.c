/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_is_better.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 03:51:02 by totommi           #+#    #+#             */
/*   Updated: 2025/06/20 14:59:08 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"

int		yft_is_better(const char *path);

t_font	*yft_font_db(int n)
{
	static	t_font	fonts[10];

	if (n >= 0 && n < 10)
		return(&fonts[n]);
	return (NULL);
}

int		yft_is_better(const char *path)
{
	static int		index;
	char			*file;
	char			*monoline;

	if (index == 10)
		return (1);
	if (yft_parse_file(path) != 0)
		return (2);
	if (yft_read_file(path, &file) != 0)
		return (3);
	if (yft_strip_comments(file) != 0)
		return (free(file), 4);
	if (yft_monoline_file(file, &monoline) != 0)
		return (free(file), 5);
	free(file);
	if (yft_fill_font(monoline, yft_font_db(index)) != 0)
		return (free(monoline), 6);
	free(monoline);
	index++;
	return (0);
}

static void print_pair(int *pair)
{
	ft_printf("{%d,%d},", pair[0], pair[1]);
}

static void	print_font(t_font *font)
{
	unsigned int	i;
	unsigned int	j;

	ft_printf("name: '%s', heigth=%d, width=%d, space=%d, colors=%d\n",
		font->name, font->heigth, font->width, font->space, font->colors);
	i = 0;
	while (i < 128)
	{
		if (font->ascii_table[i].what != '\0')
		{
			ft_printf("got what? %c\n", font->ascii_table[i].what);
			j = 0;
			while (font->ascii_table[i].map[j][0] != -1)
			{
				print_pair(font->ascii_table[i].map[j]);
				j++;
			}
			print_pair(font->ascii_table[i].map[j]);
			ft_printf("\n");
		}
		i++;
	}
}

int main(void)
{
	
	yft_is_better("my_cool_font.yft");

	// ft_printf("= = == = READ  == = = =\n%s", file);
	// // print_file(file);
	// yft_strip_comments(file);
	// // print_file(file);
	// yft_monoline_file(file, &monoline);
	// ft_printf("monoline '%s'\n", monoline);
	print_font(yft_font_db(0));


	void	*mlx_ptr = mlx_init();
	void	*img_ptr = yft_string_to_image(mlx_ptr, "MyCoolFont:AB", 1);
	
	if (img_ptr == NULL)
	{
		ft_printf("something went wrong :/\n");
		return (0);
	}
	void	*win_ptr = mlx_new_window(mlx_ptr, 200, 200, "your_font");
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	mlx_destroy_image(mlx_ptr, img_ptr);
	pause();
	mlx_destroy_window(mlx_ptr, win_ptr);
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
	return (0);
}
