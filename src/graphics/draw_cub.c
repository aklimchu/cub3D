/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:22:30 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/16 14:02:47 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void draw_game_background(t_cub *cub);
static void	print_fps(t_cub *cub, double fps);

void	draw_cub(void *input)
{
	t_cub	*cub;
	double	fps;

	cub = (t_cub *)input;
	fps = 1 / cub->mlx->delta_time;
	if (cub->mlx == NULL)
		return ;
	ft_memset(cub->img_map->pixels, 50, cub->img_map->width * \
		cub->img_map->height * BPP);
	ft_memcpy(cub->img_game->pixels, cub->bg_buffer, \
		cub->img_game->width * cub->img_game->height * BPP);
	ft_memset(cub->img_fps->pixels, 50, cub->img_fps->width * \
		cub->img_fps->height * BPP);
	print_fps(cub, fps);
	update_player(cub);
	draw_map(cub);
	draw_player(cub);
	raycasting(cub);
}

static void	print_fps(t_cub *cub, double fps)
{
	char	*str_fps;
	char	*text;

	str_fps = ft_itoa((int)fps);
	if (!str_fps)
		error_exit(ERR_FATAL);
	memlist_add(str_fps);
	text = ft_strjoin("fps: ", str_fps);
	release(str_fps);
	if (!text)
		error_exit(ERR_FATAL);
	memlist_add(text);
	cub->img_fps = mlx_put_string(cub->mlx, text, \
		cub->img_game->width - 200, 100);
	release(text);
}
