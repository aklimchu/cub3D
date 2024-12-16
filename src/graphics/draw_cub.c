/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:22:30 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/16 10:56:30 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	print_fps(t_cub *cub, double fps);

void	draw_cub(void *input)
{
	t_cub	*cub;

	cub = (t_cub *)input;
	// TEMPORARY FPS PRINTING, REMOVE BEFORE SUBMISSION
	double fps = 1 / cub->mlx->delta_time;
	printf("FPS %f\n", fps);
	//
	if (cub->mlx == NULL)
		return ;
	ft_memset(cub->img_map->pixels, 50, cub->img_map->width * \
		cub->img_map->height * BPP);
	ft_memset(cub->img_game->pixels, 50, cub->img_game->width * \
		cub->img_game->height * BPP);
	ft_memset(cub->img_fps->pixels, 50, cub->img_fps->width * \
		cub->img_fps->height * BPP);
	print_fps(cub, fps); // do we need to remove?
	draw_map(cub);
	draw_player(cub);
	raycasting(cub);
}

static void	print_fps(t_cub *cub, double fps)
{
	char *str_fps = ft_itoa((int)fps);
	printf("%s\n", str_fps);
	char *text = ft_strjoin("fps: ", str_fps);
	printf("%s\n", text);
	cub->img_fps = mlx_put_string(cub->mlx, text, cub->img_game->width - 200, 100);
	free(text);
}