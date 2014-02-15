/*
 * Extended Options management.
 *
 * This is implementation of extended options based on getopt_long
 * from getopt.h functionality.
 *
 * Major advantage is self-documenting ability - pretty options usage
 * can be generated and printed through extopts_usage() function.
 *
 * Usage is changed into a little more simple. Full copy of original
 * getopt functionality can be implemented through _orig structures
 * and functions (in this case extopt_orig will be only wrapping
 * getopt_long implementing identical behaviour so it will be fully
 * compatible).
 */

#ifndef __EXTOPTS_H
#define __EXTOPTS_H

/*
 * Types of option argument.
 * Defines the way argument will be written into @arg field of extopt
 * structure.
 */
enum extopt_argtype {
	/* Field 'arg' will be used as 'flag' pointing to flag for whether
	 * parameter was met in command line or not */
	EXTOPT_ARGTYPE_NO_ARG,
	/* Field 'arg' will be used as 'setter' handler which will be
	 * called for argument parsing */
	EXTOPT_ARGTYPE_SPECIAL,
	/* Field 'arg' will be used as 'addr' pointing to the variable of
	 * corresponding size where parsed parameter argument value will
	 * be stored */
	/* Signed integers */
	EXTOPT_ARGTYPE_INT,
	EXTOPT_ARGTYPE_LINT,
	EXTOPT_ARGTYPE_LLINT,
	/* Unsigned integers */
	EXTOPT_ARGTYPE_UINT,
	EXTOPT_ARGTYPE_ULINT,
	EXTOPT_ARGTYPE_ULLINT,
	/* Floating-point */
	EXTOPT_ARGTYPE_FLOAT,
	EXTOPT_ARGTYPE_DOUBLE,
	EXTOPT_ARGTYPE_LDOUBLE,
	/* Strings */
	EXTOPT_ARGTYPE_STR,		/* Field 'const_str' is used instead of 'addr' */
	EXTOPT_ARGTYPE_STR_ALLOC,
	EXTOPT_ARGTYPE_CHAR,
};

enum {
	no_extarg,
	required_extarg,
};

/*
 * Extended option description structure.
 */
struct extopt {
	char *name_long;
	char name_short;
	char *desc;

	/* Option argument */
	int has_arg;
	char *arg_name;
	enum extopt_argtype arg_type;
	union {
		void *addr;
		const char **const_str;
		int *flag_addr;
		int (*setter)(struct extopt *opt, const char *arg);
	} arg;
};

/* Should be used as end of extopt array */
#define EXTOPTS_END { 0, 0, 0, 0, 0, 0, {0} }

/*
 * Macro for extopt struct initialization depending on option argument
 * type
 */
/* Signed integers */
#define EXTOPT_ARG_INT(NAME, ADDR)			\
	.has_arg = required_extarg,				\
	.arg_name = NAME,						\
	.arg_type = EXTOPT_ARGTYPE_INT,			\
	.arg.addr = ADDR
#define EXTOPT_ARG_LINT(NAME, ADDR)			\
	.has_arg = required_extarg,				\
	.arg_name = NAME,						\
	.arg_type = EXTOPT_ARGTYPE_LINT,		\
	.arg.addr = ADDR
#define EXTOPT_ARG_LLINT(NAME, ADDR)		\
	.has_arg = required_extarg,				\
	.arg_name = NAME,						\
	.arg_type = EXTOPT_ARGTYPE_LLINT,		\
	.arg.addr = ADDR

/* Unsigned integers */
#define EXTOPT_ARG_UINT(NAME, ADDR)			\
	.has_arg = required_extarg,				\
	.arg_name = NAME,						\
	.arg_type = EXTOPT_ARGTYPE_UINT,		\
	.arg.addr = ADDR
#define EXTOPT_ARG_ULINT(NAME, ADDR)		\
	.has_arg = required_extarg,				\
	.arg_name = NAME,						\
	.arg_type = EXTOPT_ARGTYPE_ULINT,		\
	.arg.addr = ADDR
#define EXTOPT_ARG_ULLINT(NAME, ADDR)		\
	.has_arg = required_extarg,				\
	.arg_name = NAME,						\
	.arg_type = EXTOPT_ARGTYPE_ULLINT,		\
	.arg.addr = ADDR

/* Floating-point */
#define EXTOPT_ARG_FLOAT(NAME, ADDR)		\
	.has_arg = required_extarg,				\
	.arg_name = NAME,						\
	.arg_type = EXTOPT_ARGTYPE_FLOAT,		\
	.arg.addr = ADDR
#define EXTOPT_ARG_DOUBLE(NAME, ADDR)		\
	.has_arg = required_extarg,				\
	.arg_name = NAME,						\
	.arg_type = EXTOPT_ARGTYPE_DOUBLE,		\
	.arg.addr = ADDR
#define EXTOPT_ARG_LDOUBLE(NAME, ADDR)		\
	.has_arg = required_extarg,				\
	.arg_name = NAME,						\
	.arg_type = EXTOPT_ARGTYPE_LDOUBLE,		\
	.arg.addr = ADDR

/* Strings */
#define EXTOPT_ARG_STR(NAME, ADDR)			\
	.has_arg = required_extarg,				\
	.arg_name = NAME,						\
	.arg_type = EXTOPT_ARGTYPE_STR,			\
	.arg.const_str = ADDR
#define EXTOPT_ARG_STR_ALLOC(NAME, ADDR)	\
	.has_arg = required_extarg,				\
	.arg_name = NAME,						\
	.arg_type = EXTOPT_ARGTYPE_STR_ALLOC,	\
	.arg.addr = ADDR
#define EXTOPT_ARG_CHAR(NAME, ADDR)			\
	.has_arg = required_extarg,				\
	.arg_name = NAME,						\
	.arg_type = EXTOPT_ARGTYPE_CHAR,		\
	.arg.addr = ADDR

/* Misc */
#define EXTOPT_NO_ARG(FLAG_ADDR)			\
	.has_arg = no_extarg,					\
	.arg_name = NULL,						\
	.arg_type = EXTOPT_ARGTYPE_NO_ARG,		\
	.arg.flag_addr = FLAG_ADDR
#define EXTOPT_ARG_SPECIAL(NAME, SETTER_FUNC)	\
	.has_arg = required_extarg,					\
	.arg_name = NAME,							\
	.arg_type = EXTOPT_ARGTYPE_SPECIAL,			\
	.arg.setter = SETTER_FUNC


void extopts_usage(struct extopt *opts);
int get_extopts(int *argc, char *argv[], struct extopt *opts);

inline static char opt_is_end(struct extopt opt)
{
	return opt.name_long == 0 &&
		opt.name_short	== 0 &&
		opt.has_arg	== 0 &&
		opt.arg_name	== 0 &&
		opt.desc		== 0 &&
		opt.arg_type	== 0 &&
		opt.arg.addr	== 0;
}

#endif /* __EXTOPTS_H */
