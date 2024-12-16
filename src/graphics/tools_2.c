/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:42:30 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/16 12:02:13 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	draw_player(t_cub *cub)
{
	double	i;
	double	angle;
	double	x1;
	double	y1;

	i = 0;
	while (i < 360)
	{
		angle = i;
		x1 = ((double)CELL_SIZE / 20) * cos(angle * M_PI / 180);
		y1 = ((double)CELL_SIZE / 20) * sin(angle * M_PI / 180);
		mlx_put_pixel(cub->img_map, MM_W / 2 + (int)x1, MM_H / 2 + (int)y1, WHITE);
		i += 0.1;
	}
	if (!cub->player.dx && !cub->player.dy)
		draw_line(cub->img_map, (t_coord_f){(double)MM_W / 2, (double)MM_H / 2}, \
			(t_coord_f){(double)MM_W / 2 + cos(cub->player.angle) * PLAYER_SPEED * cub->mlx->delta_time * 2, \
			(double)MM_H / 2 + sin(cub->player.angle) * PLAYER_SPEED * cub->mlx->delta_time *  2}, WHITE);
	else
		draw_line(cub->img_map, (t_coord_f){(double)MM_W / 2, (double)MM_H / 2}, \
			(t_coord_f){(double)MM_W / 2 + cub->player.dx * 2, \
			(double)MM_H / 2 + cub->player.dy * 2}, WHITE);
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
