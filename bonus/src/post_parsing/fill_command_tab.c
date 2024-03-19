/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_command_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:40:57 by dan               #+#    #+#             */
/*   Updated: 2024/03/19 16:26:33 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fill_command_tab.h"

/**========================================================================
 *                           fill_command_tab
 *========================================================================**/
char	***fill_command_tab(char ***cmd_tab, t_ast_nde *node)
{
	t_ast_nde	*start;
	int			i;
	int			redir_were_added;
	int			cmd_was_added;
	int			jok_flag;

	i = intitialize_variables(&jok_flag, &cmd_was_added, &redir_were_added);
	start = node;
	while (node)
	{
		if (node == start || is_separator(node))
		{
			cmd_tab = add_sep_tab_loop(&cmd_tab, &node, &i, &redir_were_added);
			cmd_was_added = 0;
		}
		cmd_tab = add_redir_tabs_loop(cmd_tab, &node, &redir_were_added, &i);
		cmd_tab = add_remaining_tabs_loop(cmd_tab, node, &cmd_was_added, &i);
		if (node->token == DOLL || node->token == JOKER || node->token == STAT)
		{
			free(node->start);
			node->start = NULL;
		}
		node = node->sibling;
	}
	return (cmd_tab);
}

/**========================================================================
 *                           intitialize_variables
 *========================================================================**/
int	intitialize_variables(int *jok_flag, int *cmd_was_added,
	int *redir_were_added)
{
	int	i;

	*jok_flag = 0;
	*cmd_was_added = 0;
	*redir_were_added = 0;
	i = 0;
	return (i);
}

/**========================================================================
 *                           add_redir_tabs_loop
 *========================================================================**/
char	***add_redir_tabs_loop(char ***cmd_tab, t_ast_nde **node,
		int *redir_were_added, int *i)
{
	t_ast_nde	*current;

	if (*redir_were_added == 0)
	{
		current = *node;
		while (!is_separator(current))
		{
			if (is_chevron(current))
			{
				cmd_tab = add_redir_tabs(cmd_tab, &current, i);
			}
			current = current->sibling;
		}
		*redir_were_added = 1;
	}
	return (cmd_tab);
}

/**========================================================================
 *                           add_remaining_tabs_loop
 *========================================================================**/
char	***add_remaining_tabs_loop(char ***cmd_tab, t_ast_nde *node,
		int *cmd_was_added, int *i)
{
	if (*cmd_was_added == 0)
	{
		cmd_tab[*i] = add_remaining_tabs(cmd_tab[*i], node);
		*cmd_was_added = 1;
		(*i)++;
	}
	return (cmd_tab);
}

/**========================================================================
 *                           add_sep_tab_loop
 *========================================================================**/
char	***add_sep_tab_loop(char ****cmd_tab, t_ast_nde **node,
	int *i, int	*redir_were_added)
{
	if (is_separator(*node) && (*node)->sibling)
	{
		(*cmd_tab)[*i] = add_sep_tab((*cmd_tab)[*i], *node);
		*node = (*node)->sibling;
		(*i)++;
	}
	*redir_were_added = 0;
	return (*cmd_tab);
}
