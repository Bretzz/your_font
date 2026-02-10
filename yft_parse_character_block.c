/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yft_parse_character_block.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 21:31:20 by topiana-          #+#    #+#             */
/*   Updated: 2026/02/10 16:10:08 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yft_int.h"
// #include <stdio.h>

int	yft_parse_character_block(char **monoline);

// NULL error, ptr all good
static char	*extract_character_block(char **monoline)
{
	size_t	i;
	short	bracket_count;
	char	*block;

	bracket_count = 0;
	i = 0;
	while ((*monoline)[i] != '\0' && bracket_count < 2)
	{
		if ((*monoline)[i] == '}')
			++bracket_count;
		++i;
	}
	if (bracket_count != 2)
		return (NULL);
	block = ft_substr((*monoline), 0, i);
	if (block == NULL)
		return (NULL);
	(*monoline) = (*monoline) + i;
	return (block);
}

static int	parse_character_block(char *block)
{
	const size_t	len = ft_strlen(block);

	if (!starts_with(block, "{ascii=") || block[len - 1] != '}')
		return (1);
	return (yft_parse_glyph_block(block));
}

// RETURN: 0 all good, 1 parse error, 2 internal error, 3 finished parsing
int	yft_parse_character_block(char **monoline)
{
	char *const	block = extract_character_block(monoline);
	int			ret;

	// printf("[character] extracted character block '%s'\n", block);
	if (block == NULL)
	{
		if (**monoline == '\0')
			return (3);
		return (2);
	}
	ret = parse_character_block(block);
	free(block);
	return (ret);
}