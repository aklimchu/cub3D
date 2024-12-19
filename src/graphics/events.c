/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:15:43 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/17 13:52:10 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static int	valid_tile(size_t col, size_t row, t_map *map);

void	handle_keypress(struct mlx_key_data key_data, void *input)
{
	t_cub	*cub;

	cub = (t_cub *)input;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE) == true)
		free_everything(cub, EXIT_SUCCESS);
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

int	check_next_tile(t_cub *cub, t_coord_f cur, t_coord_f next)
{
	t_coord	cur_tile;
	t_coord	next_tile;
	t_coord	tiles_diff;

	cur_tile.x = (int)cur.x / CELL_SIZE;
	cur_tile.y = (int)cur.y / CELL_SIZE;
	next_tile.x = (int)next.x / CELL_SIZE;
	next_tile.y = (int)next.y / CELL_SIZE;
	tiles_diff.x = next_tile.x - cur_tile.x;
	tiles_diff.y = next_tile.y - cur_tile.y;
	if (tiles_diff.x && tiles_diff.y)
	{
		if (valid_tile(next_tile.x, cur_tile.y, cub->map) == 1 || \
			(valid_tile(cur_tile.x, next_tile.y, cub->map) == 1))
			return (1);
	}
	return (valid_tile(next_tile.x, next_tile.y, cub->map));
}

static int	valid_tile(size_t col, size_t row, t_map *map)
{
	int		tile_name;

	tile_name = get_tile(row, col, map);
	if (tile_name == EMPTY || tile_name == START_NO || \
		tile_name == START_SO || tile_name == START_EA || tile_name == START_WE)
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
