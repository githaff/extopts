#include <stdio.h>
#include <stdlib.h>

#include "extopts/extopts.h"
#include "extopts/extmods.h"

#include "config.h"


/* Options */
int opts_help;
int opts_version;
int opts_special_val;
int opts_special_setter(struct extopt *opt, const char *arg)
{
	(void)opt;

	opts_special_val = strtol(arg, NULL, 0) * 2;

	return 0;
}

struct extopt opts[] = {
	{
		.name_long = "special",
		EXTOPT_ARG_SPECIAL("INT", &opts_special_setter),
		.desc = "special option (takes integer and multiplies it on 2)",
	},
	EXTOPTS_HELP(&opts_help),
	EXTOPTS_VERSION(&opts_version),
	EXTOPTS_END
};

void print_usage(struct extopt *opts)
{
	printf("Usage: %s [OPTIONS] COMMAND [COMMAND_OPTIONS]\n"
		   "This is extopts test.\n"
		   "\n"
		   "Options:\n", extname);
	extopts_usage(opts);
}

void print_version()
{
	printf("extopts %s example\n", EXTOPTS_VERSION_FULL);
}


int main(int argc, char *argv[])
{
	int i;
	int ret = 0;
	struct extmod *module = 0;

	if (argc > 1)
		module = extmod_find(argv[1]);

	if (module)
		ret = extmod_exec(argc, argv, module);
	else {
		ret = extopts_get(&argc, argv, opts);
		if (ret)
			goto err;

		if (opts_help) {
			print_usage(opts);
			goto end;
		} else if (opts_version) {
			print_version();
			goto end;
		}

		printf("Application name: %s\n", extname);
		printf("Application full path: %s\n", extpath);
		printf("\n");
		printf("Arguments list after extopts parsing:\n");
		for (i = 0; i < argc; i++)
			printf("  %s\n", argv[i]);
		if (i == 0)
			printf("  --none--\n");
		printf("\n");
		printf("Configurable parameters list:\n");
		printf("  opts_help = %d\n", opts_help);
		printf("  opts_version = %d\n", opts_version);
		printf("  opts_special_val = %d\n", opts_special_val);
	}


err:
end:

	return ret;
}
