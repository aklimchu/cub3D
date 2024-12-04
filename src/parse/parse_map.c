/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:23:32 by pleander          #+#    #+#             */
/*   Updated: 2024/12/04 16:03:13 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "libft.h"
#include "memlist.h"

static	void	check_map_line(char *line)
{
	int		i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_strchr("01NSEW ", line[i]))
			error_exit(ERR_INVALID_FILE);
		i++;
	}
}

void	read_map_line(char *line, t_list **lst)
{
	t_list	*new;

	check_map_line(line);
	new = ft_lstnew(line);
	if (!new)
		error_exit(ERR_FATAL);
	memlist_add(new);
	if (*lst == NULL)
		*lst = new;
	else
		ft_lstadd_back(lst, new);
}

static int	get_longest_row(t_list **rows)
{
	t_list *row;
	int		longest;
	int		len;

	longest = 0;
	row = *rows;
	while (row)
	{
		len = ft_strlen(row->content);
		if (((char *)row->content)[len - 1] == '\n')
			len--;
		if (len > longest)
			longest = len;
		row = row->next;
	}
	return (longest);
}

static void	parse_map_row(t_map_elems *dst, int size, char *row)
{
	int i;

	i = 0;
	while (row[i])
	{
		if (row[i] == ' ')	
			dst[i] = PADDING;
		else if (row[i] == '0')
			dst[i] = EMPTY;
		else if (row[i] == '1')
			dst[i] = WALL;
		else if (row[i] == 'N')
			dst[i] = START_NO;
		else if (row[i] == 'S')
			dst[i] = START_SO;
		else if (row[i] == 'W')
			dst[i] = START_WE;
		else if (row[i] == 'E')
			dst[i] = START_EA;
		else
			error_exit(ERR_INVALID_FILE);
		i++;
	}
	while (i < size)
		dst[i++] = PADDING;
}

void	parse_map(t_map *map, t_list **rows)
{
	int n_rows;
	int	n_cols;
	int	i;

	n_cols = get_longest_row(rows);
	n_rows = ft_lstsize(*rows);
	map->map = reserve(sizeof(void *) * n_rows);
	if (!map->map)
		error_exit(ERR_FATAL);
	i = 0;
	while (i < n_rows)
	{
		map->map[i] = reserve(sizeof(t_map_elems) * n_cols);
		if (!map->map[i])
			error_exit(ERR_FATAL);
		parse_map_row(map->map[i], n_cols, *(char **)(*rows)->content);
	}
}
	
