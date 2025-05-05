#include "minishell.h"

int	handle_redirect(t_token **token, t_redirect **redirects)
{
	t_redirect	*new;

	new = malloc(sizeof(t_redirect));
	if (!new)
		return (0);
	new->type = (*token)->type;
	if ((*token)->next && (*token)->next->type == T_WORD)
	{
		new->filename = ft_strdup((*token)->next->value);
		new->next = *redirects;
		*redirects = new;
		*token = (*token)->next; // pula o nome do arquivo
	}
	return (1);
}

int	is_redirect_type(int type)
{
	return (type == T_RED_IN || type == T_RED_OUT
		|| type == T_HEREDOC || type == T_APPEND);
}
