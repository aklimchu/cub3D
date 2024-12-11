/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:24:41 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/11 13:29:18 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static float	check_dist_to_ray(t_coord_f a, t_coord_f b, float angle)
{
	(void)angle;
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

void	raycasting(t_cub *cub)
{
	t_coord_f	offset;
	t_coord_f	ray_pos;
	t_coord_f	ray_horiz;
	t_coord_f	ray_vert;
	t_coord		map_pos;
	float		ray_angle;
	float		dist_to_ray_final;
	int	i = 0;
	int	ray_iter;
	
	ray_angle = cub->player.angle - 0.523599; // 30 degrees
	if (ray_angle < 0)
		ray_angle += 2 * M_PI;
	if (ray_angle > 2 * M_PI)
		ray_angle -= 2 * M_PI;
	while (i < 60)
	{
		// checking horizontal lines
		ray_iter = 0;
		float	dist_to_ray_horiz = 1000000;
		ray_horiz.x = cub->player.x;
		ray_horiz.y = cub->player.y;
		float	neg_inv_tan = -1 / tan(ray_angle);
		if (ray_angle > M_PI) // looking up
		{
			ray_pos.y = ((((int)cub->player.y / cub->cell_size) * cub->cell_size) - 0.0001);
			ray_pos.x = (cub->player.y - ray_pos.y) * neg_inv_tan + cub->player.x;
			offset.y = -1 * cub->cell_size;
			offset.x = -offset.y * neg_inv_tan;
		}
		if (ray_angle < M_PI) // looking down
		{
			ray_pos.y = ((((int)cub->player.y / cub->cell_size) * cub->cell_size) + cub->cell_size);
			ray_pos.x = (cub->player.y - ray_pos.y) * neg_inv_tan + cub->player.x;
			offset.y = cub->cell_size;
			offset.x = -offset.y * neg_inv_tan;
		}
		if (ray_angle == 0 || ray_angle == M_PI) // looking straight left or right
		{
			ray_pos.x = cub->player.x;
			ray_pos.y = cub->player.y;
			ray_iter = cub->iter_limit;
		}
		while (ray_iter < cub->iter_limit)
		{
			map_pos.x = (int)ray_pos.x / cub->cell_size;
			map_pos.y = (int)ray_pos.y / cub->cell_size;
			if (map_pos.x >= 0 && map_pos.y >= 0 && map_pos.x < cub->map_size.x && \
				map_pos.y < cub->map_size.y && get_tile(map_pos.y, map_pos.x, cub->map) == WALL) // or equal?
			{
				ray_horiz.x = ray_pos.x;
				ray_horiz.y = ray_pos.y;
				dist_to_ray_horiz = check_dist_to_ray((t_coord_f){cub->player.x, cub->player.y}, \
					ray_horiz, ray_angle);
				ray_iter = cub->iter_limit;
			}
			else
			{
				ray_pos.x += offset.x;
				ray_pos.y += offset.y;
				ray_iter += 1;
			}
		}
		
		// checking vertical lines
		ray_iter = 0;
		ray_vert.x = cub->player.x;
		ray_vert.y = cub->player.y;
		float	dist_to_ray_vert = 1000000;
		float	neg_tan = -1 * tan(ray_angle);
		if (ray_angle > M_PI / 2 && ray_angle < M_PI * 3 / 2) // looking left
		{
			ray_pos.x = ((((int)cub->player.x / cub->cell_size) * cub->cell_size) - 0.0001);
			ray_pos.y = (cub->player.x - ray_pos.x) * neg_tan + cub->player.y;
			offset.x = -1 * cub->cell_size;
			offset.y = -offset.x * neg_tan;
		}
		if (ray_angle < M_PI / 2 || ray_angle > M_PI * 3 / 2) // looking right
		{
			ray_pos.x = ((((int)cub->player.x / cub->cell_size) * cub->cell_size) + cub->cell_size);
			ray_pos.y = (cub->player.x - ray_pos.x) * neg_tan + cub->player.y;
			offset.x = cub->cell_size;
			offset.y = -offset.x * neg_tan;
		}
		if (ray_angle == 0 || ray_angle == M_PI) // looking straight lup or down
		{
			ray_pos.x = cub->player.x;
			ray_pos.y = cub->player.y;
			ray_iter = cub->iter_limit;
		}
		while (ray_iter < cub->iter_limit)
		{
			map_pos.x = (int)ray_pos.x / cub->cell_size;
			map_pos.y = (int)ray_pos.y / cub->cell_size;
			if (map_pos.x >= 0 && map_pos.y >= 0 && map_pos.x < cub->map_size.x && \
				map_pos.y < cub->map_size.y && get_tile(map_pos.y, map_pos.x, cub->map) == WALL) // or equal?
			{
				ray_vert.x = ray_pos.x;
				ray_vert.y = ray_pos.y;
				dist_to_ray_vert = check_dist_to_ray((t_coord_f){cub->player.x, cub->player.y}, \
					ray_vert, ray_angle);
				ray_iter = cub->iter_limit;
			}
			else
			{
				ray_pos.x += offset.x;
				ray_pos.y += offset.y;
				ray_iter += 1;
			}
		}
		if (dist_to_ray_horiz < dist_to_ray_vert)
		{
			dist_to_ray_final = dist_to_ray_horiz;
			ray_pos.x = ray_horiz.x;
			ray_pos.y = ray_horiz.y;
		}
		if (dist_to_ray_vert < dist_to_ray_horiz)
		{
			dist_to_ray_final = dist_to_ray_vert;
			ray_pos.x = ray_vert.x;
			ray_pos.y = ray_vert.y;
		}
		draw_line(cub->img_map, (t_coord_f){cub->player.x, cub->player.y}, \
			(t_coord_f){ray_pos.x, ray_pos.y}, RED);
		i++;

		// draw 3D
		draw_textures(cub, dist_to_ray_final, i, ray_angle);

		// continue the loop
		ray_angle += DEGREE;
		if (ray_angle < 0)
			ray_angle += 2 * M_PI;
		if (ray_angle > 2 * M_PI)
			ray_angle -= 2 * M_PI;
	}
}