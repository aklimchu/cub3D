/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 09:40:50 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/09 14:58:54 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "../inc/cub3D.h"

void draw_textures(t_cub *cub, float dist_to_ray, int ray_loop, float ray_angle)
{

	float	cosine_angle = cub->player.angle - ray_angle; // right name?
	if (cosine_angle < 0)
		cosine_angle += 2 * M_PI;
	if (cosine_angle > 2 * M_PI)
		cosine_angle -= 2 * M_PI;
	dist_to_ray = dist_to_ray * cos(cosine_angle); // fisheye
	float	wall_height = 64 * 320 / dist_to_ray; // why 64 is best fit?
	if (wall_height > 320)
		wall_height = 320;
	float	wall_offset = 160 - wall_height / 2;
	int x = ray_loop * 8 + 300;
	int y_start = wall_offset + 800;
	int	y_end	= wall_height + wall_offset + 800;
	double y_scale = (double)cub->textures.n->height / wall_height;

	int j;
	j = 0;
	while (y_start + j < y_end)
	{
		uint8_t* pixelstart_t = &cub->textures.n->pixels[(((int)(round(j * y_scale) * cub->textures.n->width) + x) * BPP)];
		uint8_t* pixelstart_i = &cub->img_game->pixels[((y_start + j) * cub->img_game->width + x) * BPP];
		ft_memcpy(pixelstart_i, pixelstart_t, BPP * 8);
		j++;
	}
}
