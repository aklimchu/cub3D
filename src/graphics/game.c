/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 09:40:50 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/12 09:07:51 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "../inc/cub3D.h"

void draw_textures(t_cub *cub, float dist_to_ray, int ray_loop, float ray_angle, int side, size_t n_rays)
{

	double	angle_diff = cub->player.angle - ray_angle; // right name?
	if (angle_diff < 0)
		angle_diff += 2 * M_PI;
	if (angle_diff > 2 * M_PI)
		angle_diff -= 2 * M_PI;
	dist_to_ray = dist_to_ray * cos(angle_diff); // fisheye
	double	wall_height = CELL_SIZE * SCREEN_H / dist_to_ray;
	double	wall_offset = (double)SCREEN_H / 3 - wall_height / 2;
	int x = ray_loop * (cub->img_game->width / n_rays);
	int y_start = wall_offset;
	int	y_end	= wall_height + wall_offset;
	double ray_dist_along_wall = 0;

	mlx_texture_t *texture;
	texture = NULL;
	//printf("player angle: %f\n", cub->player.angle); 
	if (side == 1) // Horizontal
	{
		ray_dist_along_wall = (int)(cub->player.x + dist_to_ray * cos(ray_angle)) % CELL_SIZE;
		if (ray_angle > 0 && ray_angle < M_PI)
			texture = cub->textures.s;
		else
			texture = cub->textures.n;
	}
	else if (side == 0) // Vertical
	{
		ray_dist_along_wall = (int)(cub->player.y + dist_to_ray * sin(ray_angle)) % CELL_SIZE;
		if (ray_angle > M_PI / 2 && ray_angle < (1.5) * M_PI)
			texture = cub->textures.w;
		else
			texture = cub->textures.e;
	}
	else 
	{
		error_exit("Bad side :'(");
	}
	double y_scale = (double)texture->height / wall_height;
	ray_dist_along_wall /= CELL_SIZE; // Make percentage of progress along the wall

	int i;
	int texture_x = (int)(ray_dist_along_wall * texture->width);
	i = 0;
	if (y_end > SCREEN_H)
		y_end = SCREEN_H;
	if (y_start < 0) // y_start + i = 0
		i = -y_start;
	if (y_start > 0)
		draw_line(cub->img_game, (t_coord_f){x, 0}, (t_coord_f){x, y_start - 1}, BLUE);
	while (y_start + i < y_end && y_end <= SCREEN_H)
	{
		uint8_t* pixelstart_t = &texture->pixels[(((int)(floor(i * y_scale) * texture->width) + texture_x) * BPP)];
		uint8_t* pixelstart_i = &cub->img_game->pixels[((y_start + i) * cub->img_game->width + (x )) * BPP];
		ft_memcpy(pixelstart_i, pixelstart_t, BPP * cub->img_game->width / n_rays);
		i++;
	}
	if (y_end < SCREEN_H)
	{
		draw_line(cub->img_game, (t_coord_f){x, y_end}, (t_coord_f){x, SCREEN_H - 1}, RED);
	}
}
