/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:22:30 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/05 14:59:50 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	draw_cub(void *input)
{
	t_cub	*cub;

	cub = (t_cub *)input;
	if (cub->mlx == NULL)
		return ;
	mlx_delete_image(cub->mlx, cub->img_map);
	cub->img_map = mlx_new_image(cub->mlx, SCREEN_W, SCREEN_H);
	if (cub->img_map == NULL)
		free_everything(cub, 1);
	mlx_delete_image(cub->mlx, cub->img_game);
	cub->img_game = mlx_new_image(cub->mlx, SCREEN_W / 2, SCREEN_H / 2);
	if (cub->img_game == NULL)
		free_everything(cub, 1);
	draw_map(cub);
	draw_player(cub);
	raycasting(cub);
	if (!cub->img_map || (mlx_image_to_window(cub->mlx, cub->img_map, 0, 0) < 0))
		free_everything(cub, EXIT_FAILURE);
	/* if (!cub->img_game || (mlx_image_to_window(cub->mlx, cub->img_game, 650, 0) < 0))
		free_everything(cub, EXIT_FAILURE); */
}
