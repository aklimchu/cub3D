/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:22:30 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/12 14:19:33 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	draw_cub(void *input)
{
	t_cub	*cub;

	cub = (t_cub *)input;
	if (cub->mlx == NULL)
		return ;
	ft_memset(cub->img_map->pixels, 50, cub->img_map->width * \
		cub->img_map->height * BPP);
	ft_memset(cub->img_game->pixels, 50, cub->img_game->width * \
		cub->img_game->height * BPP);
	draw_map(cub);
	draw_player(cub);
	raycasting(cub);
}
