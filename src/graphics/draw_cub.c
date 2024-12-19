/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:22:30 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/17 13:19:21 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	print_fps(t_cub *cub, double fps);

void	draw_cub(void *input)
{
	t_cub	*cub;
	double	current_fps;

	cub = (t_cub *)input;
	ft_memset(cub->img_map->pixels, 50, cub->img_map->width * \
		cub->img_map->height * BPP);
	ft_memcpy(cub->img_game->pixels, cub->bg_buffer, \
		cub->img_game->width * cub->img_game->height * BPP);
	current_fps = 1 / cub->mlx->delta_time;
	if (fabs(current_fps - cub->previous_fps) > 2)
	{
		print_fps(cub, current_fps);
		cub->previous_fps = current_fps;
	}
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
		free_everything(cub, EXIT_FAILURE, ERR_FATAL);
	memlist_add(str_fps);
	text = ft_strjoin("fps: ", str_fps);
	release(str_fps);
	if (!text)
		free_everything(cub, EXIT_FAILURE, ERR_FATAL);
	memlist_add(text);
	if (cub->img_fps)
		mlx_delete_image(cub->mlx, cub->img_fps);
	cub->img_fps = mlx_put_string(cub->mlx, text, \
		cub->fps_on_screen.x, cub->fps_on_screen.y);
	release(text);
}
