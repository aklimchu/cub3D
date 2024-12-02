/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:51:26 by pleander          #+#    #+#             */
/*   Updated: 2024/12/02 14:49:56 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "get_next_line.h"
#include "memlist.h"


static void parse_file(int fd, t_map *map)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		parse_line(line, map);
		line = get_next_line(fd);
	}
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

