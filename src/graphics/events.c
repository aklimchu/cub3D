/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:15:43 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/16 14:16:15 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	handle_keypress(struct mlx_key_data key_data, void *input)
{
	t_cub	*cub;
	bool	key_bool;

	cub = (t_cub *)input;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE) == true)
		free_everything(cub, 0);
	if (key_data.key == MLX_KEY_W)
		cub->keys.w = (key_data.action == MLX_PRESS || \
			key_data.action == MLX_REPEAT);
	if (key_data.key == MLX_KEY_A)
		cub->keys.a = (key_data.action == MLX_PRESS || \
			key_data.action == MLX_REPEAT);
	if (key_data.key == MLX_KEY_S)
		cub->keys.s = (key_data.action == MLX_PRESS || \
			key_data.action == MLX_REPEAT);
	if (key_data.key == MLX_KEY_D)
		cub->keys.d = (key_data.action == MLX_PRESS || \
			key_data.action == MLX_REPEAT);
	if (key_data.key == MLX_KEY_LEFT)
		cub->keys.left = (key_data.action == MLX_PRESS || \
			key_data.action == MLX_REPEAT);
	if (key_data.key == MLX_KEY_RIGHT)
		cub->keys.right = (key_data.action == MLX_PRESS || \
			key_data.action == MLX_REPEAT);
}

int	check_next_tile(t_cub *cub, double x, double y)
{
	int	x_tile;
	int	y_tile;
	int	tile;

	x_tile = (int)x / CELL_SIZE;
	y_tile = (int)y / CELL_SIZE;
	tile = get_tile(y_tile, x_tile, cub->map);
	if (tile == EMPTY || tile == START_NO || \
		tile == START_SO || tile == START_EA || tile == START_WE)
		return (0);
	return (1);
}

void	check_angle(bool x_dir, double *dx, double *dy)
{
	if (x_dir == true)
		*dy = 0;
	else
		*dx = 0;
}
