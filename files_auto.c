/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 10:29:26 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/09/22 09:10:41 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line.h"

char			*auto_files(char *match)
{
	DIR				*dirp;
	struct dirent	*entry;
	char			*ret;

	if ((dirp = opendir(".")))
	{
		ret = ft_strdup(" ");
		while ((entry = readdir(dirp)) != NULL)
		{
			if (ft_strncmp(entry->d_name, match, ft_strlen(match)) == 0)
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
