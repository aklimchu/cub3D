/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:17:51 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/11 13:24:50 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static double	find_angle_and_player(t_map *map, t_cub *cub);

void	initialize_values(t_cub *cub)
{
	cub->map_size.x = cub->map->map_cols;
	cub->map_size.y = cub->map->map_rows;
	if (cub->map->map_cols > cub->map->map_rows)
	{
		cub->iter_limit = cub->map->map_cols;
		//cub->cell_size = SCREEN_W / 2 / cub->map->map_cols; // what if too small tiles?
	}
	else
	{
		cub->iter_limit = cub->map->map_rows;
		//cub->cell_size = SCREEN_W / 2 / cub->map->map_rows; // what if too small tiles?
	}
	cub->player.angle = find_angle_and_player(cub->map, cub);
	
	double	fps;

	fps = 1000 / cub->mlx->delta_time;
	cub->player.dx = cos(cub->player.angle) * /* 0.2 * fps */5;
	cub->player.dy = sin(cub->player.angle) * /* 0.2 * fps */5;
}

static double	find_angle_and_player(t_map *map, t_cub *cub)
{
	cub->player.y = (map->player_start.x + 0.5) * CELL_SIZE; // get tile number from parsing
	cub->player.x = (map->player_start.y + 0.5) * CELL_SIZE; // get tile number from parsing
	if (get_tile(map->player_start.x, map->player_start.y, map) == START_NO)
		return (3 * M_PI / 2);
	if (get_tile(map->player_start.x, map->player_start.y, map) == START_SO)
		return (M_PI / 2);
	if (get_tile(map->player_start.x, map->player_start.y, map) == START_WE)
		return (M_PI);
	if (get_tile(map->player_start.x, map->player_start.y, map) == START_EA)
		return (0);
	return (0);
}

void	draw_map(t_cub *cub)
{
	size_t	i;
	size_t	j;
	t_coord	current;

	i = 0;
	current.y = 0;
	while (i < cub->map->map_rows)
	{
		current.x = 0;
		j = 0;
		while (j < cub->map->map_cols)
		{
			// Fill rectangle
			if (get_tile(i, j, cub->map) == WALL)
			{
				fill_rect(cub->img_map, (t_rect){current.x + 1, current.y + 1, CELL_SIZE - 2, \
					CELL_SIZE - 2, BLUE});
			}
			// Draw cell border
			if (get_tile(i, j, cub->map) == EMPTY || get_tile(i, j, cub->map) == WALL)
				draw_rect(cub->img_map, (t_rect){current.x, current.y, CELL_SIZE, \
					CELL_SIZE, LIGHT_BLUE});
			j++;
			current.x += CELL_SIZE;
		}
		i++;
		current.y += CELL_SIZE;
	}
}


