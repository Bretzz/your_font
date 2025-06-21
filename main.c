/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 02:09:00 by totommi           #+#    #+#             */
/*   Updated: 2025/06/21 17:00:39 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft.h"
#include "mlx.h"
#include "libft.h"
#include <X11/X.h>

// cc main.c yft/yft.a libft/libft.a minilibx_opengl/libmlx.a -Iyft/include -I libft -I minilibx_opengl -L/usr/lib -L minilibx_opengl -lXext -lX11 -lm -lz -I/opt/homebrew/include -I/usr/X11/include -L/usr/X11/lib -framework OpenGL -framework AppKit
// cc main.c yft/yft.a libft/libft.a minilibx-linux/libmlx.a -Iyft/include -I libft -I minilibx-linux -L/usr/lib -L minilibx-linux -lXext -lX11

int	esc_exit(int keysym)
{
	if (keysym == 53
		|| keysym == 51
		|| keysym == 12)
		exit(0);
	// ft_printf("keysym %d\n", keysym);
	return (0);
}

int	my_exit(void *param)
{
	(void)param;
	exit(0);
}

int main(void)
{
	ft_printf("main in\n");

	yft_is_better("yft/fonts/wobbly.yft");
	yft_is_better("yft/fonts/my_cool_font.yft");
	
	ft_printf("got fonts\n");
	// ft_printf("= = == = READ  == = = =\n%s", file);
	// // print_file(file);
	// yft_strip_comments(file);
	// // print_file(file);
	// yft_monoline_file(file, &monoline);
	// ft_printf("monoline '%s'\n", monoline);
	// print_font(yft_font_db(0));


	void	*mlx_ptr = mlx_init();
	void	*win_ptr = mlx_new_window(mlx_ptr, 1000, 300, "your_font");
	ft_printf("window initialized\n");

	// void	*img_ptr = yft_string_to_image(mlx_ptr, "Wobbly", "AaBbCcDdEeFfGgHh", 3);
	// if (img_ptr == NULL)
	// {
	// 	ft_printf("something went wrong :/\n");
	// 	return (0);
	// }
	// mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 10, 10);
	// ft_printf("first put\n");
	// img_ptr = yft_string_to_image(mlx_ptr, "Wobbly", "IiJjKkLlMmNnOoPp", 3);
	// if (img_ptr == NULL)
	// {
	// 	ft_printf("something went wrong :/\n");
	// 	return (0);
	// }
	// mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 10, 68);

	// img_ptr = yft_string_to_image(mlx_ptr, "Wobbly", "QqRrSsTtUuVvWwXx", 3);
	// if (img_ptr == NULL)
	// {
	// 	ft_printf("something went wrong :/\n");
	// 	return (0);
	// }
	// mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 10, 126);

	// img_ptr = yft_string_to_image(mlx_ptr, "Wobbly", "YyZz0123456789", 3);
	// if (img_ptr == NULL)
	// {
	// 	ft_printf("something went wrong :/\n");
	// 	return (0);
	// }
	void	*img_ptr = mlx_new_image(mlx_ptr, 1000, 300);
	yft_string_put(img_ptr, 0, 0, "01289aaa");
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);

	


	mlx_hook(win_ptr, DestroyNotify, StructureNotifyMask, &my_exit, NULL);
	mlx_key_hook(win_ptr, &esc_exit, NULL);
	mlx_loop(mlx_ptr);
	// mlx_destroy_image(mlx_ptr, img_ptr);
	mlx_destroy_window(mlx_ptr, win_ptr);
	// mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);

	return (0);
}