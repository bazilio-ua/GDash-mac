/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <phk@FreeBSD.org> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.   Poul-Henning Kamp
 * ----------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void
usage(void)
{

	fprintf(stderr, "usage: file2c [-n count] [-x] filename [prefix [suffix]]\n");
	exit(1);
}

int
main(int argc, char *argv[])
{
	int c, count, linepos, maxcount, radix;
	FILE *fp;

	maxcount = 0;
	radix = 10;
	while ((c = getopt(argc, argv, "n:x")) != -1) {
		switch (c) {
		case 'n':	/* Max. number of bytes per line. */
			maxcount = strtol(optarg, NULL, 10);
			break;
		case 'x':	/* Print hexadecimal numbers. */
			radix = 16;
			break;
		case '?':
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (argc == 0)
	    abort ();
	fp = fopen(argv[0], "rb");
	if (!fp)
	    abort ();
	
	if (argc > 1)
		printf("%s\n", argv[1]);
	count = linepos = 0;
	while((c = fgetc(fp)) != EOF) {
		if (count) {
			putchar(',');
			linepos++;
		}
		if ((maxcount == 0 && linepos > 70) ||
		    (maxcount > 0 && count >= maxcount)) {
			putchar('\n');
			count = linepos = 0;
		}
		switch (radix) {
		case 10:
			linepos += printf("%d", c);
			break;
		case 16:
			linepos += printf("0x%02x", c);
			break;
		default:
			abort();
		}
		count++;
	}
	fclose (fp);
	putchar('\n');
	if (argc > 2)
		printf("%s\n", argv[2]);
	return (0);
}
