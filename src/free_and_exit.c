/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:06:14 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/16 08:44:28 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

//The function calls the action to free the memory
void	handle_destroy(void *input)
{
	t_cub	*cub;

	cub = (t_cub *)input;
	free_everything(cub, 0);
}

//The function frees the memory based on arguments provided
void	free_everything(t_cub *cub, int exit_code)
{
	if (cub->img_map)
		mlx_delete_image(cub->mlx, cub->img_map);
	if (cub->img_game)
		mlx_delete_image(cub->mlx, cub->img_game);
	mlx_terminate(cub->mlx);
	memlist_release_all();
	exit(exit_code);
}
