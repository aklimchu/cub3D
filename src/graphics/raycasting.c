/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:24:41 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/17 11:03:44 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void		ray_loop(t_cub *cub, double ray_angle, int i);
static double	check_horiz(t_cub *c, double r_angle, double *r_x, double *r_y);
static double	check_vert(t_cub *c, double r_angle, double *r_x, double *r_y);

void	raycasting(t_cub *cub)
{
	double	ray_angle;	
	size_t	i;
	double	viewport;

	ray_angle = cub->player.angle - 30 * DEGREE;
	ray_angle = normalize_angle(ray_angle);
	i = 0;
	viewport = 60 * DEGREE;
	while (i < cub->n_rays)
	{
		ray_loop(cub, ray_angle, i);
		ray_angle += viewport / cub->n_rays;
		ray_angle = normalize_angle(ray_angle);
		i++;
	}
}

static void	ray_loop(t_cub *cub, double ray_angle, int i)
{
	t_coord_f	ray_horiz;
	t_coord_f	ray_vert;
	t_coord_f	r_pos;
	t_coord_f	dist_to_ray;
	double		dist_to_ray_final;
	int			side;

	side = -1;
	dist_to_ray.x = check_horiz(cub, ray_angle, &ray_horiz.x, &ray_horiz.y);
	dist_to_ray.y = check_vert(cub, ray_angle, &ray_vert.x, &ray_vert.y);
	if (dist_to_ray.x < dist_to_ray.y)
	{
		dist_to_ray_final = dist_to_ray.x;
		r_pos.x = ray_horiz.x;
		r_pos.y = ray_horiz.y;
		side = 1;
	}
	else
	{
		dist_to_ray_final = dist_to_ray.y;
		r_pos.x = ray_vert.x;
		r_pos.y = ray_vert.y;
		side = 0;
	}
	draw_game(cub, (t_draw_context){dist_to_ray_final, ray_angle, i, side});
}

static double	check_horiz(t_cub *c, double r_angle, double *r_x, double *r_y)
{
	t_current	h;

	h.ray_iter = 0;
	*r_x = (double)c->player.x;
	*r_y = (double)c->player.y;
	h.ray_angle = r_angle;
	h.neg_inv_tan = -1 / tan(r_angle);
	if (r_angle > M_PI)
	{
		h.r_pos.y = ((floor(c->player.y / CELL_SIZE) * CELL_SIZE) - 0.0001);
		h.r_pos.x = (c->player.y - h.r_pos.y) * h.neg_inv_tan + c->player.x;
		h.offset.y = -1 * CELL_SIZE;
		h.offset.x = -1 * h.offset.y * h.neg_inv_tan;
	}
	else
	{
		h.r_pos.y = ((floor(c->player.y / CELL_SIZE) * CELL_SIZE) + \
			CELL_SIZE);
		h.r_pos.x = (c->player.y - h.r_pos.y) * h.neg_inv_tan + c->player.x;
		h.offset.y = CELL_SIZE;
		h.offset.x = -1 * h.offset.y * h.neg_inv_tan;
	}
	if (fabs(r_angle) < 0.0001 || fabs(r_angle - M_PI) < 0.0001)
		update_no_iter(c, &h);
	iter_loop(c, &h, r_x, r_y);
	return (h.dist_to_ray);
}

static double	check_vert(t_cub *c, double r_angle, double *r_x, double *r_y)
{
	t_current	v;

	v.ray_iter = 0;
	*r_x = c->player.x;
	*r_y = c->player.y;
	v.dist_to_ray = 1000000;
	v.neg_tan = -1 * tan(r_angle);
	if (r_angle > M_PI / 2 && r_angle < M_PI * 3 / 2)
	{
		v.r_pos.x = ((floor(c->player.x / CELL_SIZE) * CELL_SIZE) - 0.0001);
		v.r_pos.y = (c->player.x - v.r_pos.x) * v.neg_tan + c->player.y;
		v.offset.x = -1 * CELL_SIZE;
		v.offset.y = -1 * v.offset.x * v.neg_tan;
	}
	else
	{
		v.r_pos.x = ((floor(c->player.x / CELL_SIZE) * CELL_SIZE) + CELL_SIZE);
		v.r_pos.y = (c->player.x - v.r_pos.x) * v.neg_tan + c->player.y;
		v.offset.x = CELL_SIZE;
		v.offset.y = -1 * v.offset.x * v.neg_tan;
	}
	if (fabs(r_angle - M_PI / 2) < 0.0001 || fabs(r_angle - 3 * M_PI / 2) < 0.0001)
		update_no_iter(c, &v);
	iter_loop(c, &v, r_x, r_y);
	return (v.dist_to_ray);
}
