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

	float	angle_diff = cub->player.angle - ray_angle; // right name?
	if (angle_diff < 0)
		angle_diff += 2 * M_PI;
	if (angle_diff > 2 * M_PI)
		angle_diff -= 2 * M_PI;
	dist_to_ray = dist_to_ray * cos(angle_diff); // fisheye
	float	wall_height = 64 * 320 / dist_to_ray; // should it be cell_size instead of 64?
	if (wall_height > 320)
		wall_height = 320;
	float	wall_offset = 320 / 2 - wall_height / 2;
	int x = ray_loop * (cub->img_game->width / n_rays);
	int y_start = wall_offset + 800;
	int	y_end	= wall_height + wall_offset + 800;
	double y_scale = (double)cub->textures.n->height / wall_height;
	double ray_dist_along_wall = 0;

	if (side == 1) // Horizontal
	{
		ray_dist_along_wall = (int)(cub->player.x + dist_to_ray * cos(ray_angle)) % 64;
	}
	else if (side == 0) // Vertical
	{
		ray_dist_along_wall = (int)(cub->player.y + dist_to_ray * sin(ray_angle)) % 64;
	}
	else 
	{
		error_exit("Bad side :'(");
	}
	ray_dist_along_wall /= 64; // Make percentage of progress along the wall

	int i;
	int j;
	i = 0;
	while (y_start + i < y_end)
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
