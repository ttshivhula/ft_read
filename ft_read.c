/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 10:23:06 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/09/07 11:20:37 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line.h"

void	get_cursor_start_pos(t_read *line)
{
	char	answer[20];
	int		i;

	ft_putstr_fd("\e[6n", 0);
	ft_bzero(answer, 20);
	i = read(0, answer, 20);
	answer[i] = 0;
	i = 2;
	line->start.row = ft_atoi(answer + i);
	while (ft_isdigit(answer[i]))
		i++;
	line->start.col = ft_atoi(answer + i + 1);
}

void	match_hist(int key_pressed, t_read *line)
{
	int						i;
	static struct s_keyhist	keyhist[2] = {
		{KEY_UP, &old_hist_entry},
		{KEY_DOWN, &new_hist_entry}
	};

	i = 0;
	while (i < 2)
		if (key_pressed == keyhist[i++].key)
			keyhist[i - 1].p(line, &(line->hist));
}

void	match_move(int key_pressed, t_read *line)
{
	int						i;
	static struct s_keymove	keymove[8] = {
		{KEY_RIGHT, &cright},
		{KEY_LEFT, &cleft},
		{KEY_HOME, &chome},
		{KEY_END, &cend},
		{KEY_SRIGHT, &goto_next_word},
		{KEY_SLEFT, &goto_prev_word},
		{KEY_SPREVIOUS, &goto_prev_line},
		{KEY_SNEXT, &goto_next_line}
	};

	i = 0;
	while (i < 8)
		if (key_pressed == keymove[i++].key)
			keymove[i - 1].p(line);
}

void	input_loop(t_read *line)
{
	int		key_pressed;

	while (1)
	{
		key_pressed = ft_key();
		ft_windowsize(&line->winsz);
		if (line->start.row + line->cursor / line->winsz.col > line->winsz.row)
			line->start.row--;
		match_move(key_pressed, line);
		match_hist(key_pressed, line);
		if (key_pressed > 31 && key_pressed < 127)
			ft_insert_char(line, key_pressed);
		if (key_pressed == KEY_DC || key_pressed == 127)
			ft_delete_char(line, key_pressed);
		if (key_pressed == KEY_CTRLL)
		{
			tputs(tgoto(tgetstr("SF", NULL), 0, line->start.row - 1)
					, 1, &tc_putc);
			line->start.row = 1;
			set_curpos(line);
		}
		if (key_pressed == '\n')
			break ;
	}
}

char	*ft_read(void)
{
	t_read	line;

	raw_mode();
	ft_bzero(&line, sizeof(line));
	line.hist = get_history();
	line.hist_size = ft_dlstsize(line.hist);
	get_cursor_start_pos(&line);
	input_loop(&line);
	cend(&line);
	default_mode();
	ft_putchar('\n');
	add_history(line.cmd);
	ft_dlstdelstr(&line.hist);
	//must add globing and !history type .... 
	if (line.cmd[0] == '!' && ft_isdigit(line.cmd[1]))
	{
		char *fuck;
		int num = ft_atoi(line.cmd + 1);
		int fd = open(HISTORY_PATH, O_RDONLY);
		int i = 0;
		while (get_next_line(fd, &fuck))
		{
			if (i == num)
				return (fuck);
			i++;
			free(fuck);
		}
		fuck = ft_strdup("no-fuck ");
		fuck = ft_strjoin(fuck, ft_itoa(num));
		return (ft_strdup(fuck));
	}
	return (ft_strdup(line.cmd));
}
