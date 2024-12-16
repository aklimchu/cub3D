/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 08:38:26 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/16 08:54:00 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	draw_ul(t_cub *cub, t_coord_d offset, t_coord cell, t_coord_d cur);
static void	draw_ur(t_cub *cub, t_coord_d offset, t_coord cell, t_coord_d cur);
static void	draw_dl(t_cub *cub, t_coord_d offset, t_coord cell, t_coord_d cur);
static void	draw_dr(t_cub *cub, t_coord_d offset, t_coord cell, t_coord_d cur);

void	draw_map(t_cub *cub)
{
	t_coord		cell;
	t_coord_d	player_offset;
	t_coord_d	current;

	cell.y = cub->player.y / CELL_SIZE;
	cell.x = cub->player.x / CELL_SIZE;
	player_offset.x = (cub->player.x - cell.x * CELL_SIZE) / \
		((double)CELL_SIZE / MAP_CELL_SIZE);
	player_offset.y = (cub->player.y - cell.y * CELL_SIZE) / \
		((double)CELL_SIZE / MAP_CELL_SIZE);
	current.y = MM_H / 2 - player_offset.y;
	draw_ul(cub, player_offset, cell, current);
	draw_ur(cub, player_offset, cell, current);
	draw_dl(cub, player_offset, cell, current);
	draw_dr(cub, player_offset, cell, current);
}

static void	draw_ul(t_cub *cub, t_coord_d offset, t_coord cell, t_coord_d cur)
{
	while (cur.y - MAP_CELL_SIZE > 0 && cell.y >= 0)
	{
		cell.x = cub->player.x / CELL_SIZE;
		cur.x = MM_W / 2 - offset.x;
		while (cur.x - MAP_CELL_SIZE > 0 && cell.x >= 0)
		{
			draw_cell(cub, cell, cur);
			cell.x--;
			cur.x -= MAP_CELL_SIZE;
		}
		cell.y--;
		cur.y -= MAP_CELL_SIZE;
	}
}

static void	draw_ur(t_cub *cub, t_coord_d offset, t_coord cell, t_coord_d cur)
{
	while (cur.y - MAP_CELL_SIZE > 0 && cell.y >= 0)
	{
		cell.x = cub->player.x / CELL_SIZE;
		cur.x = MM_W / 2 - offset.x;
		while (cur.x + MAP_CELL_SIZE < MM_W - 1 && \
			(size_t)cell.x < cub->map->map_cols)
		{
			draw_cell(cub, cell, cur);
			cell.x++;
			cur.x += MAP_CELL_SIZE;
		}
		cell.y--;
		cur.y -= MAP_CELL_SIZE;
	}
}

static void	draw_dl(t_cub *cub, t_coord_d offset, t_coord cell, t_coord_d cur)
{
	while (cur.y + MAP_CELL_SIZE < MM_H - 1 && \
		(size_t)cell.y < cub->map->map_rows)
	{
		cell.x = cub->player.x / CELL_SIZE;
		cur.x = MM_W / 2 - offset.x;
		while (cur.x - MAP_CELL_SIZE > 0 && cell.x >= 0)
		{
			draw_cell(cub, cell, cur);
			cell.x--;
			cur.x -= MAP_CELL_SIZE;
		}
		cell.y++;
		cur.y += MAP_CELL_SIZE;
	}
}

static void	draw_dr(t_cub *cub, t_coord_d offset, t_coord cell, t_coord_d cur)
{
	while (cur.y + MAP_CELL_SIZE < MM_H - 1 && \
		(size_t)cell.y < cub->map->map_rows)
	{
		cell.x = cub->player.x / CELL_SIZE;
		cur.x = MM_W / 2 - offset.x;
		while (cur.x + MAP_CELL_SIZE < MM_W - 1 && \
			(size_t)cell.x < cub->map->map_cols)
		{
			draw_cell(cub, cell, cur);
			cell.x++;
			cur.x += MAP_CELL_SIZE;
		}
		cell.y++;
		cur.y += MAP_CELL_SIZE;
	}
}
