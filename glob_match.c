/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_match.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 10:31:01 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/09/07 13:40:06 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line.h"

int glob_match(char const *pat, char const *str)
{
	/*
	 * Backtrack to previous * on mismatch and retry starting one
	 * character later in the string.  Because * matches all characters
	 * (no exception for /), it can be easily proved that there's
	 * never a need to backtrack multiple levels.
	 */
	char const *back_pat = NULL, *back_str = back_str;

	/*
	 * Loop over each token (character or class) in pat, matching
	 * it against the remaining unmatched tail of str.  Return false
	 * on mismatch, or true after matching the trailing nul bytes.
	 */
	for (;;) {
		unsigned char c = *str++;
		unsigned char d = *pat++;

		switch (d) {
		case '?':	/* Wildcard: anything but nul */
			if (c == '\0')
				return 0;
			break;
		case '*':	/* Any-length wildcard */
			if (*pat == '\0')	/* Optimize trailing * case */
                return 1;
			back_pat = pat;
			back_str = --str;	/* Allow zero-length match */
			break;
		case '[': {	/* Character class */
            int match = 0, inverted = (*pat == '!');
			char const *class = pat + inverted;
			unsigned char a = *class++;

			/*
			 * Iterate over each span in the character class.
			 * A span is either a single character a, or a
			 * range a-b.  The first span may begin with ']'.
			 */
			do {
				unsigned char b = a;

				if (a == '\0')	/* Malformed */
					goto literal;

				if (class[0] == '-' && class[1] != ']') {
					b = class[1];

					if (b == '\0')
						goto literal;

					class += 2;
					/* Any special action if a > b? */
				}
				match |= (a <= c && c <= b);
			} while ((a = *class++) != ']');

			if (match == inverted)
				goto backtrack;
			pat = class;
			}
			break;
		case '\\':
			d = *pat++;
			/*FALLTHROUGH*/
		default:	/* Literal character */
literal:
			if (c == d) {
				if (d == '\0')
					return 1;
				break;
			}
backtrack:
			if (c == '\0' || !back_pat)
				return 0;	/* No point continuing */
			/* Try again from last *, one character later in str. */
			pat = back_pat;
			str = ++back_str;
			break;
		}
    }
}
