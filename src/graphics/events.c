/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:15:43 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/04 11:25:04 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	handle_keypress(struct mlx_key_data key_data, void *input)
{
	t_cub	*cub;
	
	cub = (t_cub *)input;
	if (key_data.key == MLX_KEY_ESCAPE && key_data.action == MLX_PRESS)
		free_everything(cub->img, cub, 0);
	if (key_data.key == MLX_KEY_A)
		cub->player.x -= cub->player.dx;
	if (key_data.key == MLX_KEY_D)
		cub->player.x += cub->player.dx;
	if (key_data.key == MLX_KEY_W)
		cub->player.y -= cub->player.dy;
	if (key_data.key == MLX_KEY_S)
		cub->player.y += cub->player.dy;
	if (key_data.key == MLX_KEY_LEFT)
	{
		cub->player.angle -= 0.1;
		if (cub->player.angle < 0)
			cub->player.angle += 2 * M_PI;
		/* cub->player.dx = cos(cub->player.angle) * 5;
		cub->player.dy = sin(cub->player.angle) * 5; */
	}
	if (key_data.key == MLX_KEY_RIGHT)
	{
		cub->player.angle += 0.1;
		if (cub->player.angle > 2 * M_PI)
			cub->player.angle -= 2 * M_PI;
		/* cub->player.dx = cos(cub->player.angle) * 5;
		cub->player.dy = sin(cub->player.angle) * 5; */
	}
}
