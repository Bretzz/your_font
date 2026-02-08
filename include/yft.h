/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 02:09:18 by totommi           #+#    #+#             */
/*   Updated: 2026/02/07 19:08:31 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef YFT_H
# define YFT_H

/* The idea is that you can load up your font, then put it on top of an image.
The first usecase is with MinilibX, but it's not bound to that library. */

// data needed to draw the font
typedef struct s_img
{
	void	*img_ptr;		// the data of your interface
	void	*pre_loaded;	// some stored data if you need them
	int		width;			// image width
	int		height;			// image heigth
}				t_img;

/* import your font */
int		yft_is_better(const char *path);

/* puts the string directly on the image passed
the 'pixel_put' functions takes:
	@t_img: the image wrapper struct
	@x the X coordinate of the pixel to be drawn
	@y the Y coordinate of the pixel to be drawn
	@color the color of the pixel */
int		yft_string_put(t_img *img,
			void (pixel_put)(t_img*, unsigned int, unsigned int, unsigned int),
			unsigned int x, unsigned int y, const char *string, const char *font_name);

#endif