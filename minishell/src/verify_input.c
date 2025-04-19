#include "minishell.h"

// Função que verifica se a string tem aspas não fechadas
// e retorna 1 se tiver erro, 0 se não tiver
int verify_quotes(const char *str)
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' && double_quotes % 2 == 0)
			single_quotes++;
		else if (str[i] == '\"' && single_quotes % 2 == 0)
			double_quotes++;
		i++;
	}
	// Verifica se as aspas não estão fechadas, e retorna erro
	if (single_quotes % 2 != 0 || double_quotes % 2 != 0)
		return (1);
	return (0);
	}


//essa função ta erradaaaa "teste >  > outr_teste"
int	verify_redirects(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (inside_quotes(str, i))
		{
			i++;
			continue;  // Se dentro de aspas, ignora o redirecionamento
		}
		if (str[i] == '>' || str[i] == '<')
		{
			if (str[i+1] == str[i])
				i++;
			if (str[i+1] == '\0' || is_delimiter(str[i+1]))
				return (1);  // Erro: Redirecionamento sem arquivo ou argumento
			if ((str[i + 1] == '>' || str[i + 1] == '<')) //is_delimiter(str[i + 2])
				return (1); // Erro: Redirecionamento seguido de outro redirecionamento
		}
		i++;
	}
	return 0;  // Tudo certo com os redirecionamentos
}


int check_syntax_error(const char *str)
{
	if (verify_quotes(str))  // Chama a função de verificação
	{
		ft_putstr_fd("Syntax error: unclosed quotes\n",2);
		return (1);
	}
	if (verify_redirects(str))  // Chama a função de verificação
	{
		ft_putstr_fd("Syntax error: invalid redirection\n",2);
		return (1);
	}
	//tratar posteriormente
	if (ft_strchr(str, '|') && str[0] == '|')
	{
		ft_putstr_fd("Syntax error: unexpected token '|'\n",2);
		return (1);
	}
	if (ft_strchr(str, '|') && str[ft_strlen(str) - 1] == '|')
	{
		ft_putstr_fd("Syntax error: unexpected token '|'\n",2);
		return (1);
	}
	return (0);
}
