/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_glob.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 12:04:33 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/09/25 09:13:16 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line.h"

char			*glob_files(char *match)
{
	DIR				*dirp;
	struct dirent	*entry;
	char			*ret;

	if ((dirp = opendir(".")))
	{
		ret = ft_strdup(" ");
		while ((entry = readdir(dirp)) != NULL)
		{
			if (glob_match(match, entry->d_name)
					&& ft_strncmp(entry->d_name, ".", 1) != 0)
			{
				ft_free_join(&ret, ret, entry->d_name);
				ft_free_join(&ret, ret, " ");
			}
		}
		closedir(dirp);
		return (ret);
	}
	return (ft_strdup(" null "));
}
