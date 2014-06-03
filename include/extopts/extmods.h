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
	char *desc_short;
	char *desc;
};

#define EXTMOD_DECL(NAME, EXEC, OPTS, DESC_SHORT, DESC)			\
	struct extmod *extmod_##NAME;								\
	void extmod_constr_##NAME() __attribute__ ((constructor));	\
	void extmod_constr_##NAME()									\
	{															\
		extmod_##NAME = &extmods[extmods_num++];				\
		extmod_##NAME->name = #NAME;							\
		extmod_##NAME->exec = EXEC;								\
		extmod_##NAME->opts = OPTS;								\
		extmod_##NAME->desc_short = DESC_SHORT;								\
		extmod_##NAME->desc = DESC;					\
	}

extern struct extmod extmods[];
extern int extmods_num;
extern struct extmod *extmod;
extern char extmodname[];

struct extmod *extmod_find(char *name);
struct extmod *extmod_extract(int *argc, char *argv[]);
int extmod_exec(int argc, char *argv[], struct extmod *module);

void extmod_print_desc(struct extmod *module);
void extmod_print_opts(struct extmod *module);

char extmod_has_name(struct extmod *module);
char extmod_has_desc(struct extmod *module);
char extmod_has_opts(struct extmod *module);

void extmods_usage_list(void);

#endif /* __EXTMODS_H */
