/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:17:51 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/05 15:00:41 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static float	find_angle_and_player(t_map *map, t_cub *cub);

void	initialize_values(t_cub *cub)
{
	cub->cell_size.x = 30; // was 64
	cub->cell_size.y = 30; // was 64
	cub->map_size.x = cub->map->map_cols;
	cub->map_size.y = cub->map->map_rows;
	cub->player.angle = find_angle_and_player(cub->map, cub);
	cub->player.dx = cos(cub->player.angle) * 5;
	cub->player.dy = sin(cub->player.angle) * 5;
}

static float	find_angle_and_player(t_map *map, t_cub *cub)
{
	cub->player.y = (5 + 0.5) * cub->cell_size.y; // get tile number from parsing
	cub->player.x = (12 + 0.5) * cub->cell_size.x; // get tile number from parsing
	if (get_tile(5, 12, map) == START_NO)
		return (0);
	if (get_tile(5, 12, map) == START_SO)
		return (M_PI);
	if (get_tile(5, 12, map) == START_WE)
		return (3 * M_PI / 2);
	if (get_tile(5, 12, map) == START_EA)
		return (M_PI / 2);
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


