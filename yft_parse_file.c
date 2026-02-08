/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_parse_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 03:26:13 by totommi           #+#    #+#             */
/*   Updated: 2026/02/08 22:19:15 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"
#include <stdio.h>

int	yft_parse_file(char *path);

const char *g_def_block_directives[] = {
	"font",
	"width",
	"heigth",
	"space",
	"colors",
	NULL
};

// ".c0x0f213f"
#define COLOR_LEN 12

size_t	g_line = 0;

// call this when you find the first bracket of the file
/* 
	font="Wobbly",
	width=16,
	height=16,
	space=0,
	colors=4,
	". c 0x0f213f",
	"# c 0xff00ac",
	"@ c 0x00ffa2",
	"x c 0xff0000"
*/
static int	parse_definition_block(char *block, size_t start_line)
{
	char			**split/*  = ft_split(block, ',') */;
	unsigned int	i;
	unsigned int	j;
	short			found[6];
	

	ft_memset(found, 0, sizeof(found));

	printf("Definition block: '%s'\n", block);

	split = ft_split(block, ',');	// #todo free this
	if (split == NULL)
		return (2);

	i = 0;
	while (split[i] != NULL)
	{
		j = 0;
		while (g_def_block_directives[j] != NULL)
		{
			if (ft_strnstr(split[i], g_def_block_directives[j], ft_strlen(split[i])))
			{
				found[j] = 1;
				break ;
			}
			++j;
		}
		if (g_def_block_directives[j] == NULL)
		{
			fprintf(stderr, "yft: Unknown directive '%s', block line %zu\n", split[i], start_line);
			return (3);
		}
		if (found[4] == 1)
		{
			if (!found[0] || !found[1] || !found[2])
			{
				fprintf(stderr, "yft: Missing directive(s), block line %zu\n", start_line);;
				return (3);

			}
			else
			{
				++i;
				break;
			}
		}
		++i;
	}

	int err;

	err = 0;

	while (split[i] != NULL)
	{
		if (split[i][1] != 'c')
		{
			err = 1;
			break ;
		}
		if (ft_strlen(split[i]) != COLOR_LEN)
		{
			if (ft_strcmp(&split[i][2], "Void") != 0)
			{
				err = 1;
				break ;
			}
		}

		// #todo check color format

		++i;
	}

	if (err != 0)
	{
		fprintf(stderr, "yft: Invalid color directive '%s', block line %zu\n", split[i], start_line);
		return (3);
	}

	return (1);


}


// 1 ok, 2 malloc failre, 3 parsing error
static int build_static_block(char c, size_t len, int (*parse)(char*, size_t))
{
	static size_t	start_line;
	static size_t	curr;
	static char		*cleanblock;
	int				ret;

	if (parse == NULL)
		return (2);
	if (!cleanblock)
	{
		cleanblock = ft_calloc(len, sizeof(char));
		if (!cleanblock) return (1);

		// printf("[building] mallocated\n");
	}
	else
	{
		// printf("[building] got '%c'\n", c);

		if (curr == 0)
		{
			if (c != '{')
			{
				fprintf(stderr, "yft: Invalid char, line %zu\n", g_line);
				free(cleanblock);
				cleanblock = NULL;
				return (3);
			}
			start_line = g_line;
			curr++;
		}
		else if (curr != 0 && (c == '\0' || c == '{'))
		{
			fprintf(stderr, "yft: Unclosed block line %zu\n", g_line);
			free(cleanblock);
			cleanblock = NULL;
			curr = 0;
			start_line = 0;
			return (3);
		}
		else if (curr != 0 && c == '}')
		{
			ret = (*parse)(cleanblock, start_line);
			free(cleanblock);
			cleanblock = NULL;
			curr = 0;
			start_line = 0;
			return (ret);
		}
		else
		{
			cleanblock[curr - 1] = c;
			++curr;
		}
	}
	
	return (0);
}

// skips blanck spaces and comments until a valid char is found.
// RETURNS: the index of the char in the file string, -1 if not found
static int	skip_blank_or_comments(char *file, int start, int (*f)(char, size_t, int (*parse)(char*, size_t)), int (*parse)(char*, size_t))
{
	const size_t	len = ft_strlen(&file[start]);
	int				i;
	short			skip;
	char			comment;

	if (f != NULL && f('\0', len, parse) != 0)
		return -1;

	comment = '\0';
	i = start;
	while (file[i] != '\0')
	{

		// printf("scanning char '%c'\n", file[i]);

		if (file[i] == '\n') ++g_line;

		// check if comment finished
		if ((comment == '/' && file[i] == '\n')
			|| (comment == '*' && file[i] == '*' && file[i + 1] == '/'))
		{

			// printf("found end of comment '%c'\n", comment);

			++i;
			if (comment == '*') ++i;

			comment = '\0';
			skip = 0;
			continue ;
		}

		// skip commented lines && blanck chars
		if (skip == 1 || ft_isspace(file[i]))
		{
			// printf("skipping...\n");
			++i;
			continue;
		}

		// check for comments
		if (file[i] == '/' && file[i + 1] == '/')
		{

			// printf("found '/' comment\n");

			comment = '/';
			skip = 1;
			i += 2;
			continue;
		}
		if (file[i] == '/' && file[i + 1] == '*')
		{
			// printf("found '*' comment\n");

			comment = '*';
			skip = 1;
			i += 2;
			continue;
		}

		// we went trough all checks
		if (f == NULL) break;
		int ret = f(file[i], len, parse);
		if (ret != 0)
			return (ret);

		++i;
	}

	return (i);
}

/* checks for correct parsing of file */
int	yft_parse_file(char *file)
{
	int				head;

	g_line = 0;
	head = skip_blank_or_comments(file, 0, NULL, NULL);

	if (file[head] == '\0')
	{
		write(2, "yft: Empty file\n", 17);
		return (1);
	}

	head = skip_blank_or_comments(file, head - 1, build_static_block, parse_definition_block);
	if (head == -1 || head > 1)
		return (1);
	

	return (0);
}
