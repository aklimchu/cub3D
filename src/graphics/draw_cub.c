/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:22:30 by aklimchu          #+#    #+#             */
/*   Updated: 2024/12/04 10:22:29 by aklimchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	draw_cub(void *input)
{
	t_cub	*cub;

	cub = (t_cub *)input;
	if (cub->mlx == NULL)
		return ;
	mlx_delete_image(cub->mlx, cub->img);
	cub->img = mlx_new_image(cub->mlx, SCREEN_W, SCREEN_H);
	if (cub->img == NULL)
		free_everything(NULL, cub, 1);
	draw_map(cub);
	draw_player(cub);
	raycasting(cub);
	if (!cub->img || (mlx_image_to_window(cub->mlx, cub->img, 0, 0) < 0))
		free_everything(cub->img, cub, EXIT_FAILURE);
}

void	raycasting(t_cub *cub)
{
	t_coord_f	ray_dir;
	t_coord_f	ray_start;
	t_coord		step;
	t_coord_f	ray_unit_step_size;
	t_coord_f	ray_length;
	t_coord		mouse;
	t_coord		map_check;

	mlx_get_mouse_pos(cub->mlx, &mouse.x, &mouse.y);
	ray_dir.x = 1;
	ray_dir.y = 1;
	ray_start.x = cub->player.x;
	ray_start.y = cub->player.y;
	//ray_dir should change based on keys pressed


	/*  float dirX = -1.0,  dirY = 0.0; //initial direction vector
	float planeX = 0.0, planeY = 0.66; //the 2d raycaster version of camera plane
	//float cameraX = 2*x/float(w)-1; //x-coordinate in camera space
	float cameraX = 1; // delete
      ray_dir.x = dirX + planeX * cameraX;
      ray_dir.y = dirY + planeY * cameraX; */
	
	ray_unit_step_size.x = sqrt(1 + (ray_dir.y / ray_dir.x) * \
		(ray_dir.y / ray_dir.x));
	printf("ray_unit_step_size x, %f\n", ray_unit_step_size.x);
	ray_unit_step_size.y = sqrt(1 + (ray_dir.x / ray_dir.y) * \
		(ray_dir.x / ray_dir.y));
	printf("ray_unit_step_size y, %f\n", ray_unit_step_size.y);
	map_check.x = (int)ray_start.x; // to know which tile we are in now based on start pos
	map_check.y = (int)ray_start.y; // to know which tile we are in now based on start pos
	if (ray_dir.x < 0)
	{
		step.x = -1;
		ray_length.x = (ray_start.x - (float)map_check.x) * ray_unit_step_size.x;
	}
	else
	{
		step.x = 1;
		ray_length.x = ((float)(map_check.x + 1) - ray_start.x) * ray_unit_step_size.x;
		printf("ray_length x, %f\n", ray_length.x);
	}
	if (ray_dir.y < 0)
	{
		step.y = -1;
		ray_length.y = (ray_start.y - (float)map_check.y) * ray_unit_step_size.y;
	}
	else
	{
		step.y = 1;
		ray_length.y = ((float)(map_check.y + 1) - ray_start.y) * ray_unit_step_size.y;
		printf("ray_length y, %f\n", ray_length.y);
	}

	bool	tile_found = false;
	float	max_distance = 100.0f;
	float	distance = 0.0f;

	while (!tile_found && distance < max_distance)
	{
		//walking
		if (ray_length.x < ray_length.y)
		{
			map_check.x += step.x;
			distance = ray_length.x;
			ray_length.x += ray_unit_step_size.x;
		}
		else
		{
			map_check.y += step.y;
			distance = ray_length.y;
			ray_length.y += ray_unit_step_size.y;
		}
		// check
		if (map_check.x >= 0 && map_check.x < cub->map_size.x && \
			map_check.y >= 0 && map_check.y < cub->map_size.y)
		{
			if (map_check.y * cub->map_size.x + map_check.x < cub->map_size.x * cub->map_size.y && \
				cub->map[map_check.y * cub->map_size.x + map_check.x] == 1)
			{
				tile_found = true;
				printf("TILE FOUND!!!: %d\n", map_check.y * cub->map_size.x + map_check.x);
			}
		}
	}

	t_coord_f	intersection;
	if (tile_found)
	{
		printf("number of tile found: %d\n", map_check.y * cub->map_size.x + map_check.x);
		intersection.x = ray_start.x + ray_dir.x * distance;
		intersection.y = ray_start.y + ray_dir.y * distance;
		printf("intersection x, %f\n", intersection.x);
		printf("intersection y, %f\n", intersection.y);
	}
}