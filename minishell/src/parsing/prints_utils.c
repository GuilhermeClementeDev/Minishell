/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-conc <gda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:03:35 by gda-conc          #+#    #+#             */
/*   Updated: 2025/05/14 15:03:36 by gda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

const char	*token_type_to_str(int type)
{
	if (type == T_WORD)
		return ("WORD");
	else if (type == T_PIPE)
		return ("PIPE");
	else if (type == T_RED_IN)
		return ("REDIR_IN");
	else if (type == T_RED_OUT)
		return ("REDIR_OUT");
	else if (type == T_HEREDOC)
		return ("HEREDOC");
	else if (type == T_APPEND)
		return ("APPEND");
	return ("UNKNOWN");
}

const char	*redir_type_to_str(int type)
{
	if (type == T_RED_IN)
		return ("<");
	else if (type == T_RED_OUT)
		return (">");
	else if (type == T_HEREDOC)
		return ("<<");
	else if (type == T_APPEND)
		return (">>");
	return ("UNKNOWN");
}
