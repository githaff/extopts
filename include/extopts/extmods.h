#ifndef __EXTMODS_H
#define __EXTMODS_H

struct extopt;

/*
 * Module structure.
 */
struct extmod {
	char *name;
	int (*exec)(int argc, char *argv[]);
	struct extopt *opts;
};

#define EXTMOD_DECL(NAME, EXEC, OPTS)							\
	struct extmod *extmod_##NAME;								\
	void extmod_constr_##NAME() __attribute__ ((constructor));	\
	void extmod_constr_##NAME()									\
	{															\
		extmod_##NAME = &extmods[extmods_num++];				\
		extmod_##NAME->name = #NAME;							\
		extmod_##NAME->exec = EXEC;								\
		extmod_##NAME->opts = OPTS;								\
	}

extern struct extmod extmods[];
extern int extmods_num;
extern char extmodname[];

struct extmod *extmod_find(char *name);
int extmod_exec(int argc, char *argv[], struct extmod *module);
inline static char extmod_is_end(struct extmod opt)
{
	return opt.name == 0 &&
		opt.opts == 0 &&
		opt.exec == 0;
}

#endif /* __EXTMODS_H */
