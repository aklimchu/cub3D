/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:19:18 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/16 13:15:27 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	update_player(t_cub *cub)
{
	cub->player.dx = 0;
	cub->player.dy = 0;

    double delta_t = cub->mlx->delta_time;
	// Handle forward/backward movement
    // Handle rotation
    if (cub->keys.left)
        cub->player.angle -= ROTATION_SPEED * delta_t;
    if (cub->keys.right)
        cub->player.angle += ROTATION_SPEED * delta_t;
    cub->player.angle = normalize_angle(cub->player.angle);
    if (cub->keys.w) {
        cub->player.dx += cos(cub->player.angle) * PLAYER_SPEED * delta_t; // fps?
        cub->player.dy += sin(cub->player.angle) * PLAYER_SPEED * delta_t;
    }
    if (cub->keys.s) {
        cub->player.dx -= cos(cub->player.angle) * PLAYER_SPEED * delta_t;
        cub->player.dy -= sin(cub->player.angle) * PLAYER_SPEED * delta_t;
    }

    // Handle strafing (left/right movement)
    if (cub->keys.a) {
        cub->player.dx += sin(cub->player.angle) * PLAYER_SPEED * delta_t;
        cub->player.dy -= cos(cub->player.angle) * PLAYER_SPEED * delta_t;
    }
    if (cub->keys.d) {
        cub->player.dx -= sin(cub->player.angle) * PLAYER_SPEED * delta_t;
        cub->player.dy += cos(cub->player.angle) * PLAYER_SPEED * delta_t;
    }

	if (check_next_tile(cub, cub->player.x + cub->player.dx, \
		cub->player.y + cub->player.dy) == 1)
	{
		check_angle(cub, true, &cub->player.dx, &cub->player.dy);
	}
	if (check_next_tile(cub, cub->player.x + cub->player.dx, \
		cub->player.y + cub->player.dy) == 1)
	{
		check_angle(cub, false, &cub->player.dx, &cub->player.dy);
	}

    // Update position if the new tile is valid
    if (check_next_tile(cub, cub->player.x + cub->player.dx, cub->player.y + cub->player.dy) == 0) {
        cub->player.x += cub->player.dx;
        cub->player.y += cub->player.dy;
    }
}