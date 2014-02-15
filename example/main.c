#include <stdio.h>

#include "extopts/extopts.h"
#include "cmdargs.h"


char test_name[] = "test";
int test_name_len = sizeof(test_name);
void test_usage(struct extopt *opts)
{
	printf("Usage: %s [OPTIONS] COMMAND [COMMAND_OPTIONS]\n"
		   "This is extopts test.\n"
		   "\n"
		   "Options:\n", test_name);
	extopts_usage(opts);
}


int main(int argc, char *argv[])
{
	int i;
	int ret = 0;
	struct extmod *module;
	int index;

	index = extopts_get(&argc, argv, test_opts);
	if (index < 0) {
		ret = 1;
		goto err;
	}

	if (opts_help) {
		test_usage(test_opts);
		goto end;
	}

	printf("Application name: %s\n", extname);
	printf("Application full path: %s\n", extpath);
	printf("Passed arguments list:\n");
	if (argc == 0)
		printf("  --none--\n");
	else
		for (i = 0; i < argc; i++)
			printf("  %s\n", argv[i]);
	printf("Parameters read:\n");
	printf("  opts_int = %d\n", opts_int);
	printf("  opts_long = %ld\n", opts_lint);
	printf("  opts_long_long = %lld\n", opts_llint);
	printf("  \n");
	printf("  opts_unsign = %u\n", opts_uint);
	printf("  opts_unsigned_long = %lu\n", opts_ulint);
	printf("  opts_unsigned_long_long = %llu\n", opts_ullint);
	printf("  \n");
	printf("  opts_float = %f\n", opts_float);
	printf("  opts_double = %lf\n", opts_double);
	printf("  opts_double_double = %Lf\n", opts_ldouble);
	printf("  \n");
	printf("  opts_str = %s\n", opts_str);
	printf("  opts_alloc_str = %s\n", opts_alloc_str);
	printf("  opts_symb = %c\n", opts_symb);
	printf("  \n");
	printf("  opts_special_val = %d\n", opts_special_val);

err:
end:

	return ret;
}
