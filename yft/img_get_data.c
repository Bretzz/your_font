/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_get_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:40:05 by topiana-          #+#    #+#             */
/*   Updated: 2025/06/21 16:40:31 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"
#include "mlx_int.h"

void	img_get_data(void *img_ptr, t_my_img *img)
{
	t_img *const	mlx_img = (t_img *)img_ptr;

	img->img = img_ptr;
	img->addr = mlx_img->data;
	img->bits_per_pixel = mlx_img->bpp;
	img->line_length = mlx_img->size_line;
	img->endian = mlx_img->image->byte_order;
	img->heigth = mlx_img->height;
	img->width = mlx_img->width;
	img->bpp = img->bits_per_pixel >> 3;
}
