/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:42:34 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/16 10:12:15 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "../inc/cub3D.h"

double	check_dist_to_ray(t_coord_f a, t_coord_f b, double angle)
{
	(void)angle;
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

void	iter_loop(t_cub *cub, t_current *h, double *ray_x, double *ray_y)
{
	h->ray_iter = 0;
	h->dist_to_ray = 1000000;
	while (h->ray_iter < cub->iter_limit)
	{
		if (h->r_pos.y < (double)INT_MIN)
			break ;
		h->map_pos.x = (int)h->r_pos.x / CELL_SIZE;
		h->map_pos.y = (int)h->r_pos.y / CELL_SIZE;
		if (h->map_pos.x >= 0 && h->map_pos.y >= 0 && h->map_pos.x < \
			cub->map_size.x && h->map_pos.y < cub->map_size.y && \
			get_tile(h->map_pos.y, h->map_pos.x, cub->map) == WALL)
		{
			*ray_x = h->r_pos.x;
			*ray_y = h->r_pos.y;
			h->dist_to_ray = check_dist_to_ray((t_coord_f){cub->player.x, \
				cub->player.y}, (t_coord_f){(*ray_x), (*ray_y)}, h->ray_angle);
			h->ray_iter = cub->iter_limit;
		}
		else
		{
			h->r_pos.x += h->offset.x;
			h->r_pos.y += h->offset.y;
			h->ray_iter += 1;
		}
	}
}

void	update_no_iter(t_cub *cub, t_current *h)
{
	h->r_pos.x = cub->player.x;
	h->r_pos.y = cub->player.y;
	h->ray_iter = cub->iter_limit;
}
