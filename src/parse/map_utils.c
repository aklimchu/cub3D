/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 09:57:13 by pleander          #+#    #+#             */
/*   Updated: 2024/12/05 10:26:09 by pleander         ###   ########.fr       */
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

void	show_map(t_map_elems **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] != END_ROW)
		{
			ft_printf("%s", get_token(map[i][j]));
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

t_map_elems	get_tile(size_t row, size_t col, t_map *map)
{
	if (col > map->map_cols - 1 || col < 0)
		error_exit("get_tile: attemtped read out of bounds");
	if (row > map->map_rows - 1 || row < 0)
		error_exit("get_tile: attemtped read out of bounds");
	return (map->map[row][col]);
}
