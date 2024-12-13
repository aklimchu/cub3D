// 42 header

#include "../inc/cub3D.h"

static void	draw_cell(t_cub *cub, t_coord cell, t_coord current);

/* void	draw_map(t_cub *cub)
{
	t_coord		cell;
	t_coord		current;
	t_coord		player_offset;
		
	cell.x = cub->player.x / CELL_SIZE;
	cell.y = cub->player.y / CELL_SIZE;
	player_offset.x = (cub->player.x - cell.x * CELL_SIZE) / (CELL_SIZE / MAP_CELL_SIZE);
	player_offset.y = (cub->player.y - cell.y * CELL_SIZE) / (CELL_SIZE / MAP_CELL_SIZE);
	current.y = MM_H / 2 - player_offset.y;
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

	cell.x = cub->player.x / CELL_SIZE;
	cell.y = cub->player.y / CELL_SIZE;
	current.y = MM_H / 2 - player_offset.y;
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
	
	cell.x = cub->player.x / CELL_SIZE;
	cell.y = cub->player.y / CELL_SIZE;
	current.y = MM_H / 2 - player_offset.y;
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
	
	cell.x = cub->player.x / CELL_SIZE;
	cell.y = cub->player.y / CELL_SIZE;
	current.y = MM_H / 2 - player_offset.y;
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
} */

void	draw_map(t_cub *cub)
{
	t_coord		cell;
	t_coord		current;
	t_coord		player_offset;
		
	cell.x = cub->player.x / CELL_SIZE;
	cell.y = cub->player.y / CELL_SIZE;
	player_offset.x = (cub->player.x - cell.x * CELL_SIZE) / (CELL_SIZE / MAP_CELL_SIZE);
	player_offset.y = (cub->player.y - cell.y * CELL_SIZE) / (CELL_SIZE / MAP_CELL_SIZE);
	current.y = MM_H / 2 - player_offset.y;
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

	cell.x = cub->player.x / CELL_SIZE;
	cell.y = cub->player.y / CELL_SIZE;
	current.y = MM_H / 2 - player_offset.y;
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
	
	cell.x = cub->player.x / CELL_SIZE;
	cell.y = cub->player.y / CELL_SIZE;
	current.y = MM_H / 2 - player_offset.y;
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
	
	cell.x = cub->player.x / CELL_SIZE;
	cell.y = cub->player.y / CELL_SIZE;
	current.y = MM_H / 2 - player_offset.y;
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

static void	draw_cell(t_cub *cub, t_coord cell, t_coord current)
{
	int	tile;
	
	tile = get_tile(cell.y, cell.x, cub->map);
	if (tile == WALL)
	{
		fill_rect(cub->img_map, (t_rect){current.x + 1, current.y + 1, MAP_CELL_SIZE - 2, \
				MAP_CELL_SIZE - 2, BLUE});
	}
	if (tile == EMPTY || tile == WALL)
	{
		draw_rect(cub->img_map, (t_rect){current.x, current.y, MAP_CELL_SIZE, \
			MAP_CELL_SIZE, LIGHT_BLUE});
	}
}