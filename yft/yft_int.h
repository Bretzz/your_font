/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_int.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:48:06 by totommi           #+#    #+#             */
/*   Updated: 2025/06/20 05:49:43 by totommi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef YFT_INT_H
# define YFT_INT_H

/* The idea is that you can load up your font, and the function will create
an mlx image with the string passed using your font. Your choice of what
to do with that image (similar to xpm functions) */

# include "libft.h"
# include "mlx.h"
# include <unistd.h>

# define VOID_STRING "Void"
# define FILL_STRING "Fill"

# define FONT_STRING "font"	/* maybe useless? (and so on...) */
# define WIDTH_STRING "widt"

// mlx img related data
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		heigth;
}				t_img;

/* current 16x16, go with malloc for bigger sized fonts */
typedef struct s_draw_map
{
	char	what;
	int		map[256][2];
}				t_draw_map;

typedef struct s_color_pair
{
	char			pointer;
	unsigned int	color;
}			t_color_pair;

typedef struct s_font
{
	char			name[128];			// name of the font
	int				heigth;				// heigth of each char
	int				width;				// width of each char
	int				space;				// space between letters
	t_color_pair	table[16];
	t_draw_map		ascii_table[128];
}				t_font;

/* "font:string" */
void	*yft_sting_to_image(const char *string, int x, int y, int scale);

int		yft_img_init(t_font *font, size_t len, t_img *img);

int		yft_draw_ascii(t_img *img, t_draw_map *map);

/* GET THE FONT */

/* import your font */
int		yft_is_better(const char *path);

int		yft_parse_file(const char *path);

int		yft_read_file(const char *path, char ***file);
int		yft_strip_comments(char **file);
int		yft_monoline_file(char **file, char **monoline);

int		yft_fill_font(char *monoline, t_font *font);
int		yft_fill_map(char *miniline, t_font *font, int ascii);

#endif