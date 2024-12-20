/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:10:41 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/20 09:49:50 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	create_images(t_cub *c);
static void	add_shading(mlx_texture_t *texture);
static void	create_bg_buffer(t_cub *cub);

int	main(int argc, char **argv)
{
	t_cub	cub;

	ft_memset(&cub, 0, sizeof(cub));
	if (argc != 2)
		error_exit("Incorrect amount of arguments");
	cub.map = parse(argv[1]);
	load_textures(&cub);
	add_shading(cub.textures.n);
	add_shading(cub.textures.e);
	create_images(&cub);
	initialize_values(&cub);
	create_bg_buffer(&cub);
	mlx_loop_hook(cub.mlx, &draw_cub, &cub);
	mlx_close_hook(cub.mlx, &handle_destroy, &cub);
	mlx_key_hook(cub.mlx, &handle_keypress, &cub);
	mlx_loop(cub.mlx);
	free_everything(&cub, EXIT_SUCCESS, NULL);
	return (0);
}

static void	create_images(t_cub *c)
{
	int32_t	m_width;
	int32_t	m_height;

	c->mlx = mlx_init(800, 600, "cub3D", 0);
	if (c->mlx == NULL)
		free_everything(c, EXIT_FAILURE, strerror(mlx_errno));
	mlx_get_monitor_size(0, &m_width, &m_height);
	mlx_set_window_size(c->mlx, m_width, m_height);
	if (m_width > m_height)
		c->img_map = mlx_new_image(c->mlx, m_width / 10, m_width / 10);
	else
		c->img_map = mlx_new_image(c->mlx, m_height / 10, m_height / 10);
	if (c->img_map == NULL)
		free_everything(c, EXIT_FAILURE, strerror(mlx_errno));
	c->img_game = mlx_new_image(c->mlx, m_width, m_height);
	if (c->img_game == NULL)
		free_everything(c, EXIT_FAILURE, strerror(mlx_errno));
	c->img_fps = NULL;
	if (!c->img_map || (mlx_image_to_window(c->mlx, c->img_map, 0, 0) < 0))
		free_everything(c, EXIT_FAILURE, strerror(mlx_errno));
	if (!c->img_game || (mlx_image_to_window(c->mlx, c->img_game, 0, 0) < 0))
		free_everything(c, EXIT_FAILURE, strerror(mlx_errno));
	mlx_set_instance_depth(c->img_map->instances, 1);
	mlx_set_instance_depth(c->img_game->instances, 0);
}

static void	add_shading(mlx_texture_t *texture)
{
	float	shading_factor;
	int		i;
	uint8_t	*pixels;
	int		pixel_count;
	uint8_t	*pixel;

	shading_factor = 0.7;
	i = 0;
	pixels = texture->pixels;
	pixel_count = texture->width * texture->height;
	while (i < pixel_count)
	{
		pixel = &pixels[i * BPP];
		pixel[0] = (uint8_t)(pixel[0] * shading_factor);
		pixel[1] = (uint8_t)(pixel[1] * shading_factor);
		pixel[2] = (uint8_t)(pixel[2] * shading_factor);
		if (BPP == 4)
			pixel[3] = pixel[3];
		i++;
	}
}

static void	create_bg_buffer(t_cub *cub)
{
	size_t	i;
	size_t	game_size;

	game_size = cub->img_game->height * cub->img_game->width * BPP;
	cub->bg_buffer = reserve(game_size);
	if (!cub->bg_buffer)
		free_everything(cub, EXIT_FAILURE, ERR_FATAL);
	i = 0;
	while (i < game_size / 2)
	{
		mlx_draw_pixel(&cub->bg_buffer[i], get_rgba(cub->map->roof_color));
		i += 4;
	}
	while (i < game_size)
	{
		mlx_draw_pixel(&cub->bg_buffer[i], get_rgba(cub->map->floor_color));
		i += 4;
	}
}
