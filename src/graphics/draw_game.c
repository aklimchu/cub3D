/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 09:40:50 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/12 15:39:14 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "../inc/cub3D.h"

void draw_textures(t_cub *cub, double dist_to_ray, int ray_loop, double ray_angle, int side, size_t n_rays)
{

	double	angle_diff = cub->player.angle - ray_angle; // right name?
	angle_diff = normalize_angle(angle_diff);
	double dist_to_ray_corr = dist_to_ray * cos(angle_diff); // fisheye
	double	wall_height = CELL_SIZE * cub->img_map->height / dist_to_ray_corr;
	double	wall_offset = (double)cub->img_map->height / 2 - wall_height / 2;
	int x = ray_loop * (cub->img_game->width / n_rays);
	int y_start = wall_offset;
	int	y_end	= wall_height + wall_offset;
	double ray_dist_along_wall = 0;

	mlx_texture_t *texture;
	texture = NULL;
	//printf("player angle: %f\n", cub->player.angle); 
	double ray_hit_location = 0;
	if (side == 1) // Horizontal
	{
		ray_hit_location = (cub->player.x + dist_to_ray * cos(ray_angle));
		ray_dist_along_wall = ray_hit_location - CELL_SIZE * floor((ray_hit_location / CELL_SIZE));
		if (ray_angle > 0 && ray_angle < M_PI)
			texture = cub->textures.s;
		else
			texture = cub->textures.n;
	}
	else if (side == 0) // Vertical
	{
		ray_hit_location = (cub->player.y + dist_to_ray * sin(ray_angle));
		ray_dist_along_wall = ray_hit_location - CELL_SIZE * floor((ray_hit_location / CELL_SIZE));
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
	int texture_x = (int)floor(ray_dist_along_wall * (texture->width - 1));
	i = 0;
	if ((uint32_t)y_end > cub->img_game->height)
		y_end = cub->img_game->height;
	if (y_start < 0) // y_start + i = 0
		i = -y_start;
	if (y_start > 0)
		draw_line(cub->img_game, (t_coord_f){x, 0}, (t_coord_f){x, y_start - 1}, get_rgba(cub->map->roof_color));
	while (y_start + i < y_end && (uint32_t)y_end <= cub->img_game->width)
	{
		uint8_t* pixelstart_t = &texture->pixels[(((int)(floor(i * y_scale) * texture->width) + texture_x) * BPP)];
		uint8_t* pixelstart_i = &cub->img_game->pixels[((y_start + i) * cub->img_game->width + x) * BPP];
		ft_memcpy(pixelstart_i, pixelstart_t, BPP * cub->img_game->width / n_rays);
		i++;
	}
	if ((uint32_t)y_end < cub->img_game->height - 1)
	{
		draw_line(cub->img_game, (t_coord_f){x, y_end}, (t_coord_f){x, cub->img_game->height - 1}, get_rgba(cub->map->floor_color));
	}
}
