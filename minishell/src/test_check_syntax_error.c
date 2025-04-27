#include "minishell.h"

static void	run_test(const char *input, int expected)
{
	int	result;

	result = check_syntax_error(input);
	if (result == expected)
		printf("OK: \"%s\"\n", input);
	else
		printf("FAIL: \"%s\" (expected %d, got %d)\n",
			input, expected, result);
}

int	main(void)
{
	run_test("| ls", 1);
	run_test("ls |", 1);
	run_test("ls || wc", 0);
	run_test("echo 'unclosed", 1);
	run_test("echo \"unclosed", 1);
	run_test("echo 'closed'", 0);
	run_test("echo \"closed\"", 0);
	run_test(">", 1);
	run_test("<", 1);
	run_test("ls > > out.txt", 1);
	run_test("> out.txt", 0);
	run_test("", 0);
	return (0);
}
