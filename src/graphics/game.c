/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 09:40:50 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/09 13:01:32 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	draw_line(cub->img_game, (t_coord_f){ray_loop * 8 + 300, wall_offset + 800}, \
		(t_coord_f){ray_loop * 8 + 300, wall_height + wall_offset + 800}, 0x008000FF);
	
	
}