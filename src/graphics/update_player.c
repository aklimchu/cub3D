/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:19:18 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/17 10:53:46 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	handle_awsd(t_cub *cub, double delta_t);
static void	handle_sliding(t_cub *cub);

void	update_player(t_cub *cub)
{
	double		delta_t;

	cub->player.dx = 0;
	cub->player.dy = 0;
	delta_t = cub->mlx->delta_time;
	if (cub->keys.left)
		cub->player.angle -= ROTATION_SPEED * delta_t;
	if (cub->keys.right)
		cub->player.angle += ROTATION_SPEED * delta_t;
	cub->player.angle = normalize_angle(cub->player.angle);
	handle_awsd(cub, delta_t);
	handle_sliding(cub);
	if (check_next_tile(cub, (t_coord_f){cub->player.x, cub->player.y}, \
		(t_coord_f){cub->player.x + cub->player.dx, \
		cub->player.y + cub->player.dy}) == 0)
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

static void	handle_sliding(t_cub *cub)
{
	double	dy_backup;

	dy_backup = cub->player.dy;
	if (check_next_tile(cub, (t_coord_f){cub->player.x, cub->player.y}, \
		(t_coord_f){cub->player.x + cub->player.dx, \
		cub->player.y + cub->player.dy}) == 1)
	{
		check_angle(true, &cub->player.dx, &cub->player.dy);
	}
	if (check_next_tile(cub, (t_coord_f){cub->player.x, cub->player.y}, \
		(t_coord_f){cub->player.x + cub->player.dx, \
		cub->player.y + cub->player.dy}) == 1)
	{
		cub->player.dy = dy_backup;
		check_angle(false, &cub->player.dx, &cub->player.dy);
	}
}
