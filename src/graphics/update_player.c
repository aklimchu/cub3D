/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:19:18 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/16 11:56:48 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	update_player(t_cub *cub)
{
	cub->player.dx = 0;
   cub->player.dy = 0;

	// Handle forward/backward movement
    if (cub->keys.w) {
        cub->player.dx += cos(cub->player.angle) * PLAYER_SPEED; // fps?
        cub->player.dy += sin(cub->player.angle) * PLAYER_SPEED;
    }
    if (cub->keys.s) {
        cub->player.dx -= cos(cub->player.angle) * PLAYER_SPEED;
        cub->player.dy -= sin(cub->player.angle) * PLAYER_SPEED;
    }

    // Handle strafing (left/right movement)
    if (cub->keys.a) {
        cub->player.dx += sin(cub->player.angle) * PLAYER_SPEED;
        cub->player.dy -= cos(cub->player.angle) * PLAYER_SPEED;
    }
    if (cub->keys.d) {
        cub->player.dx -= sin(cub->player.angle) * PLAYER_SPEED;
        cub->player.dy += cos(cub->player.angle) * PLAYER_SPEED;
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

    // Handle rotation
    if (cub->keys.left)
        cub->player.angle -= ROTATION_SPEED;
    if (cub->keys.right)
        cub->player.angle += ROTATION_SPEED;
    cub->player.angle = normalize_angle(cub->player.angle);
}