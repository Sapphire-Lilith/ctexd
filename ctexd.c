#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define DIRNAME_LEN    50
#define SUBDIRNAME_LEN 10
#define FNAME_LEN      20

/* format: "./${DIRNAME}/${SUBDIRNAME}/" */
#define DIRPATH_LEN (DIRNAME_LEN + SUBDIRNAME_LEN + 4)

/* format: "./${DIRNAME}/${SUBDIRNAME}/${FNAME}.tex" */
#define FPATH_LEN (DIRNAME_LEN + SUBDIRNAME_LEN + FNAME_LEN + 8)

typedef enum {
	CTEXD_DEFAULT,
	CTEXD_NEW,
	CTEXD_REPORT,
} ctexd_mode_t;

void exit_errno() {
	fprintf(stderr, "[Error]: %s.\n", strerror(errno));
	errno = 0;

	exit(1);
}

void ctexd(ctexd_mode_t mode, char *dirname) {
	char *dirpath, *fpath;
	FILE *fp = NULL;

	if ((dirpath = malloc(DIRPATH_LEN)) == NULL) { exit_errno(); }
	if ((fpath = malloc(FPATH_LEN)) == NULL) { exit_errno(); }

	errno = 0;

	/* common process */

	/* mkdir ./${DIRNAME} */
	memset(dirpath, 0x0, DIRPATH_LEN);
	snprintf(dirpath, DIRPATH_LEN, "./%s/", dirname);
	mkdir(dirpath, 0755);
	if (errno) { exit_errno(); }

	/* mkdir ./${DIRNAME}/src/ */
	memset(dirpath, 0x0, DIRPATH_LEN);
	snprintf(dirpath, DIRPATH_LEN, "./%s/src/", dirname);
	mkdir(dirpath, 0755);
	if (errno) { exit_errno(); }

	/* touch ./${DIRNAME}/main.tex */
	memset(fpath, 0x0, FPATH_LEN);
	snprintf(fpath, FPATH_LEN, "./%s/main.tex", dirname);
	if ((fp = fopen(fpath, "w")) == NULL) { exit_errno(); }
	fclose(fp);

	switch (mode) {
	case CTEXD_REPORT:
			/* mkdir ./${DIRNAME}/data/ */
		memset(dirpath, 0x0, DIRPATH_LEN);
		snprintf(dirpath, DIRPATH_LEN, "./%s/data/", dirname);
		mkdir(dirpath, 0755);
		if (errno) { exit_errno(); }

		/* mkdir ./${DIRNAME}/fig/ */
		memset(dirpath, 0x0, DIRPATH_LEN);
		snprintf(dirpath, DIRPATH_LEN, "./%s/fig/", dirname);
		mkdir(dirpath, 0755);
		if (errno) { exit_errno(); }

		/* mkdir ./${DIRNAME}/script/ */
		memset(dirpath, 0x0, DIRPATH_LEN);
		snprintf(dirpath, DIRPATH_LEN, "./%s/script/", dirname);
		mkdir(dirpath, 0755);
		if (errno) { exit_errno(); }

		/* touch ./${DIRNAME}/src/01_purpose.tex */
		memset(fpath, 0x0, FPATH_LEN);
		snprintf(fpath, FPATH_LEN, "./%s/src/01_purpose.tex", dirname);
		if ((fp = fopen(fpath, "w")) == NULL) { exit_errno(); }
		fclose(fp);

		/* touch ./${DIRNAME}/src/02_content.tex */
		memset(fpath, 0x0, FPATH_LEN);
		snprintf(fpath, FPATH_LEN, "./%s/src/02_content.tex", dirname);
		if ((fp = fopen(fpath, "w")) == NULL) { exit_errno(); }
		fclose(fp);

		/* touch ./${DIRNAME}/src/03_result.tex */
		memset(fpath, 0x0, FPATH_LEN);
		snprintf(fpath, FPATH_LEN, "./%s/src/03_result.tex", dirname);
		if ((fp = fopen(fpath, "w")) == NULL) { exit_errno(); }
		fclose(fp);

		/* touch ./${DIRNAME}/src/04_discussion.tex */
		memset(fpath, 0x0, FPATH_LEN);
		snprintf(fpath, FPATH_LEN, "./%s/src/04_discussion.tex", dirname);
		if ((fp = fopen(fpath, "w")) == NULL) { exit_errno(); }
		fclose(fp);

		/* touch ./${DIRNAME}/src/05_exercise.tex */
		memset(fpath, 0x0, FPATH_LEN);
		snprintf(fpath, FPATH_LEN, "./%s/src/05_exercise.tex", dirname);
		if ((fp = fopen(fpath, "w")) == NULL) { exit_errno(); }
		fclose(fp);

		/* touch ./${DIRNAME}/src/06_reference.tex */
		memset(fpath, 0x0, FPATH_LEN);
		snprintf(fpath, FPATH_LEN, "./%s/src/06_reference.tex", dirname);
		if ((fp = fopen(fpath, "w")) == NULL) { exit_errno(); }
		fclose(fp);

		break;
	default:
		break;
	}

	free(dirpath);
	free(fpath);
}

int main(int argc, char **argv) {
	static const char          opts[]     = "n:r:";
	static const struct option longopts[] = {
	    {   "new", required_argument, 0, 'n'},
	    {"report", required_argument, 0, 'r'},
	    {       0,	             0, 0,   0},
	};

	int optid = 0;
	int c;
	opterr = 0;

	ctexd_mode_t mode    = CTEXD_DEFAULT;
	char        *dirname = malloc(DIRNAME_LEN);

	int flag = 0;
	while ((c = getopt_long(argc, argv, opts, longopts, &optid)) != -1) {
		switch (c) {
		case 0:
			break;
		case 'n':
			flag = 1;
			mode = CTEXD_NEW;
			snprintf(dirname, DIRNAME_LEN, "%s", optarg);
			break;
		case 'r':
			flag = 1;
			mode = CTEXD_REPORT;
			snprintf(dirname, DIRNAME_LEN, "%s", optarg);
			break;
		case '?':
		default:
			fprintf(stderr, "[Error]: Option is invalid.\n");
			return 1;
			break;
		}

		if (flag) { break; }
	}

	if (mode == CTEXD_DEFAULT) { snprintf(dirname, DIRNAME_LEN, "texd"); }

	ctexd(mode, dirname);

	free(dirname);

	return 0;
}
