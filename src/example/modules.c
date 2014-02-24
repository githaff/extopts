#include <stdio.h>

#include "extopts/extopts.h"
#include "extopts/extmods.h"


int opts_help;
int		opts_int;
long		opts_lint;
long long	opts_llint;
unsigned			opts_uint;
unsigned long		opts_ulint;
unsigned long long	opts_ullint;
float		opts_float;
double		opts_double;
long double	opts_ldouble;
const char *opts_str;
char opts_alloc_str[256];
char opts_char;

struct extopt int_opts[] = {
	{
		.name_long = "int",
		.name_short = 'i',
		EXTOPT_ARG_INT("INT", &opts_int),
		.desc = "int option",
	}, {
		.name_long = "lint",
		EXTOPT_ARG_LINT("LINT", &opts_lint),
		.desc = "long int option",
	}, {
		.name_long = "llint",
		EXTOPT_ARG_LLINT("LLINT", &opts_llint),
		.desc = "long long int option",
	},
	EXTOPTS_HELP(&opts_help),
	EXTOPTS_END
};

struct extopt uint_opts[] = {
	{
		.name_long = "uint",
		.name_short = 'u',
		EXTOPT_ARG_UINT("UINT", &opts_uint),
		.desc = "unsigned int option",
	}, {
		.name_long = "ulint",
		EXTOPT_ARG_ULINT("LUINT", &opts_ulint),
		.desc = "unsigned long int option",
	}, {
		.name_long = "ullint",
		EXTOPT_ARG_ULLINT("ULLINT", &opts_ullint),
		.desc = "unsigned long long int option",
	},
	EXTOPTS_HELP(&opts_help),
	EXTOPTS_END
};

struct extopt float_opts[] = {
	{
		.name_long = "float",
		.name_short = 'f',
		EXTOPT_ARG_FLOAT("FLOAT", &opts_float),
		.desc = "float option",
	}, {
		.name_long = "double",
		EXTOPT_ARG_DOUBLE("DOUBLE", &opts_double),
		.desc = "double option",
	}, {
		.name_long = "ldouble",
		EXTOPT_ARG_LDOUBLE("LDOUBLE", &opts_ldouble),
		.desc = "long double option",
	},
	EXTOPTS_HELP(&opts_help),
	EXTOPTS_END
};

struct extopt str_opts[] = {
	{
		.name_long = "str",
		EXTOPT_ARG_STR("STR", &opts_str),
		.desc = "string option",
	}, {
		.name_long = "str-alloc",
		EXTOPT_ARG_STR_ALLOC("STR", &opts_alloc_str),
		.desc = "allocated string option",
	}, {
		.name_long = "char",
		EXTOPT_ARG_CHAR("SYMBOL", &opts_char),
		.desc = "single symbol option",
	},
	EXTOPTS_HELP(&opts_help),
	EXTOPTS_END
};

void common_usage(struct extopt *opts)
{
	printf("Usage: %s [COMMAND_OPTIONS]\n"
		   "This is extopts test.\n"
		   "\n"
		   "Options:\n", extmodname);
	extopts_usage(opts);
}

int common_output(int argc, char *argv[], struct extopt opts[])
{
	int ret = 0;
	int i;

	printf("Passed arguments list:\n");
	for (i = 0; i < argc; i++)
		printf("  %s\n", argv[i]);
	printf("\n");

	printf("Parsing command line arguments...\n");
	ret = extopts_get(&argc, argv, opts);
	if (ret)
		goto err;

	if (opts_help) {
		common_usage(opts);
		goto end;
	}
	
	printf("Application name: %s\n", extname);
	printf("Application full path: %s\n", extpath);
	printf("Module name: %s\n", extmodname);
	printf("\n");

	printf("Arguments list after extopts parsing:\n");
	for (i = 0; i < argc; i++)
		printf("  %s\n", argv[i]);
	printf("\n");

err:
end:
	return ret;
	
}


int int_module(int argc, char *argv[])
{
	int ret = 0;
	
	printf("Integer module is executed\n");

	ret = common_output(argc, argv, int_opts);
	if (ret)
		goto err;

	printf("Configurable parameters list:\n");
	printf("  opts_int = %d\n", opts_int);
	printf("  opts_long = %ld\n", opts_lint);
	printf("  opts_long_long = %lld\n", opts_llint);

err:
	return ret;
}

int uint_module(int argc, char *argv[])
{
	int ret = 0;
	
	printf("Unsigned integer module is executed\n");

	ret = common_output(argc, argv, uint_opts);
	if (ret)
		goto err;

	printf("Configurable parameters list:\n");
	printf("  opts_unsign = %u\n", opts_uint);
	printf("  opts_unsigned_long = %lu\n", opts_ulint);
	printf("  opts_unsigned_long_long = %llu\n", opts_ullint);
	
err:
	return ret;
}

int float_module(int argc, char *argv[])
{
	int ret = 0;
	
	printf("Float module is executed\n");

	ret = common_output(argc, argv, float_opts);
	if (ret)
		goto err;

	printf("Configurable parameters list:\n");
	printf("  opts_float = %f\n", opts_float);
	printf("  opts_double = %lf\n", opts_double);
	printf("  opts_double_double = %Lf\n", opts_ldouble);

err:
	return ret;
}

int str_module(int argc, char *argv[])
{
	int ret = 0;
	
	printf("String integer module is executed\n");

	ret = common_output(argc, argv, str_opts);
	if (ret)
		goto err;

	printf("Configurable parameters list:\n");
	printf("  opts_str = %s\n", opts_str);
	printf("  opts_alloc_str = %s\n", opts_alloc_str);
	printf("  opts_char = %c\n", opts_char);

err:
	return ret;
}


EXTMOD_DECL(int, int_module, int_opts)
EXTMOD_DECL(uint, uint_module, uint_opts)
EXTMOD_DECL(float, float_module, float_opts)
EXTMOD_DECL(str, str_module, str_opts)
