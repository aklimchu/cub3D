/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:14:45 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/16 11:55:28 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	check_next_tile(t_cub *cub, double x, double y)
{
	int	x_tile;
	int	y_tile;
	int	tile;

	x_tile = (int)x / CELL_SIZE;
	y_tile = (int)y / CELL_SIZE;
	tile = get_tile(y_tile, x_tile, cub->map);
	if (tile == EMPTY || tile == START_NO || \
		tile == START_SO || tile == START_EA || tile == START_WE)
		return (0);
	return (1);
}

/* int	check_offset(double *num1, double *off1, double *num2, double *off2)
{
	if (*num1 > 0 && *off1 < 0)
		*off1 *= -1;
	if (*num1 < 0 && *off1 > 0)
		*off1 *= -1;
	if (*num2 > 0 && *off2 < 0)
		*off2 *= -1;
	if (*num2 < 0 && *off2 > 0)
		*off2 *= -1;
	return (0);
} */

void	check_angle(t_cub *cub, bool x_dir, double *dx, double *dy)
{
	/* if (x_dir == true)
	{
		cub->player.dx = cos(cub->player.angle) * 5; // fps?
		cub->player.dy = 0;
	}
	else
	{
		cub->player.dx = 0;
		cub->player.dy = sin(cub->player.angle) * 5; // fps?
	} */
	(void)cub;
	if (x_dir == true)
		*dy = 0;
	else
		*dx = 0;
}

void	key_left_event(t_cub *cub)
{
	cub->player.angle -= 0.05;
	if (cub->player.angle < 0)
		cub->player.angle += 2 * M_PI;
}

void	key_right_event(t_cub *cub)
{
	cub->player.angle += 0.05;
	if (cub->player.angle > 2 * M_PI)
		cub->player.angle -= 2 * M_PI;
}
