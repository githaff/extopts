#ifndef __CMDARGS_H
#define __CMDARGS_H

extern int opts_help;
extern int opts_int;
extern long opts_lint;
extern long long opts_llint;
extern unsigned opts_uint;
extern unsigned long opts_ulint;
extern unsigned long long opts_ullint;
extern float opts_float;
extern double opts_double;
extern long double opts_ldouble;
extern const char *opts_str;
extern char opts_alloc_str[];
extern char opts_symb;
extern int opts_special_val;

extern struct extopt test_opts[];

#endif /* __CMDARGS_H */
