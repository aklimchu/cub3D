/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:06:14 by aklimchu          #+#    #+#             */
/*   Updated: 2024/11/29 14:38:05 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

//The function calls the action to free the memory
void	handle_destroy(void *input)
{
	t_cub	*cub;

	cub = (t_cub *)input;
	free_everything(cub->img, cub, 0);
}

//The function frees the memory based on arguments provided
void	free_everything(mlx_image_t *img, t_cub *cub, int exit_code)
{
	if (cub->map)
		free (cub->map);
	if (img)
		mlx_delete_image(cub->mlx, img);
	mlx_terminate(cub->mlx);
	exit(exit_code);
}