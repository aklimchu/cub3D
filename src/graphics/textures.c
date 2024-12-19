/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:40:58 by pleander          #+#    #+#             */
/*   Updated: 2024/12/10 13:45:53 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	load_textures(t_cub *cub)
{
	cub->textures.n = mlx_load_png(cub->map->no_texture);
	if (!cub->textures.n)
		free_everything(cub, EXIT_FAILURE, "Failed to load NO texture");
	cub->textures.s = mlx_load_png(cub->map->so_texture);
	if (!cub->textures.s)
		free_everything(cub, EXIT_FAILURE, "Failed to load SO texture");
	cub->textures.w = mlx_load_png(cub->map->we_texture);
	if (!cub->textures.w)
		free_everything(cub, EXIT_FAILURE, "Failed to load WE texture");
	cub->textures.e = mlx_load_png(cub->map->ea_texture);
	if (!cub->textures.e)
		free_everything(cub, EXIT_FAILURE, "Failed to load EA texture");
}

void	delete_textures(t_cub *cub)
{
	if (cub->textures.n)
		mlx_delete_texture(cub->textures.n);
	if (cub->textures.e)
		mlx_delete_texture(cub->textures.e);
	if (cub->textures.s)
		mlx_delete_texture(cub->textures.s);
	if (cub->textures.w)
		mlx_delete_texture(cub->textures.w);
}
