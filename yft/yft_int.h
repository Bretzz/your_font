/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_int.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totommi <totommi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:48:06 by totommi           #+#    #+#             */
/*   Updated: 2025/06/21 02:15:34 by totommi          ###   ########.fr       */
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

# define FONT_STRING "font="	/* maybe useless? (and so on...) */
# define WIDTH_STRING "width="

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
	char	what;			// ascii to display
	int		map[257][3];	// [x,y,color]
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
	int				colors;
	t_color_pair	table[16];
	t_draw_map		ascii_table[128];
}				t_font;

void	*yft_string_to_image(void *mlx_ptr, const char *font_name, const char *string, int scale);

t_img	yft_img_init(void *mlx_ptr, int length, int heigth);

void	yft_draw_ascii(t_img *img, t_draw_map *map, int x, int scale);

/* GET THE FONT */

/* do not ge it out of here */
t_font	*yft_font_db(int n);

/* import your font */
int		yft_is_better(const char *path);

int		yft_parse_file(const char *path);

int		yft_read_file(const char *path, char **file);
int		yft_strip_comments(char *file);
int		yft_monoline_file(char *file, char **monoline);

int		yft_fill_font(char *monoline, t_font *font);
int		yft_fill_map(char *miniline, t_font *font);

#endif