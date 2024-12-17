/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:29:20 by pleander          #+#    #+#             */
/*   Updated: 2024/12/17 11:31:21 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	close_fd_and_exit(int fd, char *msg)
{
	close(fd);
	error_exit(msg);
}

static int	open_fd(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit(strerror(errno));
	return (fd);
}

void	read_file(char *path, t_list **file)
{
	int		fd;
	char	*line;
	t_list	*new;

	fd = open_fd(path);
	line = get_next_line(fd);
	if (!line)
		close_fd_and_exit(fd, ERR_FATAL);
	memlist_add(line);
	while (line)
	{
		new = ft_lstnew(line);
		if (!new)
			close_fd_and_exit(fd, ERR_FATAL);
		memlist_add(new);
		if (*file)
			ft_lstadd_back(file, new);
		else
			*file = new;
		line = get_next_line(fd);
		if (line)
			memlist_add(line);
	}
	close(fd);
}
