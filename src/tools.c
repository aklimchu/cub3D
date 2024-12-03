/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:27:30 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/03 15:13:28 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	initialize_values(t_cub *cub)
{
	cub->map_size.x = 10;
	cub->map_size.y = 10;
	cub->player.x = 0.5;
	cub->player.y = 0.5;
	cub->cell_size.x = 64;
	cub->cell_size.y = 64;
	cub->map = (int *)malloc(cub->map_size.x * cub->map_size.y * sizeof(int));
	memset(cub->map, 0, cub->map_size.x * cub->map_size.y * sizeof(int)); // ?
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
			if (i == 0 || j == cub->map_size.x - 1)
			{
				fill_rect(cub->img, (t_rect){current.x + 1, current.y + 1, cub->cell_size.x - 2, \
					cub->cell_size.y - 2, 0x0000FFFF});
				cub->map[i * cub->map_size.x + j] = 1;
			}
			// Draw cell border
			draw_rect(cub->img, (t_rect){current.x, current.y, cub->cell_size.x, \
				cub->cell_size.y, 0x00FFFFFF});
			j++;
			current.x += cub->cell_size.x;
		}
		i++;
		current.y += cub->cell_size.y;
	}
}

void	draw_rect(mlx_image_t *img, t_rect rect)
{
	int		x;
	int		y;

	x = rect.x;
	y = rect.y;
	while (x < rect.x + rect.width)
		mlx_put_pixel(img, x++, y, rect.color);
	while (y < rect.y + rect.height)
		mlx_put_pixel(img, x, y++, rect.color);
	while (x > rect.x)
		mlx_put_pixel(img, x--, y, rect.color);
	while (y > rect.y)
		mlx_put_pixel(img, x, y--, rect.color);
}

void	fill_rect(mlx_image_t *img, t_rect rect)
{
	int		y;
	int		x;

	y = rect.y;
	while (y < rect.y + rect.height)
	{
		x = rect.x;
		while (x < rect.x + rect.width)
			mlx_put_pixel(img, x++, y, rect.color);
		y++;
	}
}
