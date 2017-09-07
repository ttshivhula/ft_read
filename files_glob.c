/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_glob.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 12:04:33 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/09/07 13:37:36 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line.h"

static int		num_files(void)
{
	int				file_count;
	DIR				*dirp;
	struct dirent	*entry;

	file_count = 0;
	dirp = opendir(".");
	while ((entry = readdir(dirp)) != NULL)
		file_count++;
	closedir(dirp);
	return (file_count);
}

static char		**remove_hidden(char **fl)
{
	char	**tmp;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	while (fl[i])
	{
		if (fl[i][0] != '.')
			len++;
		i++;
	}
	tmp = (char **)malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (fl[i])
	{
		if (fl[i][0] != '.')
			tmp[j++] = ft_strdup(fl[i]);
		i++;
	}
	tmp[j] = NULL;
	return (tmp);
}

char			**get_files(void)
{
	char			**files;
	int				i;
	DIR				*dirp;
	struct dirent	*entry;

	files = (char **)malloc(sizeof(char *) * (num_files() + 1));
	i = 0;
	dirp = opendir(".");
	while ((entry = readdir(dirp)) != NULL)
		files[i++] = ft_strdup(entry->d_name);
	files[i] = NULL;
	closedir(dirp);
	files = remove_hidden(files);
	return (files);
}
