#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "extopts/extopts.h"
#include "extopts/extmods.h"
#include "common.h"


#define BUF_SIZE 1024

/* Total line maximal length */
#define MAX_STRLEN 80
/* Minimal description field size */
#define MIN_DESC_SIZE 42
#define MAX_DESC_START (MAX_STRLEN - MIN_DESC_SIZE)
/* Start-of-string tabulation space */
#define TAB_SIZE 2
/* Desirable and minimal distance between option and its description */
#define OPT_DESC_DIST 4
#define MIN_OPT_DESC_DIST 2

char desc_default[] = "no description specified";


/*
 * Check options for validity.
 */
inline static bool option_is_ok(struct extopt *opt)
{
	if (!opt->name_short && !opt->name_long) {
		errmsg("option doesn't have nor short nor long name.\n");
		return false;
	}

	if (opt->has_arg && !opt->arg_name) {
		errmsg("option has required argument but its name is not specified.\n");
		return false;
	}

	return true;
}


/*
 * Get subline of specified maximum @size. Substring will be written to
 * @buffer. Separates strings on ' ' and '\n' symbols.
 * Returns stop-position in original string: first char of next word
 * or end of string if string has ended. NULL - if buffer is too small.
 */
char *get_subline(char *str, char *buf, int size, int buf_size)
{
	int end = 0;
	int i;

	if (!buf_size)
		buf_size = BUF_SIZE;

	for (i = 0; i < buf_size - 1; i++) {
		if (str[i] == '\n' || str[i] == 0) {
			end = i;
			break;
		}

		if (str[i] == ' ')
			end = i;

		if (i >= size && end != 0)
			break;
	}

	if (!end)
		return NULL;

	for (i = 0; i < end; i++)
		buf[i] = str[i];
	buf[i] = 0;

	if (!str[i])
		return str + i;

	return str + i + 1;
}

/*
 * Get printed long option name length.
 */
int get_opt_length(struct extopt *opt)
{
	int len = 0;

	/* Printed format: '--<name> <ARG>' */
	if (opt->name_long)
		len += strlen(opt->name_long) + 2;

	if (opt->has_arg && opt->arg_name)
		len += strlen(opt->arg_name) + 1;

	return len;
}

/*
 * Calculate layout for usage printout.
 * @opts - array of options.
 * @any_short - addr where 0 will be writen if there is at least one
 * option with short name
 * Returns position from which descriptions must be written.
 */
int get_desc_offset(struct extopt *opts, bool *any_short)
{
	int len, i;
	int len_max = 0;
	bool any_long = 0;

	*any_short = 0;

	i = 0;
	while (1) {
		if (extopt_is_end(opts[i]))
			break;

		len = get_opt_length(opts + i);
		if (len_max < len)
			len_max = len;

		if (opts[i].name_long)
			any_long = true;

		if (opts[i].name_short)
			*any_short = true;

		i++;
	}

	if (*any_short)
		len_max += any_long ? 4 : 2;  /* for e.g. '-h, ' or '-h' */

	len_max += TAB_SIZE + OPT_DESC_DIST;

	if (len_max + MIN_DESC_SIZE > MAX_STRLEN)
		return MAX_STRLEN - MIN_DESC_SIZE;

	return len_max;
}

/*
 * Print single option.
 * @opt - pointer to option to be printed.
 * @desc_offset_norm - normal offset with which description will be printed.
 * @any_short - there is at least one option with short name.
 */
void print_opt(struct extopt *opt, int desc_offset_norm, bool any_short)
{
	char buf[BUF_SIZE];
	int bufsize = BUF_SIZE;
	char *str, *desc;
	int desc_offset, desc_size;
	int i;

	if (!option_is_ok(opt))
		return;

	/* Compose tabs */
	for (i = 0; i < TAB_SIZE; i++) {
		buf[i] = ' ';
	}
	str     = buf + i;
	bufsize = BUF_SIZE - i;

	/* Compose short option */
	if (any_short) {
		i += (opt->name_short) ?
			snprintf(str, bufsize, "-%c", opt->name_short) :
			snprintf(str, bufsize, "    ");
	}
	str     = buf + i;
	bufsize = BUF_SIZE - i;

	/* Compose long option */
	if (opt->name_long) {
		i += (opt->name_short) ?
			snprintf(str, bufsize, ", --%s", opt->name_long) :
			snprintf(str, bufsize, "--%s", opt->name_long);
	}
	str     = buf + i;
	bufsize = BUF_SIZE - i;

	/* Compose option argument */
	if (opt->has_arg)
		i += snprintf(str, bufsize, " %s", opt->arg_name);
	str     = buf + i;
	bufsize = BUF_SIZE - i;

	/* Compose and print first line with description start */
	desc = opt->desc ? opt->desc : desc_default;
	desc_offset = (i > MAX_DESC_START) ?
		i + MIN_OPT_DESC_DIST :
		desc_offset_norm;
	desc_size = MAX_STRLEN - desc_offset;
	for (; i < desc_offset; i++)
		buf[i] = ' ';
	str     = buf + i;
	bufsize = BUF_SIZE - i;
	desc = get_subline(desc, str, desc_size, bufsize);
	printf("%s\n", buf);

	/* Print the rest of description */
	desc_offset = desc_offset_norm;
	desc_size = MAX_STRLEN - desc_offset;
	str = buf;
	for (i = 0; i < desc_offset; i++)
		str[i] = ' ';
	str += i;
	while (desc && *desc) {
		desc = get_subline(desc, str, desc_size, bufsize);
		printf("%s\n", buf);
	}
}

/*
 * Prints info about command options in standard usage format.
 * @section - name of optins section. If not-NULL will be printed
 * before options.
 * @opts - array of options, must end with all-zero struct OPTS_END.
 */
void extopts_usage(struct extopt *opts)
{
	int i;
	int desc_offset;
	bool any_short;

	desc_offset = get_desc_offset(opts, &any_short);

	i = 0;
	while (1) {
		if (extopt_is_end(opts[i]))
			break;

		print_opt(opts + i, desc_offset, any_short);

		i++;
	}
}

/*
 * Calculate offset for modules description.
 */
int get_mods_desc_offset(void)
{
	int offset;
	int min_offset;
	int max_modname = 0;
	int i;

	for (i = 0; i < extmods_num; i++)
		if (max_modname < strlen(extmods[i].name))
			max_modname = strlen(extmods[i].name);

	min_offset = TAB_SIZE + max_modname + MIN_OPT_DESC_DIST;
	offset = TAB_SIZE + max_modname + OPT_DESC_DIST;
	if (offset > MAX_DESC_START) {
		if (min_offset < MAX_DESC_START)
			offset = MAX_DESC_START;
		else
			offset = min_offset;
	}

	return offset;
}

/*
 * Prints list of modules with their descriptions.
 */
void extmods_usage_list(void)
{
	int i;
	int offset;
	int desc_offset;
	int desc_size;
	char buf[BUF_SIZE];
	char *desc;

	desc_offset = get_mods_desc_offset();

	for (i = 0; i < extmods_num; i++) {
		desc = extmods[i].desc_short;

		/* Compose first line with module name */
		for (offset = 0; offset < TAB_SIZE; offset++)
			printf(" ");
		printf("%s", extmods[i].name);
		offset += strlen(extmods[i].name);

		/* Print the rest of description */
		desc_size = MAX_STRLEN - desc_offset;
		while (desc && *desc) {
			desc = get_subline(desc, buf, desc_size, BUF_SIZE);
			for (; offset < desc_offset; offset++)
				printf(" ");
			printf("%s\n", buf);
			offset = 0;
		}
	}
}
