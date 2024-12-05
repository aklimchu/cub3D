/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:24:41 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/05 13:48:14 by aklimchu         ###   ########.fr       */
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
	int	dof; // fields checked???
	
	ray_angle = cub->player.angle - 0.523599;
	if (ray_angle < 0)
		ray_angle += 2 * M_PI;
	if (ray_angle > 2 * M_PI)
		ray_angle -= 2 * M_PI;
	while (i < 60)
	{
		// checking horizontal lines
		dof = 0;
		float	dist_to_ray_horiz = 1000000;
		ray_horiz.x = cub->player.x;
		ray_horiz.y = cub->player.y;
		float	neg_inv_tan = -1 / tan(ray_angle);
		if (ray_angle > M_PI) // looking up
		{
			ray_pos.y = ((((int)cub->player.y / 64) * 64) - 0.0001);
			ray_pos.x = (cub->player.y - ray_pos.y) * neg_inv_tan + cub->player.x;
			offset.y = -64;
			offset.x = -offset.y * neg_inv_tan;
		}
		if (ray_angle < M_PI) // looking down
		{
			ray_pos.y = ((((int)cub->player.y / 64) * 64) + 64);
			ray_pos.x = (cub->player.y - ray_pos.y) * neg_inv_tan + cub->player.x;
			offset.y = 64;
			offset.x = -offset.y * neg_inv_tan;
		}
		if (ray_angle == 0 || ray_angle == M_PI) // looking straight left or right
		{
			ray_pos.x = cub->player.x;
			ray_pos.y = cub->player.y;
			dof = 8;
		}
		while (dof < 8)
		{
			map_pos.x = (int)ray_pos.x / 64;
			map_pos.y = (int)ray_pos.y / 64;
			if (map_pos.x >= 0 && map_pos.y >= 0 && map_pos.x <= cub->map_size.x && \
				map_pos.y <= cub->map_size.y && cub->map.map[map_pos.x][map_pos.y] == 2)
			{
				printf("Wall hit: %d, %d\n", map_pos.x, map_pos.y);
				ray_horiz.x = ray_pos.x;
				ray_horiz.y = ray_pos.y;
				dist_to_ray_horiz = check_dist_to_ray((t_coord_f){cub->player.x, cub->player.y}, \
					ray_horiz, ray_angle);
				dof = 8;
			}
			else
			{
				ray_pos.x += offset.x;
				ray_pos.y += offset.y;
				dof += 1;
			}
		}
		printf("x: %f\n", ray_pos.x);
		printf("y: %f\n", ray_pos.y);
		
		// checking vertical lines
		dof = 0;
		ray_vert.x = cub->player.x;
		ray_vert.y = cub->player.y;
		float	dist_to_ray_vert = 1000000;
		float	neg_tan = -1 * tan(ray_angle);
		if (ray_angle > M_PI / 2 && ray_angle < M_PI * 3 / 2) // looking left
		{
			ray_pos.x = ((((int)cub->player.x / 64) * 64) - 0.0001);
			ray_pos.y = (cub->player.x - ray_pos.x) * neg_tan + cub->player.y;
			offset.x = -64;
			offset.y = -offset.x * neg_tan;
		}
		if (ray_angle < M_PI / 2 || ray_angle > M_PI * 3 / 2) // looking right
		{
			ray_pos.x = ((((int)cub->player.x / 64) * 64) + 64);
			ray_pos.y = (cub->player.x - ray_pos.x) * neg_tan + cub->player.y;
			offset.x = 64;
			offset.y = -offset.x * neg_tan;
		}
		if (ray_angle == 0 || ray_angle == M_PI) // looking straight lup or down
		{
			ray_pos.x = cub->player.x;
			ray_pos.y = cub->player.y;
			dof = 8;
		}
		while (dof < 8)
		{
			map_pos.x = (int)ray_pos.x / 64;
			map_pos.y = (int)ray_pos.y / 64;
			if (map_pos.x >= 0 && map_pos.y >= 0 && map_pos.x <= cub->map_size.x && \
				map_pos.y <= cub->map_size.y && cub->map.map[map_pos.x][map_pos.y] == 2)
			{
				printf("Wall hit: %d, %d\n", map_pos.x, map_pos.y);
				ray_vert.x = ray_pos.x;
				ray_vert.y = ray_pos.y;
				dist_to_ray_vert = check_dist_to_ray((t_coord_f){cub->player.x, cub->player.y}, \
					ray_vert, ray_angle);
				dof = 8;
			}
			else
			{
				ray_pos.x += offset.x;
				ray_pos.y += offset.y;
				dof += 1;
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
			(t_coord_f){ray_pos.x, ray_pos.y}, 0xFF0000FF);
		i++;

		// draw 3D
		draw_game(cub, dist_to_ray_final, i, ray_angle);

		// continue the loop
		ray_angle += DEGREE;
		if (ray_angle < 0)
			ray_angle += 2 * M_PI;
		if (ray_angle > 2 * M_PI)
			ray_angle -= 2 * M_PI;
	}
}