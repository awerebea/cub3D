/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awerebea <awerebea@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 16:28:26 by awerebea          #+#    #+#             */
/*   Updated: 2020/07/28 12:15:28 by awerebea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int			f_window(t_sdf *opts)
{
	(void)opts;
	void	*mlx_ptr;
	void	*window;
	int x, y;

	x = 200;
	y = 200;
	mlx_ptr = mlx_init();
	window = mlx_new_window(mlx_ptr, 750, 750, "test");
	while(x < 400)
	{
		mlx_pixel_put(mlx_ptr, window, x, y, 0xFFFFFF);
		x++;
		y++;
	}
	y = 200;
	while(x > 200)
	{
		mlx_pixel_put(mlx_ptr, window, x, y, 0xFFFFFF);
		x--;
		y++;
	}
	mlx_loop(mlx_ptr);
	return (0);
}
