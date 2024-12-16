/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 09:40:50 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/16 10:12:15 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "../inc/cub3D.h"

static mlx_texture_t	*get_texture(t_draw_context *dc, t_cub *cub);
static double			get_ray_dist_on_wall(t_draw_context *dc, t_cub *cub);
static void				draw_loop(t_draw_context *dc, t_cub *cub, int y_start, int y_end);

void draw_game(t_cub *cub, t_draw_context dc)
{
	double			wall_height;
	double			wall_offset;
	mlx_texture_t	*texture;
	int				y_start;
	int				y_end;

	dc.dist_to_wall = dc.dist_to_wall * cos(normalize_angle(cub->player.angle - dc.ray_angle));
	wall_height = CELL_SIZE * cub->img_game->height / dc.dist_to_wall;
	wall_offset = (double)cub->img_game->height / 2 - wall_height / 2;
	texture = get_texture(&dc, cub);
	y_start = (size_t)wall_offset;
	y_end	= (size_t)wall_height + wall_offset;

	draw_loop(&dc, cub, y_start, y_end);
}

static size_t	get_texture_ind(t_draw_context *dc, mlx_texture_t *t,
		t_cub *cub, int iter)
{
	double	wall_height;
	double	y_scale;
	size_t	texture_x;
	size_t	ind;

	wall_height = CELL_SIZE * cub->img_game->height / dc->dist_to_wall;
	y_scale = (double)t->height / wall_height;
	texture_x = (int)floor(get_ray_dist_on_wall(dc, cub) * (t->width - 1));
	size_t row = (int)(iter * y_scale);
	ind = (((row * t->width) + texture_x) * BPP);
	return (ind);
}

static void	draw_loop(t_draw_context *dc, t_cub *cub, int y_start, int y_end)
{
	int				i;
	size_t			x;
	mlx_texture_t	*t;
	uint8_t			*pixelstart_t;
	uint8_t			*pixelstart_i;

	x = dc->iteration * cub->vertical_lines;
	t = get_texture(dc, cub);
	i = 0;
	if ((uint32_t)y_end > cub->img_game->height)
		y_end = cub->img_game->height;
	if (y_start < 0)
		i = -y_start;
	while (y_start + i < y_end)
	{
		pixelstart_t = &t->pixels[get_texture_ind(dc, t, cub, i)];
		pixelstart_i = &cub->img_game->pixels[((y_start + i) * \
			cub->img_game->width + x) * BPP];
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
			floor((ray_hit_location / CELL_SIZE));
	}
	else
	{
		ray_hit_location = (cub->player.y + dc->dist_to_wall * \
			sin(dc->ray_angle));
		ray_dist_on_wall = ray_hit_location - CELL_SIZE * \
			floor((ray_hit_location / CELL_SIZE));
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
