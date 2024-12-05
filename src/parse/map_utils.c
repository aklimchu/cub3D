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
		while (map[i][j])
		{
			ft_printf("%s", get_token(map[i][j]));
			j++;
		}
		ft_printf("\n");
		i++;
	}
}
