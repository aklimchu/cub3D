/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 09:40:50 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/12 11:30:11 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "../inc/cub3D.h"

void draw_textures(t_cub *cub, float dist_to_ray, int ray_loop, float ray_angle, int side, size_t n_rays)
{

	double	angle_diff = cub->player.angle - ray_angle; // right name?
	angle_diff = normalize_angle(angle_diff);
	dist_to_ray = dist_to_ray * cos(angle_diff); // fisheye
	double	wall_height = CELL_SIZE * SCREEN_H / dist_to_ray;
	double	wall_offset = (double)SCREEN_H / 3 - wall_height / 2;
	int x = ray_loop * (cub->img_game->width / n_rays);
	int y_start = wall_offset;
	int	y_end	= wall_height + wall_offset;
	double y_scale = (double)cub->textures.n->height / wall_height;
	double ray_dist_along_wall = 0;

	if (side == 1) // Horizontal
	{
		ray_dist_along_wall = (int)(cub->player.x + dist_to_ray * cos(ray_angle)) % CELL_SIZE;
	}
	else if (side == 0) // Vertical
	{
		ray_dist_along_wall = (int)(cub->player.y + dist_to_ray * sin(ray_angle)) % CELL_SIZE;
	}
	else 
	{
		error_exit("Bad side :'(");
	}
	ray_dist_along_wall /= CELL_SIZE; // Make percentage of progress along the wall

	int i;
	int j;
	i = 0;
	if (y_end > SCREEN_H)
		y_end = SCREEN_H - 1;
	if (y_start < 0) // y_start + i = 0
		i = -y_start;
	while (y_start + i < y_end && y_end <= SCREEN_H)
	{
		j = 0;
		while (j < (cub->img_game->width / n_rays))
		{
			int texture_x = (int)(ray_dist_along_wall * cub->textures.n->width);
			uint8_t* pixelstart_t = &cub->textures.n->pixels[(((int)(round(i * y_scale) * cub->textures.n->width) + texture_x) * BPP)];
			uint8_t* pixelstart_i = &cub->img_game->pixels[((y_start + i) * cub->img_game->width + (x + j)) * BPP];
			ft_memcpy(pixelstart_i, pixelstart_t, BPP);
			j++;
		}
		i++;
	}
}
