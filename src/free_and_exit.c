/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:06:14 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/17 12:39:56 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	handle_destroy(void *input)
{
	t_cub	*cub;

	cub = (t_cub *)input;
	free_everything(cub, EXIT_SUCCESS, NULL);
}

void	free_everything(t_cub *cub, int exit_code, char *msg)
{
	if (cub->img_map)
		mlx_delete_image(cub->mlx, cub->img_map);
	if (cub->img_game)
		mlx_delete_image(cub->mlx, cub->img_game);
	if (cub->img_fps)
		mlx_delete_image(cub->mlx, cub->img_fps);
	delete_textures(cub);
	if (cub->mlx)
		mlx_terminate(cub->mlx);
	if (msg && exit_code != 0)
		error_exit(msg);
	memlist_release_all();
	exit(exit_code);
}
