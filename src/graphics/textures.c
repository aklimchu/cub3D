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
		error_exit(strerror(mlx_errno));
	cub->textures.s = mlx_load_png(cub->map->so_texture);
	if (!cub->textures.s)
		error_exit(strerror(mlx_errno));
	cub->textures.w = mlx_load_png(cub->map->we_texture);
	if (!cub->textures.w)
		error_exit(strerror(mlx_errno));
	cub->textures.e = mlx_load_png(cub->map->ea_texture);
	if (!cub->textures.e)
		error_exit(strerror(mlx_errno));
}
