/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:42:30 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/09 10:12:56 by aklimchu         ###   ########.fr       */
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
		x1 = (cub->cell_size / 7) * cos(angle * M_PI / 180);
		y1 = (cub->cell_size / 7) * sin(angle * M_PI / 180);
		mlx_put_pixel(cub->img_map, cub->player.x + x1, cub->player.y + y1, 0xFFFFFFFF);
		i += 0.1;
	}
	//draw direction line
	/* draw_line(cub->img_map, (t_coord_f){cub->player.x, cub->player.y}, \
		(t_coord_f){cub->player.x + cub->player.dx * 5, \
		cub->player.y + cub->player.dy * 5}, 0xFFFFFFFF); */ 
	
}

//The function draws the line based on given dimensions
void	draw_line(mlx_image_t *img, t_coord_f a, t_coord_f b, int color)
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
		mlx_put_pixel(img, x, y, color);
		x += diff_x;
		y += diff_y;
		--pixels;
	}
}

void	draw_rect(mlx_image_t *img, t_rect rect)
{
	int		x;
	int		y;

	x = rect.x;
	y = rect.y;
	while (x < rect.x + rect.width)
		mlx_put_pixel(img, x++, y, rect.color);
	while (y < rect.y + rect.height)
		mlx_put_pixel(img, x, y++, rect.color);
	while (x > rect.x)
		mlx_put_pixel(img, x--, y, rect.color);
	while (y > rect.y)
		mlx_put_pixel(img, x, y--, rect.color);
}

void	fill_rect(mlx_image_t *img, t_rect rect)
{
	int		y;
	int		x;

	y = rect.y;
	while (y < rect.y + rect.height)
	{
		x = rect.x;
		while (x < rect.x + rect.width)
			mlx_put_pixel(img, x++, y, rect.color);
		y++;
	}
}