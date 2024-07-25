/*
 * adapted from sample code found in:
 * https://github.com/shanecoughlan/OpenGEM/
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <dos.h>

#include "gem.h"

WORD appl_init(void);
WORD appl_exit(void);
WORD form_alert(WORD defbut, void FAR *astring);

const char alert[] = "[1][Hello World!][ Ok ]";

int main(int argc, char **argv)
{
	/* check for GEM */
	if (_dos_getvect(0xEF) == NULL)
	{
		printf("GEMAES is not present in memory.\n");
		return 1;
	}

	/* run GEM program */
	appl_init();
	form_alert(1, alert);
	appl_exit();

	return 0;
}
