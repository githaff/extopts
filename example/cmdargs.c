#include <stdlib.h>

#include "extopts/extopts.h"
#include "cmdargs.h"


/* Options */
int opts_help;
int			opts_int;
long		opts_lint;
long long	opts_llint;
unsigned 			opts_uint;
unsigned long		opts_ulint;
unsigned long long	opts_ullint;
float 		opts_float;
double		opts_double;
long double	opts_ldouble;
const char *opts_str;
char opts_alloc_str[256];
char opts_symb;
int opts_special_val;
int opts_special_setter(struct extopt *opt, const char *arg)
{
	opts_special_val = strtol(arg, NULL, 0) * 2;
}

struct extopt test_opts[] = {
	{
		.name_long = "help",
		.name_short = 'h',
		EXTOPT_NO_ARG(&opts_help),
		.desc = "print this help",
	}, {
		.name_long = "int",
		.name_short = 'i',
		EXTOPT_ARG_INT("INT", &opts_int),
		.desc = "int option",
	}, {
		.name_long = "long-int",
		EXTOPT_ARG_LINT("LINT", &opts_lint),
		.desc = "long int option",
	}, {
		.name_long = "long-long-int",
		EXTOPT_ARG_LLINT("LLINT", &opts_llint),
		.desc = "long long int option",
	}, {
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
	}, {
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
	}, {
		.name_long = "str",
		EXTOPT_ARG_STR("STR", &opts_str),
		.desc = "string option",
	}, {
		.name_long = "str-alloc",
		EXTOPT_ARG_STR_ALLOC("STR", &opts_alloc_str),
		.desc = "allocated string option",
	}, {
		.name_long = "special",
		EXTOPT_ARG_SPECIAL("INT", &opts_special_setter),
		.desc = "special option (int x2)",
	},
	EXTOPTS_END
};
