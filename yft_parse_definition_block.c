/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_parse_definition_block.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 21:27:02 by topiana-          #+#    #+#             */
/*   Updated: 2026/02/10 16:22:02 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"
// #include <stdio.h>

#define SIZEOF_DIR_NUMS 6

const char *g_def_block_directives[SIZEOF_DIR_NUMS] = {
	"font=",
	"width=",
	"heigth=",
	"space=",
	"colors=",
	NULL
};

const char *g_forbidden_ascii = "\"";

int g_parsing_width = 0;
int	g_parsing_heigth = 0;

// ".c0x0f213f"
#define COLOR_LEN 12

int	yft_parse_definition_block(char **monoline);

// NULL error, ptr all good
static char	*extract_definition_block(char **monoline)
{
	size_t	i;
	char	*block;

	i = 0;
	while ((*monoline)[i] != '\0' && (*monoline)[i] != '}')
		++i;
	if ((*monoline)[i] == '\0')
		return (NULL);
	block = ft_substr((*monoline), 0, i + 1);
	if (block == NULL)
		return (NULL);
	(*monoline) = (*monoline) + i + 1;
	return (block);
}

// ".c0x0f213f"
static int parse_colors(char **colors)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (colors[i] != 0)
	{
		// printf("[definition] parsing color '%s'\n", colors[i]);
		len = ft_strlen(colors[i]);
		if (colors[i][0] != '"' || colors[i][len - 1] != '"')
			return (1);
		if (ft_strichr(g_forbidden_ascii, colors[i][1]) != 0)
			return (1);
		if (len != COLOR_LEN)
		{
			if (ft_strcmp((colors[i] + 2), "cVoid") != 0)
				return (1);
		}
		else
		{
			if (!starts_with(colors[i] + 2, "c0x")
				|| ft_strset(colors[i] + 5, "\"abcdef0123456789"))
				return (1);
		}
		++i;
	}

	return (0);
}

static int	parse_directives(char **dirs)
{
	int		found[SIZEOF_DIR_NUMS];
	size_t	i, j;

	ft_memset(found, 0, sizeof(found));

	i = 0;
	do
	{
		// printf("[definition] parsing directive '%s'\n", dirs[i]);
		if (dirs[i] == NULL) goto error;
		j = 0;
		while (j < SIZEOF_DIR_NUMS)
		{
			if (starts_with(dirs[i], (char *)g_def_block_directives[j]))
			{
				// printf("[definition] found directive '%s'\n", g_def_block_directives[j]);
				if (found[j] != 0) goto error;
				if (j == 1) g_parsing_width = ft_atoi(&dirs[i][6]);
				if (j == 2) g_parsing_heigth = ft_atoi(&dirs[i][7]);
				found[j] = 1;
				break ;
			}
			++j;
		}
		if (j == SIZEOF_DIR_NUMS)
		{
			// printf("asd");
			goto error;
		}
		++i;
	}
	while (found[4] == 0);
	if (parse_colors(&dirs[i]))
		return (1);
	return (0);
error:
	// printf("[definition] An error occured\n");
	return (1);
}
// RETURN: 0 all good, 1 parse error, 2 internal error, 3 finished parsing
int	yft_parse_definition_block(char **monoline)
{
	char *const	block = extract_definition_block(monoline);
	char		**dirs;
	size_t		len;
	int			ret;

	if (block == NULL)
		return (2);
	// printf("[definition] extracted '%s'\n", block);
	// printf("[definition] new monoline '%s'\n", *monoline);
	if (*block != '{')
		return (free(block), 1);
	len = ft_strlen(block);
	block[len - 1] = '\0';
	dirs = ft_split(block + 1, ',');
	free(block);
	if (dirs == NULL)
		return (2);
	ret = parse_directives(dirs);
	ft_free_mtx((void **)dirs);
	// printf("got width=%d, heigth=%d\n", g_parsing_width, g_parsing_heigth);
	if (g_parsing_heigth == 0 || g_parsing_width == 0)
		return (1);
	return (ret);
}
