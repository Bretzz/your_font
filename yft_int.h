/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_int.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:48:06 by totommi           #+#    #+#             */
/*   Updated: 2026/02/08 19:16:31 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef YFT_INT_H
# define YFT_INT_H

/* The idea is that you can load up your font, and the function will create
an mlx image with the string passed using your font. Your choice of what
to do with that image (similar to xpm functions) */

# include "yft_libft.h"
// # include "mlx.h"
# include <unistd.h>
# include <stdlib.h> // free
# include <string.h> // memset, strcmp

# define VOID 0x000000
# define FILL 0xffffff

# define VOID_STRING "Void"
# define FILL_STRING "Fill"

# define FONT_STRING "font="	/* maybe useless? (and so on...) */
# define WIDTH_STRING "width="

# ifndef MAX_FONTS
#  define MAX_FONTS 10
# endif

// # ifdef __APPLE__

// typedef struct s_mlx_img
// {
// 	int		width;
// 	int		height;
// 	void	*other;
// }			t_mlx_img;

// # endif

// what the user will pass
typedef struct s_img
{
	void			*img_ptr;
	void			*pre_loaded;
	unsigned int	width;
	unsigned int	height;
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
	int				height;				// height of each char
	int				width;				// width of each char
	int				space;				// space between letters
	int				colors;
	t_color_pair	table[16];
	t_draw_map		ascii_table[128];
}				t_font;

/* USE THE FONT */

int			yft_string_put(t_img *img,
				void (pixel_put)(t_img*, unsigned int, unsigned int, unsigned int),
				unsigned int x, unsigned int y, const char *string, const char *font_name);

/* DRAWERS */

void		draw_scaled_pixel(t_img *img,
				void (pixel_put)(t_img*, unsigned int, unsigned int, unsigned int),
				unsigned int *pixel, unsigned int color, int scale);

void		yft_draw_ascii(t_img *img,
				void (pixel_put)(t_img*, unsigned int, unsigned int, unsigned int),
				t_draw_map *map, int *coord, int scale);

void		yft_draw_space(t_img *img,
				void (pixel_put)(t_img*, unsigned int, unsigned int, unsigned int),
				t_font *font, int *coord, int scale);

/* GET THE FONT */

/* do not ge it out of here */
t_font		*yft_font_db(int n);

/* import your font */
int			yft_is_better(const char *path);

int			yft_parse_file(const char *path);

int			yft_read_file(const char *path, char **file);
int			yft_strip_comments(char *file);
int			yft_monoline_file(char *file, char **monoline);

int			yft_fill_font(char *monoline, t_font *font);
int			yft_fill_map(char *miniline, t_font *font);

/* UTILS */

void	fill_spacing(t_img *img,
	void (pixel_put)(t_img*, unsigned int, unsigned int, unsigned int),
	t_font *font, int *coord, int scale);

#endif