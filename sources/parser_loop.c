/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:09:29 by sponthus          #+#    #+#             */
/*   Updated: 2024/06/23 19:13:11 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_non_operator(t_token *co, t_block *head, int *i)
{
	if (co->str || (co->str && co->str[0] != 0 && co->quote == 0))
	{
		head->args[*i] = ft_strdup(co->str);
		(*i)++;
	}
}

int	handle_operator_pipe(t_data *data, t_token **co, t_block **he, int *i)
{
	int	val;

	val = parse_operators(data, *co, *i);
	if (val != 0)
	{
		while ((*co)->next)
		{
			if ((*co)->next->type == PIPE)
				break ;
			*co = (*co)->next;
		}
	}
	if (val != 0 && !(*co)->next)
		return (val);
	if (ft_strncmp("|", (*co)->str, 1) == 0)
	{
		*i = 0;
		*he = (*he)->next;
	}
	else if (val == 0)
	{
		*co = (*co)->next;
	}
	return (0);
}

int	is_operator_or_pipe(t_token *co)
{
	if (co->type == OP || co->type == PIPE)
		return (1);
	else
		return (0);
}
