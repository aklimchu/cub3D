/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:24:41 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/05 11:59:55 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	raycasting(t_cub *cub)
{
	t_coord_f	offset;
	t_coord_f	ray_pos;
	t_coord		map_pos;
	float	ray_angle = cub->player.angle;
	int	r = 0;
	int	dof; // ???
	
	dof = 0;
	while (r < 1)
	{
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
		if (ray_angle == 0 || ray_angle == M_PI)
		{
			ray_pos.x = cub->player.x;
			ray_pos.y = cub->player.y;
			dof = 8;
		}
		while (dof < 8)
		{
			map_pos.x = (int)ray_pos.x / 64;
			map_pos.y = (int)ray_pos.y / 64;
			if (map_pos.y * cub->map_size.x + map_pos.x < cub->map_size.x * cub->map_size.y && \
				cub->map[map_pos.y * cub->map_size.x + map_pos.x] == 1) // wall hit
			{
				printf("Wall hit: %d\n", map_pos.y * cub->map_size.x + map_pos.x);
				dof = 8;
			}
			else
			{
				ray_pos.x += offset.x;
				ray_pos.y += offset.y;
				dof += 1;
			}
			//draw_line(cub->img, (t_coord_f){cub->player.x, cub->player.y}, (t_coord_f){ray_pos.x, ray_pos.y});
		}
		printf("x: %f\n", ray_pos.x);
		printf("y: %f\n", ray_pos.y);
		r++;
	}
}