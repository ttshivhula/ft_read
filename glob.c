/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 10:29:26 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/09/07 13:39:49 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line.h"

static int		glob_len(char **str, char **v)
{
	int len;
	int i;
	int j;
	int p;

	i = 0;
	len = 0;
	while (str[i])
	{
		j = 0;
		p = 0;
		while (v[j])
		{
			if (glob_match(str[i], v[j]))
			{
				p++;
				len += ft_strlen(v[j]) + 1;
			}
			j++;
		}
		if (!p)
			len += ft_strlen(str[i]) + 1;
		i++;
	}
	return (len + 1);
}

char			*glob_replace(char *str)
{
	char **sp = ft_strsplit(str, ' ');
	char **files = get_files();
	int i = 0;
	int j;
	int p;
	int k = 0;
	int r;
	int av = 0;
	char *new = (char *)malloc(sizeof(char) * glob_len(sp, files));
	while (sp[i])
	{
		j = 0;
		p = 0;
		while (files[j])
		{
			if (glob_match(sp[i], files[j]))
			{
				p++;
				r = 0;
				while (files[j][r])
				{
					av = 1;
					new[k++] = files[j][r++];
				}
				if (av)
				{
					new[k++] = ' ';
					av = 0;
				}
			}
			j++;
		}
		if (!p)
		{
			r = 0;
			while (sp[i][r])
			{
				av = 1;
				new[k++] = sp[i][r++];
			}
			if (av)
			{
				new[k++] = ' ';
				av = 0;
			}
		}
		i++;
	}
	new[k] = '\0';
	char *ret = ft_strdup(ft_strtrim(new));
	free(new);
	return (ret);
}
