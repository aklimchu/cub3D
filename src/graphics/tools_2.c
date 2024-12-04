/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:42:30 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/04 15:19:02 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	draw_player(t_cub *cub)
{
	float i, angle, x1, y1;

	i = 0;
	while (i < 360)
	{
		angle = i;
		x1 = 5 * cos(angle * M_PI / 180);
		y1 = 5 * sin(angle * M_PI / 180);
		mlx_put_pixel(cub->img, cub->player.x + x1, cub->player.y + y1, 0xFFFFFFFF);
		i += 0.1;
	}
	//draw direction line
	draw_line(cub->img, (t_coord_f){cub->player.x, cub->player.y}, \
		(t_coord_f){cub->player.x + cub->player.dx * 5, \
		cub->player.y + cub->player.dy * 5});
	
}

//The function draws the line based on given dimensions
void	draw_line(mlx_image_t *img, t_coord_f a, t_coord_f b)
{
	double	x;
	double	y;
	double	diff_x;
	double	diff_y;
	int		pixels;

	diff_x = b.x - a.x;
	diff_y = b.y - a.y;
	pixels = sqrt(diff_x * diff_x + diff_y * diff_y);
	diff_x /= pixels;
	diff_y /= pixels;
	x = a.x;
	y = a.y;
	while (pixels)
	{
		mlx_put_pixel(img, x, y, 0xFFFFFFFF);
		x += diff_x;
		y += diff_y;
		--pixels;
	}
}