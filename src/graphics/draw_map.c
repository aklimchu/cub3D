// 42 header

#include "../inc/cub3D.h"

static void	draw_quadrant_up_left(t_cub *cub, t_coord_f player_offset, t_coord cell, t_coord_f current);
static void	draw_quadrant_up_right(t_cub *cub, t_coord_f player_offset, t_coord cell, t_coord_f current);
static void	draw_quadrant_down_left(t_cub *cub, t_coord_f player_offset, t_coord cell, t_coord_f current);
static void	draw_quadrant_down_right(t_cub *cub, t_coord_f player_offset, t_coord cell, t_coord_f current);

void	draw_map(t_cub *cub)
{
	t_coord		cell;
	t_coord_f	player_offset;
	t_coord_f	current;
	
	cell.y = cub->player.y / CELL_SIZE;
	cell.x = cub->player.x / CELL_SIZE;
	player_offset.x = (cub->player.x - cell.x * CELL_SIZE) / ((double)CELL_SIZE / MAP_CELL_SIZE);
	player_offset.y = (cub->player.y - cell.y * CELL_SIZE) / ((double)CELL_SIZE / MAP_CELL_SIZE);
	current.y = MM_H / 2 - player_offset.y;
	draw_quadrant_up_left(cub, player_offset, cell, current);
	draw_quadrant_up_right(cub, player_offset, cell, current);
	draw_quadrant_down_left(cub, player_offset, cell, current);
	draw_quadrant_down_right(cub, player_offset, cell, current);
}

static void	draw_quadrant_up_left(t_cub *cub, t_coord_f player_offset, t_coord cell, t_coord_f current)
{
	while (current.y - MAP_CELL_SIZE > 0 && cell.y >= 0)
	{
		cell.x = cub->player.x / CELL_SIZE;
		current.x = MM_W / 2 - player_offset.x;
		while (current.x - MAP_CELL_SIZE > 0 && cell.x >= 0)
		{
			draw_cell(cub, cell, current);
			cell.x--;
			current.x -= MAP_CELL_SIZE;
		}
		cell.y--;
		current.y -= MAP_CELL_SIZE;
	}
}

static void	draw_quadrant_up_right(t_cub *cub, t_coord_f player_offset, t_coord cell, t_coord_f current)
{
	while (current.y - MAP_CELL_SIZE > 0 && cell.y >= 0)
	{
		cell.x = cub->player.x / CELL_SIZE;
		current.x = MM_W / 2 - player_offset.x;
		while (current.x + MAP_CELL_SIZE < MM_W - 1 && cell.x < cub->map->map_cols)
		{
			draw_cell(cub, cell, current);
			cell.x++;
			current.x += MAP_CELL_SIZE;
		}
		cell.y--;
		current.y -= MAP_CELL_SIZE;
	}
}

static void	draw_quadrant_down_left(t_cub *cub, t_coord_f player_offset, t_coord cell, t_coord_f current)
{
	while (current.y + MAP_CELL_SIZE < MM_H - 1 && cell.y < cub->map->map_rows)
	{
		cell.x = cub->player.x / CELL_SIZE;
		current.x = MM_W / 2 - player_offset.x;
		while (current.x - MAP_CELL_SIZE > 0 && cell.x >= 0)
		{
			draw_cell(cub, cell, current);
			cell.x--;
			current.x -= MAP_CELL_SIZE;
		}
		cell.y++;
		current.y += MAP_CELL_SIZE;
	}
}

static void	draw_quadrant_down_right(t_cub *cub, t_coord_f player_offset, t_coord cell, t_coord_f current)
{
	while (current.y + MAP_CELL_SIZE < MM_H - 1 && cell.y < cub->map->map_rows)
	{
		cell.x = cub->player.x / CELL_SIZE;
		current.x = MM_W / 2 - player_offset.x;
		while (current.x + MAP_CELL_SIZE < MM_W - 1 && cell.x < cub->map->map_cols)
		{
			draw_cell(cub, cell, current);
			cell.x++;
			current.x += MAP_CELL_SIZE;
		}
		cell.y++;
		current.y += MAP_CELL_SIZE;
	}
}