/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:17:51 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/05 14:29:12 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static float	find_angle_and_player(t_map *map, t_cub *cub);

void	initialize_values(t_cub *cub)
{
	cub->map_size.x = cub->map->map_cols;
	cub->map_size.y = cub->map->map_rows;
	cub->player.angle = find_angle_and_player(cub->map, cub);
	cub->player.dx = cos(cub->player.angle) * 5;
	cub->player.dy = sin(cub->player.angle) * 5;
	cub->cell_size.x = 64;
	cub->cell_size.y = 64;
}

static float	find_angle_and_player(t_map *map, t_cub *cub)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map->map_rows)
	{
		j = 0;
		while (j < map->map_cols)
		{
			if (get_tile(i, j, map) == START_NO || get_tile(i, j, map) == START_SO ||\
				get_tile(i, j, map) == START_WE || get_tile(i, j, map) == START_EA)
				break ;
			j++;
		}
		i++;
	}
	printf("size of map %zu, %zu\n", map->map_rows , map->map_cols);
	printf("player found in tile %zu, %zu\n", i , j);
	cub->player.y = (i + 0.5) * cub->cell_size.y;
	cub->player.x = (j + 0.5) * cub->cell_size.x;
	if (get_tile(i, j, map) == START_NO)
		return (0);
	if (get_tile(i, j, map) == START_SO)
		return (M_PI);
	if (get_tile(i, j, map) == START_WE)
		return (3 * M_PI / 2);
	if (get_tile(i, j, map) == START_EA)
		return (M_PI / 2);
	return (-1);
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
				fill_rect(cub->img_map, (t_rect){current.x + 1, current.y + 1, cub->cell_size.x - 2, \
					cub->cell_size.y - 2, 0x0000FFFF});
			}
			// Draw cell border
			if (get_tile(i, j, cub->map) == EMPTY || get_tile(i, j, cub->map) == WALL)
				draw_rect(cub->img_map, (t_rect){current.x, current.y, cub->cell_size.x, \
					cub->cell_size.y, 0x00FFFFFF});
			j++;
			current.x += cub->cell_size.x;
		}
		i++;
		current.y += cub->cell_size.y;
	}
}


