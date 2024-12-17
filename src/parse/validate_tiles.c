/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 09:16:19 by pleander          #+#    #+#             */
/*   Updated: 2024/12/09 10:34:10 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// static void	check_empty_tile(t_map *map, size_t row, size_t col)
// {
// 	int	i;
// 	int	j;
//
// 	if (row == 0 || row == map->map_rows - 1
// 		|| col == 0 || col == map->map_cols - 1)
// 		error_exit("The map must be surrounded by walls");
// 	i = -1;
// 	while (i < 2)
// 	{
// 		j = -1;
// 		while (j < 2)
// 		{
// 			if (map->map[row + i][col + j] == PADDING)
// 				error_exit("The map must be surrounded by walls");
// 			j++;
// 		}
// 		i++;
// 	}
// }

static void	check_empty_tile(t_map *map, size_t row, size_t col)
{
	int	i;
	int	j;

	if (row == 0 || row == map->map_rows - 1
		|| col == 0 || col == map->map_cols - 1)
		error_exit("The map must be surrounded by walls");
	i = -1;
	while (i < 2)
	{
		j = -1;
		while (j < 2)
		{
			if (abs(i) != abs(j))
			{
				if (map->map[row + i][col + j] == PADDING)
					error_exit("The map must be surrounded by walls");
			}
			j++;
		}
		i++;
	}
}

void	check_tiles(t_map *map)
{
	size_t		i;
	size_t		j;

	i = 0;
	while (i < map->map_rows)
	{
		j = 0;
		while (j < map->map_cols)
		{
			if (map->map[i][j] == EMPTY)
				check_empty_tile(map, i, j);
			j++;
		}
		i++;
	}
}
