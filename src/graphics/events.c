/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:15:43 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/11 11:28:18 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	key_a_event(t_cub *cub);
static void	key_d_event(t_cub *cub);
static void	key_w_event(t_cub *cub);
static void	key_s_event(t_cub *cub);

void	handle_keypress(struct mlx_key_data key_data, void *input)
{
	t_cub	*cub;
	
	cub = (t_cub *)input;
	(void)key_data;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE) == true)
		free_everything(cub, 0);
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_A) == true)
		key_a_event(cub);
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_D) == true)
		key_d_event(cub);
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_W) == true)
		key_w_event(cub);
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_S) == true)
		key_s_event(cub);	
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT) == true)
		key_left_event(cub);
	else if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT) == true)
		key_right_event(cub);
	cub->player.dx = cos(cub->player.angle) * 5;
	cub->player.dy = sin(cub->player.angle) * 5;
}

static void	key_a_event(t_cub *cub)
{
	int	x_offset;
	int	y_offset;
	
	x_offset = cub->cell_size / 7;
	y_offset = cub->cell_size / 7;
	check_offset(&cub->player.dy, &x_offset, &cub->player.dx, &y_offset);
	if (check_next_tile(cub, cub->player.x + cub->player.dy + x_offset, \
		cub->player.y - cub->player.dx - y_offset) == 1)
	{
		check_angle(cub, true);
	}
	if (check_next_tile(cub, cub->player.x + cub->player.dy + x_offset, \
		cub->player.y - cub->player.dx - y_offset) == 1)
	{
		check_angle(cub, false);
	}
	if (check_next_tile(cub, cub->player.x + cub->player.dy + x_offset, \
		cub->player.y - cub->player.dx - y_offset) == 0)
	{
		cub->player.x += cub->player.dy;
		cub->player.y -= cub->player.dx;
	}
}

static void	key_d_event(t_cub *cub)
{
	int	x_offset;
	int	y_offset;
	
	x_offset = cub->cell_size / 7;
	y_offset = cub->cell_size / 7;
	check_offset(&cub->player.dy, &x_offset, &cub->player.dx, &y_offset);
	if (check_next_tile(cub, cub->player.x - cub->player.dy - x_offset, \
		cub->player.y + cub->player.dx + y_offset) == 1)
	{
		check_angle(cub, true);
	}
	if (check_next_tile(cub, cub->player.x - cub->player.dy - x_offset, \
		cub->player.y + cub->player.dx + y_offset) == 1)
	{
		check_angle(cub, false);
	}
	if (check_next_tile(cub, cub->player.x - cub->player.dy - x_offset, \
		cub->player.y + cub->player.dx + y_offset) == 0)
	{
		cub->player.x -= cub->player.dy;
		cub->player.y += cub->player.dx;
	}
}

static void	key_w_event(t_cub *cub)
{
	int	x_offset;
	int	y_offset;
	
	x_offset = cub->cell_size / 7;
	y_offset = cub->cell_size / 7;
	check_offset(&cub->player.dx, &x_offset, &cub->player.dy, &y_offset);
	if (check_next_tile(cub, cub->player.x + cub->player.dx + x_offset, \
		cub->player.y + cub->player.dy + y_offset) == 1)
	{
		check_angle(cub, true);
	}
	if (check_next_tile(cub, cub->player.x + cub->player.dx + x_offset, \
		cub->player.y + cub->player.dy + y_offset) == 1)
	{
		check_angle(cub, false);
	}
	if (check_next_tile(cub, cub->player.x + cub->player.dx + x_offset, \
		cub->player.y + cub->player.dy + y_offset) == 0)
	{
		cub->player.x += cub->player.dx;
		cub->player.y += cub->player.dy;
	}
}

static void	key_s_event(t_cub *cub)
{
	int	x_offset;
	int	y_offset;
	
	x_offset = cub->cell_size / 7;
	y_offset = cub->cell_size / 7;
	check_offset(&cub->player.dx, &x_offset, &cub->player.dy, &y_offset);
	if (check_next_tile(cub, cub->player.x - cub->player.dx - x_offset, \
		cub->player.y - cub->player.dy - y_offset) == 1)
	{
		check_angle(cub, true);
	}
	if (check_next_tile(cub, cub->player.x - cub->player.dx - x_offset, \
		cub->player.y - cub->player.dy - y_offset) == 1)
	{
		check_angle(cub, false);
	}
	if (check_next_tile(cub, cub->player.x - cub->player.dx - x_offset, \
		cub->player.y - cub->player.dy - y_offset) == 0)
	{
		cub->player.x -= cub->player.dx;
		cub->player.y -= cub->player.dy;
	}
}
