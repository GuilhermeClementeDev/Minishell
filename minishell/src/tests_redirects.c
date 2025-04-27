#include "minishell.h"

static void	run_test(const char *input, int expected)
{
	int	result;

	result = verify_redirects(input);
	if (result == expected)
		printf("OK: \"%s\"\n", input);
	else
		printf("FAIL: \"%s\" (expected %d, got %d)\n",
			input, expected, result);
}

int	main(void)
{
	run_test("> out.txt", 0);
	run_test(">> out.txt", 0);
	run_test("ls > out.txt", 0);
	run_test("cat < in.txt", 0);
	run_test("> > out.txt", 1);
	run_test("ls > | wc", 1);
	run_test("ls >", 1);
	run_test("cat <", 1);
	run_test("", 0);
	return (0);
}
