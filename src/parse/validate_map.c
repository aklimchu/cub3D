/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:40:34 by pleander          #+#    #+#             */
/*   Updated: 2024/12/17 12:35:16 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_start_location(t_map_elems tok)
{
	if (tok == START_NO || tok == START_SO
		|| tok == START_WE || tok == START_EA)
		return (1);
	return (0);
}

static void	find_player_start(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map->map_rows)
	{
		j = 0;
		while (j < map->map_cols)
		{
			if (is_start_location((get_tile(i, j, map))))
			{
				if (map->player_start.x != -1)
					error_exit("Too many starting locations for player");
				map->player_start.x = i;
				map->player_start.y = j;
			}
			j++;
		}
		i++;
	}
	if (map->player_start.x == -1 || map->player_start.y == -1)
		error_exit("Player start location missing");
}

static void	check_player_inside_map(t_map *map)
{
	int		i;
	int		j;
	t_coord	s;

	s = map->player_start;
	i = map->player_start.x - 1;
	while (i < map->player_start.x + 1)
	{
		j = map->player_start.y - 1;
		if (i < 0 || i >= (int)map->map_rows - 1)
			error_exit("Player is on the edge of the map");
		while (j < map->player_start.y + 1)
		{
			if (j < 0 || j >= (int)map->map_cols - 1)
				error_exit("Player is on the edge of the map");
			if (map->map[i][j] == PADDING)
				error_exit("Player start is outside the map");
			j++;
		}
		i++;
	}
}

void	check_map(t_map *map)
{
	if (!map->map || !*map->map)
		error_exit("The map is missing from the cub-file");
	find_player_start(map);
	check_player_inside_map(map);
	check_tiles(map);
}
