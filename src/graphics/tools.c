/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:17:51 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/16 13:35:54 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static double	find_angle_and_player(t_map *map, t_cub *cub);

void	initialize_values(t_cub *cub)
{
	cub->map_size.x = cub->map->map_cols;
	cub->map_size.y = cub->map->map_rows;
	if (cub->map->map_cols > cub->map->map_rows)
		cub->iter_limit = cub->map->map_cols;
	else
		cub->iter_limit = cub->map->map_rows;
	cub->player.angle = find_angle_and_player(cub->map, cub);
	ft_memset(&cub->keys, false, sizeof(cub->keys));
	cub->n_rays = cub->img_game->width / 2;
	cub->vertical_lines = cub->img_game->width / cub->n_rays;
}

static double	find_angle_and_player(t_map *map, t_cub *cub)
{
	int	tile;

	cub->player.y = (map->player_start.x + 0.5) * CELL_SIZE;
	cub->player.x = (map->player_start.y + 0.5) * CELL_SIZE;
	tile = get_tile(map->player_start.x, map->player_start.y, map);
	if (tile == START_NO)
		return (3 * M_PI / 2);
	if (tile == START_SO)
		return (M_PI / 2);
	if (tile == START_WE)
		return (M_PI);
	if (tile == START_EA)
		return (0);
	return (0);
}

double	normalize_angle(double angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

void	draw_cell(t_cub *cub, t_coord cell, t_coord_f current)
{
	int	tile;

	tile = get_tile(cell.y, cell.x, cub->map);
	if (tile == WALL)
	{
		fill_rect(cub->img_map, (t_rect){current.x + 1, current.y + 1, \
			MAP_CELL_SIZE - 2, MAP_CELL_SIZE - 2, BLUE});
	}
	if (tile == EMPTY || tile == WALL)
	{
		draw_rect(cub->img_map, (t_rect){current.x, current.y, MAP_CELL_SIZE, \
			MAP_CELL_SIZE, LIGHT_BLUE});
	}
}
