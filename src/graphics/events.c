/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:15:43 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/09 13:50:35 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static int	check_next_tile(t_cub *cub, float x, float y);

void	handle_keypress(struct mlx_key_data key_data, void *input)
{
	t_cub	*cub;
	
	cub = (t_cub *)input;
	int	x_offset, y_offset;
	x_offset = cub->cell_size / 7;
	y_offset = cub->cell_size / 7;
	
	if (key_data.key == MLX_KEY_ESCAPE && key_data.action == MLX_PRESS)
		free_everything(cub, 0);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A) == true && \
		check_next_tile(cub, cub->player.x + cub->player.dy + x_offset, \
			cub->player.y - cub->player.dx - y_offset) == 0)
	{
		cub->player.x += cub->player.dy;
		cub->player.y -= cub->player.dx;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D) == true && \
		check_next_tile(cub, cub->player.x - cub->player.dy - x_offset, \
			cub->player.y + cub->player.dx + y_offset) == 0)
	{
		cub->player.x -= cub->player.dy;
		cub->player.y += cub->player.dx;;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W) == true && \
		check_next_tile(cub, cub->player.x + cub->player.dx + x_offset, \
			cub->player.y + cub->player.dy + y_offset) == 0)
	{
		cub->player.x += cub->player.dx;
		cub->player.y += cub->player.dy;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S) == true && \
		check_next_tile(cub, cub->player.x - cub->player.dx - x_offset, \
			cub->player.y - cub->player.dy - y_offset) == 0)
	{
		cub->player.x -= cub->player.dx;
		cub->player.y -= cub->player.dy;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT) == true)
	{
		cub->player.angle -= 0.1;
		if (cub->player.angle < 0)
			cub->player.angle += 2 * M_PI;
		cub->player.dx = cos(cub->player.angle) * 5;
		cub->player.dy = sin(cub->player.angle) * 5;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT) == true)
	{
		cub->player.angle += 0.1;
		if (cub->player.angle > 2 * M_PI)
			cub->player.angle -= 2 * M_PI;
		cub->player.dx = cos(cub->player.angle) * 5;
		cub->player.dy = sin(cub->player.angle) * 5;
	}
}

static int	check_next_tile(t_cub *cub, float x, float y)
{
	int	x_tile;
	int	y_tile;
	
	printf("x, y, %f, %f\n", x, y);
	x_tile = (int)x / cub->cell_size;
	y_tile = (int)y / cub->cell_size;
	printf("x tile, y tile, %d, %d\n", x_tile, y_tile);
	if (get_tile(y_tile, x_tile, cub->map) == EMPTY || \
		get_tile(y_tile, x_tile, cub->map) == START_NO || \
		get_tile(y_tile, x_tile, cub->map) == START_SO || \
		get_tile(y_tile, x_tile, cub->map) == START_EA || \
		get_tile(y_tile, x_tile, cub->map) == START_WE)
		return (0);
	return (1);
}