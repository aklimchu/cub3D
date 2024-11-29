/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:22:30 by aklimchu          #+#    #+#             */
/*   Updated: 2024/11/29 15:10:10 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	draw_cub(void *input)
{
	t_cub	*cub;

	cub = (t_cub *)input;
	if (cub->mlx == NULL)
		return ;
	draw_map(cub);
	//raycasting algorythm
}
