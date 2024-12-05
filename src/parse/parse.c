/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:51:26 by pleander          #+#    #+#             */
/*   Updated: 2024/12/04 15:24:31 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "get_next_line.h"
#include "libft.h"
#include "memlist.h"

static void parse_file(int fd, t_map *map)
{
	char	*line;
	int		reading_map;
	t_list	*map_rows;

	reading_map = 0;
	map_rows = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (reading_map)
			read_map_line(line, &map_rows);
		if (!reading_map && parse_line(line, map) < 0)
			reading_map = 1;
		else
			line = get_next_line(fd);
	}
	parse_map(map, &map_rows);
	ft_lstclear(&map_rows, &free);
}

t_map	*parse(char *path)
{
	t_map	*map;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit(strerror(errno));
	map = creserve(1, sizeof(t_map));
	if (!map)
		error_exit(ERR_FATAL);
	parse_file(fd, map);
	return (map);
}

