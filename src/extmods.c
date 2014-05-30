#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

#include "extopts/extopts.h"
#include "extopts/extmods.h"


struct extmod extmods[64];
int extmods_num = 0;
char extmodname[255];

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
	int argc_tmp;
	char **argv_tmp;
	int ret = 0;
	int i;

	argc_tmp = argc - 1;
	argv_tmp = (char **)calloc(argc_tmp, sizeof(char *));
	argv_tmp[0] = argv[0];
	for (i = 1; i < argc_tmp; i++)
		argv_tmp[i] = argv[i + 1];

	sprintf(extmodname, "%s-%s", basename(argv[0]), argv[1]);

	if (module && module->exec)
		ret = module->exec(argc_tmp, argv_tmp);

	extmodname[0] = 0;
	free(argv_tmp);

	return ret;
}

/*
 * Print module description.
 */
void extmod_print_desc(struct extmod *module)
{
	if (module->desc_long)
		puts(module->desc_long);
	else
		printf("--no description for %s module--\n", module->name);
}

/*
 * Print module options.
 */
void extmod_print_opts(struct extmod *module)
{
	if (module->opts)
		extopts_usage(module->opts);
}
