/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:19:18 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/16 14:18:37 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	handle_awsd(t_cub *cub, double delta_t);
static void	handle_sliding(t_cub *cub, t_coord_f *offset);
static void	check_offset(double dx, double dy, t_coord_f *offset);

void	update_player(t_cub *cub)
{
	double		delta_t;
	t_coord_f	offset;

	cub->player.dx = 0;
	cub->player.dy = 0;
	/* offset.x = MOVEMENT_OFFSET;
	offset.y = MOVEMENT_OFFSET; */
	delta_t = cub->mlx->delta_time;
	if (cub->keys.left)
		cub->player.angle -= ROTATION_SPEED * delta_t;
	if (cub->keys.right)
		cub->player.angle += ROTATION_SPEED * delta_t;
	cub->player.angle = normalize_angle(cub->player.angle);
	handle_awsd(cub, delta_t);
	handle_sliding(cub, &offset);
	check_offset(cub->player.dx, cub->player.dy, &offset);
	if (check_next_tile(cub, cub->player.x + cub->player.dx + offset.x, \
		cub->player.y + cub->player.dy + offset.y) == 0)
	{
		cub->player.x += cub->player.dx;
		cub->player.y += cub->player.dy;
	}
}

static void	handle_awsd(t_cub *cub, double delta_t)
{
	if (cub->keys.w)
	{
		cub->player.dx += cos(cub->player.angle) * PLAYER_SPEED * delta_t;
		cub->player.dy += sin(cub->player.angle) * PLAYER_SPEED * delta_t;
	}
	if (cub->keys.s)
	{
		cub->player.dx -= cos(cub->player.angle) * PLAYER_SPEED * delta_t;
		cub->player.dy -= sin(cub->player.angle) * PLAYER_SPEED * delta_t;
	}
	if (cub->keys.a)
	{
		cub->player.dx += sin(cub->player.angle) * PLAYER_SPEED * delta_t;
		cub->player.dy -= cos(cub->player.angle) * PLAYER_SPEED * delta_t;
	}
	if (cub->keys.d)
	{
		cub->player.dx -= sin(cub->player.angle) * PLAYER_SPEED * delta_t;
		cub->player.dy += cos(cub->player.angle) * PLAYER_SPEED * delta_t;
	}
}

static void	handle_sliding(t_cub *cub, t_coord_f *offset)
{
	double	dy_backup;

	dy_backup = cub->player.dy;
	check_offset(cub->player.dx, cub->player.dy, offset);
	if (check_next_tile(cub, cub->player.x + cub->player.dx + offset->x, \
		cub->player.y + cub->player.dy + offset->y) == 1)
	{
		check_angle(true, &cub->player.dx, &cub->player.dy);
	}
	check_offset(cub->player.dx, cub->player.dy, offset);
	if (check_next_tile(cub, cub->player.x + cub->player.dx + offset->x, \
		cub->player.y + cub->player.dy + offset->y) == 1)
	{
		cub->player.dy = dy_backup;
		check_offset(cub->player.dx, cub->player.dy, offset);
		check_angle(false, &cub->player.dx, &cub->player.dy);
	}
}

// causes issues in corners
static void	check_offset(double dx, double dy, t_coord_f *offset)
{
	if (fabs(dx) < MOVEMENT_OFFSET)
		offset->x = MOVEMENT_OFFSET_MIN;
	else
		offset->x = MOVEMENT_OFFSET;
	if (dx < 0)
		offset->x = (-1) * offset->x;
	if (fabs(dy) < MOVEMENT_OFFSET)
		offset->y = MOVEMENT_OFFSET_MIN;
	else
		offset->y = MOVEMENT_OFFSET;
	if (dy < 0)
		offset->y = (-1) * offset->y;
}