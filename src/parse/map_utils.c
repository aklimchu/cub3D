/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 09:57:13 by pleander          #+#    #+#             */
/*   Updated: 2024/12/09 09:09:05 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*get_token(t_map_elems tok)
{
	if (tok == EMPTY)
		return (" ");
	else if (tok == WALL)
		return ("#");
	else if (tok == PADDING)
		return ("=");
	else if (tok == START_NO)
		return ("N");
	else if (tok == START_SO)
		return ("S");
	else if (tok == START_WE)
		return ("W");
	else if (tok == START_EA)
		return ("E");
	else if (tok == END_ROW)
		return ("$");
	else
		return ("!ERROR!");
}

void	show_map(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map->map_rows)
	{
		j = 0;
		while (j < map->map_cols)
		{
			ft_printf("%s", get_token(get_tile(i, j, map)));
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

/**
 * @brief Fetches tile information with xy coordinates
 *
 * @param x horizontal coordinate. Grows left.
 * @param y vertical coordinate. Grows down.
 * @param map 
 * @return 
 */
t_map_elems	get_tile_xy(size_t x, size_t y, t_map *map)
{
	if (x > map->map_cols - 1)
		error_exit("get_tile: attemtped read out of bounds");
	if (y > map->map_rows - 1)
		error_exit("get_tile: attemtped read out of bounds");
	return (map->map[y][x]);
}

t_map_elems	get_tile(size_t row, size_t col, t_map *map)
{
	if (col > map->map_cols - 1)
		error_exit("get_tile: attemtped read out of bounds");
	if (row > map->map_rows - 1)
		error_exit("get_tile: attemtped read out of bounds");
	return (map->map[row][col]);
}
