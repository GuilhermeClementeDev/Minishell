#include "minishell.h"


static char	*get_env_var_value(const char *var)
{
	char	*value;

	value = getenv(var);
	if (!value)
		return ft_strdup("");  // Se não encontrar, retorna uma string vazia
	return ft_strdup(value);
}

char	*expand_variable(const char *input, int *index)
{
	int		start;
	char	*var_name;
	char	*var_value;

	start = *index;
	// Avança o índice para o próximo caractere após o '$'
	(*index)++;
	// Determina o nome da variável
	while (input[*index] && (isalnum(input[*index]) || input[*index] == '_'))
		(*index)++;
	var_name = ft_substr(input, start + 1, *index - start - 1);
	// Obtém o valor da variável
	var_value = get_env_var_value(var_name);
	free(var_name);
	return var_value;
}

void	expand_variables_in_str(char **str, const char *input)
{
	int		i;
	char	*expanded_str;

	if (!input)
		return ;
	i = 0;
	expanded_str = ft_strdup("");  // Inicializa a string expandida
	while (input[i])
	{
		// Verifica se estamos dentro de aspas simples (não deve expandir)
		if (inside_quotes(input, i) == 1)  // Dentro de aspas simples
		{
			// Não faz expansão, apenas adiciona o caractere ao resultado
			if (!handle_quoted_part(input, &i, &expanded_str))
				return ;
		}
		// Verifica se estamos dentro de aspas duplas (deve expandir)
		else if (input[i] == '$' && inside_quotes(input, i) != 1)
		{
			if (!handle_variable_expansion(input, &i, &expanded_str))
				return ;
		}
		else
		{
			// Para os caracteres normais, apenas adiciona ao resultado
			if (!handle_normal_char(input, &i, &expanded_str))
				return ;
		}
	}
	*str = expanded_str;
}




void	handle_expansion(t_token *token)
{
	char	*expanded_value;

	expanded_value = NULL;  // Inicializa a string expandida
	if (token->type == T_WORD)
	{
		// Expande variáveis no valor do token (somente se não estiver em aspas simples)
		if (!inside_quotes(token->value, 0))  // Se não está dentro de aspas
		{

			expand_variables_in_str(&expanded_value, token->value);
			free(token->value);
			token->value = expanded_value;
		}
	}
}

void	expand_variables_in_token(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		handle_expansion(current);
		current = current->next;
	}
}
