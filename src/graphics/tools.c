/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:17:51 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/05 13:25:23 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void		get_map_size(t_cub *cub);
static void		get_player_location(t_cub *cub);
static float	find_angle(t_map_elems **map);

void	initialize_values(t_cub *cub)
{
	int		i;
	
	get_map_size(cub);
	get_player_location(cub);
	/* cub->map_size.x = 10;
	cub->map_size.y = 10; */
	cub->player.angle = find_angle(cub->map->map);
/* 	cub->player.x = 300; // change to actual location
	cub->player.y = 300; // change to actual location */
	cub->player.dx = cos(cub->player.angle) * 5;
	cub->player.dy = sin(cub->player.angle) * 5;
	cub->cell_size.x = 64;
	cub->cell_size.y = 64;
}

static void		get_map_size(t_cub *cub)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	cub->map_size.x = i;
	i = 0;
	if (map[0])
	{
		while (map[0][i])
			i++;
	}
	cub->map_size.y = i;
}

static void		get_player_location(t_cub *cub)
{
	// find tile
	// calculate the center of tile
}

static float	find_angle(t_map_elems **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == START_NO || map[i][j] == START_SO ||\
				map[i][j] == START_WE || map[i][j] == START_EA)
				break ;
			j++;
		}
		i++;
	}
	if (map[i][j] == START_NO)
		return (0);
	if (map[i][j] == START_SO)
		return (M_PI);
	if (map[i][j] == START_WE)
		return (3 * M_PI / 2);
	if (map[i][j] == START_EA)
		return (M_PI / 2);
	return (-1);
}

void	draw_map(t_cub *cub)
{
	int	i;
	int	j;
	t_coord	current;

	i = 0;
	current.y = 0;
	while (i < cub->map_size.y)
	{
		current.x = 0;
		j = 0;
		while (j < cub->map_size.x)
		{
			// Fill rectangle
			if (cub->map[i * cub->map_size.x + j] == 2)
			{
				fill_rect(cub->img_map, (t_rect){current.x + 1, current.y + 1, cub->cell_size.x - 2, \
					cub->cell_size.y - 2, 0x0000FFFF});
			}
			// Draw cell border
			if (cub->map.... = 1)
				draw_rect(cub->img_map, (t_rect){current.x, current.y, cub->cell_size.x, \
					cub->cell_size.y, 0x00FFFFFF});
			j++;
			current.x += cub->cell_size.x;
		}
		i++;
		current.y += cub->cell_size.y;
	}
}


