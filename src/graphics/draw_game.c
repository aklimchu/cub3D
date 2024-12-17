/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 09:40:50 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/17 10:52:26 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "../inc/cub3D.h"

static mlx_texture_t	*get_texture(t_draw_context *dc, t_cub *cub);
static double			get_ray_dist_on_wall(t_draw_context *dc, t_cub *cub);
static void				draw_loop(t_draw_context *dc, t_cub *cub,
							t_texture_context *t);

void	draw_game(t_cub *cub, t_draw_context dc)
{
	double				wall_height;
	double				wall_offset;
	double				dist_to_wall_corr;
	t_texture_context	t;

	dist_to_wall_corr = dc.dist_to_wall * \
		cos(normalize_angle(cub->player.angle - dc.ray_angle));
	wall_height = CELL_SIZE * cub->img_game->height / dist_to_wall_corr;
	wall_offset = (double)cub->img_game->height / 2 - wall_height / 2;
	t.texture = get_texture(&dc, cub);
	t.y_start = (size_t)wall_offset;
	t.y_end = (size_t)wall_height + wall_offset;
	t.x = dc.iteration * cub->vertical_lines;
	t.y_scale = (double)t.texture->height / wall_height;
	t.texture_x = (int)floor(get_ray_dist_on_wall(&dc, cub) * \
					(t.texture->width - 1));
	draw_loop(&dc, cub, &t);
}

static size_t	get_texture_ind(t_texture_context *t, int iter)
{
	size_t	ind;
	size_t	row;

	row = (size_t)(iter * t->y_scale);
	ind = (((row * t->texture->width) + t->texture_x) * BPP);
	return (ind);
}

static void	draw_loop(t_draw_context *dc, t_cub *cub, t_texture_context *t)
{
	int				i;
	uint8_t			*pixelstart_t;
	uint8_t			*pixelstart_i;

	i = 0;
	if ((uint32_t)t->y_end > cub->img_game->height)
		t->y_end = cub->img_game->height;
	if (t->y_start < 0)
		i = -t->y_start;
	while (t->y_start + i < t->y_end)
	{
		pixelstart_t = &t->texture->pixels[
			get_texture_ind(t, i)];
		pixelstart_i = &cub->img_game->pixels[((t->y_start + i) * \
			cub->img_game->width + t->x) * BPP];
		ft_memcpy(pixelstart_i, pixelstart_t, BPP * cub->vertical_lines);
		i++;
	}
}

static double	get_ray_dist_on_wall(t_draw_context *dc, t_cub *cub)
{
	double	ray_hit_location;
	double	ray_dist_on_wall;

	if (dc->side == 1)
	{
		ray_hit_location = (cub->player.x + dc->dist_to_wall * \
			cos(dc->ray_angle));
		ray_dist_on_wall = ray_hit_location - CELL_SIZE * \
			(int)((ray_hit_location / CELL_SIZE));
	}
	else
	{
		ray_hit_location = (cub->player.y + dc->dist_to_wall * \
			sin(dc->ray_angle));
		ray_dist_on_wall = ray_hit_location - CELL_SIZE * \
			(int)((ray_hit_location / CELL_SIZE));
	}
	return (ray_dist_on_wall / CELL_SIZE);
}

static mlx_texture_t	*get_texture(t_draw_context *dc, t_cub *cub)
{
	if (dc->side == 1)
	{
		if (dc->ray_angle > 0 && dc->ray_angle < M_PI)
			return (cub->textures.s);
		else
			return (cub->textures.n);
	}
	else
	{
		if (dc->ray_angle > M_PI / 2 && dc->ray_angle < (1.5) * M_PI)
			return (cub->textures.w);
		else
			return (cub->textures.e);
	}
}
