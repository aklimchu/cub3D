/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:24:41 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/12 08:24:55 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void		raycasting_loop(t_cub *cub, float ray_angle, int i, size_t n_rays);
static float	check_horiz(t_cub *cub, float ray_angle, float *ray_x, float *ray_y);
static float	check_vert(t_cub *cub, float ray_angle, float *ray_x, float *ray_y);

void	raycasting(t_cub *cub)
{
	float		ray_angle;	
	size_t		i;
	size_t		n_rays;

	ray_angle = cub->player.angle - 30 * DEGREE;
	if (ray_angle < 0)
		ray_angle += 2 * M_PI;
	if (ray_angle > 2 * M_PI)
		ray_angle -= 2 * M_PI;
	i = 0;
	n_rays = cub->img_game->width / 2;
	while (i < n_rays)
	{
		raycasting_loop(cub, ray_angle, i, n_rays);
		ray_angle += 60 * DEGREE / n_rays;
		if (ray_angle < 0)
			ray_angle += 2 * M_PI;
		if (ray_angle > 2 * M_PI)
			ray_angle -= 2 * M_PI;
		i++;
	}
}

static void	raycasting_loop(t_cub *cub, float ray_angle, int i, size_t n_rays)
{
	t_coord_f	ray_horiz;
	t_coord_f	ray_vert;
	t_coord_f	ray_pos;
	t_coord_f	dist_to_ray;
	float		dist_to_ray_final;
	int			side;
	
	side = -1;
	dist_to_ray.x = check_horiz(cub, ray_angle, &ray_horiz.x, &ray_horiz.y);
	dist_to_ray.y = check_vert(cub, ray_angle, &ray_vert.x, &ray_vert.y);
	if (dist_to_ray.x < dist_to_ray.y)
	{
		dist_to_ray_final = dist_to_ray.x;
		ray_pos.x = ray_horiz.x;
		ray_pos.y = ray_horiz.y;
		side = 1;
	}
	else
	{
		dist_to_ray_final = dist_to_ray.y;
		ray_pos.x = ray_vert.x;
		ray_pos.y = ray_vert.y;
		side = 0;
	}
	//draw_line(cub->img_map, (t_coord_f){cub->player.x, cub->player.y}, \
		(t_coord_f){ray_pos.x, ray_pos.y}, RED);
	draw_textures(cub, dist_to_ray_final, i, ray_angle, side, n_rays);
}

static float	check_horiz(t_cub *cub, float ray_angle, float *ray_x, float *ray_y)
{
	t_current	h;

	*ray_x = cub->player.x;
	*ray_y = cub->player.y;
	h.ray_angle = ray_angle;
	h.neg_inv_tan = -1 / tan(ray_angle);
	if (ray_angle > M_PI) // looking up
	{
		h.ray_pos.y = ((((int)cub->player.y / CELL_SIZE) * CELL_SIZE) - 0.0001);
		h.ray_pos.x = (cub->player.y - h.ray_pos.y) * h.neg_inv_tan + cub->player.x;
		h.offset.y = -1 * CELL_SIZE;
		h.offset.x = -1 * h.offset.y * h.neg_inv_tan;
	}
	if (ray_angle < M_PI) // looking down
	{
		h.ray_pos.y = ((((int)cub->player.y / CELL_SIZE) * CELL_SIZE) + CELL_SIZE);
		h.ray_pos.x = (cub->player.y - h.ray_pos.y) * h.neg_inv_tan + cub->player.x;
		h.offset.y = CELL_SIZE;
		h.offset.x = -1 * h.offset.y * h.neg_inv_tan;
	}
	if (fabs(ray_angle) < 0.01 || fabs(ray_angle - M_PI) < 0.01) // looking straight left or right
		update_no_iter(cub, &h);
	iter_loop(cub, &h, ray_x, ray_y);
	return (h.dist_to_ray);
}

static float	check_vert(t_cub *cub, float ray_angle, float *ray_x, float *ray_y)
{
	t_current	v;
	
	v.ray_iter = 0;
	*ray_x = cub->player.x;
	*ray_y = cub->player.y;
	v.dist_to_ray = 1000000;
	v.neg_tan = -1 * tan(ray_angle);
	if (ray_angle > M_PI / 2 && ray_angle < M_PI * 3 / 2) // looking left
	{
		v.ray_pos.x = ((((int)cub->player.x / CELL_SIZE) * CELL_SIZE) - 0.0001);
		v.ray_pos.y = (cub->player.x - v.ray_pos.x) * v.neg_tan + cub->player.y;
		v.offset.x = -1 * CELL_SIZE;
		v.offset.y = -1 * v.offset.x * v.neg_tan;
	}
	if (ray_angle < M_PI / 2 || ray_angle > M_PI * 3 / 2) // looking right
	{
		v.ray_pos.x = ((((int)cub->player.x / CELL_SIZE) * CELL_SIZE) + CELL_SIZE);
		v.ray_pos.y = (cub->player.x - v.ray_pos.x) * v.neg_tan + cub->player.y;
		v.offset.x = CELL_SIZE;
		v.offset.y = -1 * v.offset.x * v.neg_tan;
	}
	if (fabs(ray_angle - M_PI / 2) < 0.01 || fabs(ray_angle - 3 * M_PI / 2) < 0.01) // looking straight up or down
		update_no_iter(cub, &v);
	iter_loop(cub, &v, ray_x, ray_y);
	return(v.dist_to_ray);
}
