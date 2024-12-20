/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:51:26 by pleander          #+#    #+#             */
/*   Updated: 2024/12/17 11:31:37 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "memlist.h"

static void	release_list(t_list **lst)
{
	t_list	*current;
	t_list	*next;

	current = *lst;
	while (current)
	{
		next = current->next;
		release(current->content);
		release(current);
		current = next;
	}
	*lst = NULL;
}

static void	parse_file(t_list **file, t_map *map)
{
	char	*line;
	t_list	*cur;
	t_list	*map_start;
	int		reading_map;

	cur = *file;
	reading_map = 0;
	map_start = NULL;
	while (cur)
	{
		line = cur->content;
		if (reading_map)
			check_map_line(line);
		else if (parse_line(line, map) < 0)
		{
			reading_map = 1;
			map_start = cur;
		}
		cur = cur->next;
	}
	if (!map_start)
		error_exit("Map is missing from .cub file");
	parse_map(map, &map_start);
	release_list(file);
}

t_map	*parse(char *path)
{
	t_map	*map;
	t_list	*file;

	map = creserve(1, sizeof(t_map));
	map->player_start.x = -1;
	map->player_start.y = -1;
	if (!map)
		error_exit(ERR_FATAL);
	file = NULL;
	read_file(path, &file);
	parse_file(&file, map);
	check_map(map);
	return (map);
}
