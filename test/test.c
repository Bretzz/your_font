/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 02:09:00 by totommi           #+#    #+#             */
/*   Updated: 2026/02/10 16:56:59 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft.h"
#include "mlx.h"
#include <X11/X.h>
#include <stdio.h>
#include <stdlib.h>

int	esc_exit(int keysym)
{
	if (keysym == 65307	/* Ubuntu */
		|| keysym == 51
		|| keysym == 12/* MacOS */)
		exit(0);

	return (0);
}

int	my_exit(void *param)
{
	(void)param;
	exit(0);
}

void	pixel_put(t_img *img, unsigned int x, unsigned int y, unsigned int color)
{
	if (img == NULL || img->img_ptr == NULL)
		return ;

	if (x > img->width || y > img->height)
		return ;

	// draw addr
	*(unsigned int *)(*((char **)(img->pre_loaded) + 2)
		+ ((y * ((int*)img->pre_loaded)[1])
			+ (x * ((int*)img->pre_loaded)[0]))) = color;

}

int main(void)
{

	// Load font
	int ret = yft_is_better("../fonts/wobbly.yft");
	if (ret != 0)
	{
		printf("Failed to load font\n");
		return 1;
	}

	// Initialize MinilibX window
	void	*mlx_ptr = mlx_init();
	void	*win_ptr = mlx_new_window(mlx_ptr, 1000, 300, "your_font");

	// Initialize image
	void	*img_ptr = mlx_new_image(mlx_ptr, 1000, 300);

	// Prepare image data structure for your_font
	t_img	img_data;
	int		preloaded[6] = { 0 };
	char	**addr_ptr = ((char **)preloaded + 2);	// <-- storing the mem address inside an array of int
	
	img_data.width = 1000;
	img_data.height = 300;
	img_data.img_ptr = img_ptr;
	*addr_ptr = mlx_get_data_addr(img_ptr, &preloaded[0], &preloaded[1], &preloaded[2]);
	preloaded[0] >>= 3;
	img_data.pre_loaded = preloaded;

	// Write on the image
	yft_string_put(&img_data, &pixel_put, 0, 0, "your font is actually pretty :)", "Wobbly", 2);
	
	// Draw the image on the window using MinilibX
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);

	// Add exit hooks
	mlx_hook(win_ptr, DestroyNotify, StructureNotifyMask, &my_exit, NULL);
	mlx_key_hook(win_ptr, &esc_exit, NULL);

	// loop the image on the screen
	mlx_loop(mlx_ptr);

	// Cleanup procedure skipped ;P (should be in my_exit and esc_exit)
	// mlx_destroy_image(mlx_ptr, img_ptr);
	// mlx_destroy_window(mlx_ptr, win_ptr);
	// mlx_destroy_display(mlx_ptr);
	// free(mlx_ptr);

	return (0);
}