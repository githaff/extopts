#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

#include "extopts/extopts.h"
#include "extopts/extmods.h"

#define EXTMODS_OPTS_STR "[[OPTIONS]]"


struct extmod extmods[64];
int extmods_num = 0;
char extmodname[255];
struct extmod *extmod;



/*
 * Extract module name from command line arguments.
 * Module name in:
 *   argv[0] - leave arguments unchanged;
 *   argv[1] - remove this argument.
 * If no module was found than for sanity better check if execname is correct.
 * It would be strange if some utility called with unexpected name will act
 * like usual.
 */
struct extmod *extmod_extract(int *argcp, char *argv[])
{
	struct extmod *module;
	char *execname;
	int argc = *argcp;
	int i;

	execname = basename(argv[0]);

	module = extmod_find(execname);
	if (!module && argc > 1) {
		module = extmod_find(argv[1]);
		if (module)
		{
			argc--;
			for (i = 1; i < argc; i++)
				argv[i] = argv[i+1];
			*argcp = argc;
		}
	}

	return module;
}

/*
 * Find extmodule with specified name.
 */
struct extmod *extmod_find(char *name)
{
	int i;

	for (i = 0; i < extmods_num; i++) {
		if (!strcmp(name, extmods[i].name))
			return &extmods[i];
	}

	return 0;
}

/*
 * Execute module with passing rest of arguments as if it was runned
 * from simple main() function.
 */
int extmod_exec(int argc, char *argv[], struct extmod *module)
{
	char *execname;
	int ret = 0;

	if (!module)
		return 1;

	execname = basename(argv[0]);
	extmod = module;
	sprintf(extmodname, "%s-%s", execname, module->name);

	if (module->exec)
		ret = module->exec(argc, argv);

	extmodname[0] = 0;
	extmod = 0;

	return ret;
}

/*
 * Print module description.
 * Replaces options keyword with module options printed with
 * extmod_print_opts()
 */
void extmod_print_desc(struct extmod *module)
{
	int desc_len;
	char *buf;
	char *opts_str;

	if (module->desc) {
		desc_len = strlen(module->desc);
		buf = (char *)malloc(desc_len + 1);
		strcpy(buf, module->desc);

		opts_str = strstr(buf, EXTMODS_OPTS_STR);
		if (opts_str) {
			*opts_str = 0;
			printf(buf);
			extmod_print_opts(module);
			opts_str += strlen(EXTMODS_OPTS_STR);
			puts(opts_str);
		}
		else
			puts(module->desc);

		free(buf);
	}
	else
		puts("No description");
}

/*
 * Print module options.
 */
void extmod_print_opts(struct extmod *module)
{
	if (module->opts)
		extopts_usage(module->opts);
}

char extmod_has_name(struct extmod *module)
{ return module->name ? 1 : 0; }
char extmod_has_desc(struct extmod *module)
{ return module->desc ? 1 : 0; }
char extmod_has_opts(struct extmod *module)
{ return module->opts ? 1 : 0; }
char extmod_is_end(struct extmod opt)
{
	return opt.name == 0 &&
		opt.opts == 0 &&
		opt.exec == 0;
}
