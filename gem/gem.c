/*
 * adapted from sample code found in:
 * https://github.com/shanecoughlan/OpenGEM/
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <dos.h>
#include <io.h>
#include <conio.h>
#include <i86.h>

#include "gem.h"

/* GEM array sizes */
#define C_SIZE 5
#define G_SIZE 15
#define I_SIZE 16
#define O_SIZE 7
#define AI_SIZE 2
#define AO_SIZE 5
#define CTRL_CNT 4

BYTE ctrl_cnts[] = {
/* Application Manager		*/
	0, 1, 0, 			/* func 010		*/
	2, 1, 1, 			/* func 011		*/
	2, 1, 1, 			/* func 012		*/
	0, 1, 1, 			/* func 013		*/
	2, 1, 1, 			/* func 014		*/
	1, 1, 1, 			/* func 015		*/
	2, 1, 0, 			/* func 016		*/
	0, 0, 0, 			/* func 017		*/
	0, 0, 0, 			/* func 008		*/
	0, 1, 0, 			/* func 019		*/
/* Event Manager		*/
	0, 1, 0, 			/* func 020		*/
	3, 5, 0, 			/* func 021		*/
	5, 5, 0, 			/* func 022		*/
	0, 1, 1, 			/* func 023		*/
	2, 1, 0, 			/* func 024		*/
	16, 7, 1,	 		/* func 025		*/
	2, 1, 0, 			/* func 026		*/
	0, 0, 0, 			/* func 027		*/
	0, 0, 0, 			/* func 028		*/
	0, 0, 0, 			/* func 009		*/
/* Menu Manager			*/
	1, 1, 1, 			/* func 030		*/
	2, 1, 1, 			/* func 031		*/
	2, 1, 1, 			/* func 032		*/
	2, 1, 1, 			/* func 033		*/
	1, 1, 2, 			/* func 034		*/
	1, 1, 1, 			/* func 005		*/
	1, 1, 0, 			/* func 006		*/
	2, 1, 0, 			/* func 007		*/
	0, 0, 0, 			/* func 008		*/
	0, 0, 0, 			/* func 009		*/
/* Object Manager		*/
	2, 1, 1, 			/* func 040		*/
	1, 1, 1, 			/* func 041		*/
	6, 1, 1, 			/* func 042		*/
	4, 1, 1, 			/* func 043		*/
	1, 3, 1, 			/* func 044		*/
	2, 1, 1, 			/* func 045		*/
	4, 2, 1, 			/* func 046		*/
	8, 1, 1, 			/* func 047		*/
	0, 0, 0, 			/* func 048		*/
	0, 0, 0, 			/* func 049		*/
/* Form Manager			*/
	1, 1, 1, 			/* func 050		*/
	9, 1, 0, 			/* func 051 	*/
	1, 1, 1, 			/* func 002		*/
	1, 1, 0, 			/* func 003		*/
	0, 5, 1, 			/* func 004		*/
	3, 3, 1, 			/* func 005		*/
	2, 2, 1, 			/* func 006		*/
	0, 0, 0, 			/* func 007		*/
	0, 0, 0, 			/* func 008		*/
	0, 0, 0, 			/* func 009		*/
/* Process Manager		*/
	0, 0, 0, 			/* func 060		*/
	0, 0, 0, 			/* func 061		*/
	0, 0, 0, 			/* func 062		*/
	0, 0, 0, 			/* func 063		*/
	0, 0, 0, 			/* func 064		*/
	0, 0, 0, 			/* func 065		*/
	0, 0, 0, 			/* func 066		*/
	0, 0, 0, 			/* func 067		*/
	0, 0, 0, 			/* func 008		*/
	0, 0, 0, 			/* func 009		*/
/* Graphics Manager	*/
	4, 3, 0, 			/* func 070		*/
	8, 3, 0, 			/* func 071		*/
	6, 1, 0, 			/* func 072		*/
	8, 1, 0, 			/* func 073		*/
	8, 1, 0, 			/* func 074		*/
	4, 1, 1, 			/* func 075		*/
	3, 1, 1, 			/* func 076		*/
	0, 5, 0, 			/* func 077		*/
	1, 1, 1, 			/* func 078		*/
	0, 5, 0, 			/* func 009		*/
/* Scrap Manager		*/
	0, 1, 1, 			/* func 080		*/
	0, 1, 1, 			/* func 081		*/
	0, 1, 0, 			/* func 082		*/
	0, 0, 0, 			/* func 083		*/
	0, 0, 0, 			/* func 084		*/
	0, 0, 0, 			/* func 005		*/
	0, 0, 0, 			/* func 006		*/
	0, 0, 0, 			/* func 007		*/
	0, 0, 0, 			/* func 008		*/
	0, 0, 0, 			/* func 009		*/
/* fseler Manager		*/
	0, 2, 2, 			/* func 090		*/
	0, 0, 0, 			/* func 091		*/
	0, 0, 0, 			/* func 092		*/
	0, 0, 0, 			/* func 003		*/
	0, 0, 0, 			/* func 004		*/
	0, 0, 0, 			/* func 005		*/
	0, 0, 0, 			/* func 006		*/
	0, 0, 0, 			/* func 007		*/
	0, 0, 0, 			/* func 008		*/
	0, 0, 0, 			/* func 009		*/
/* Window Manager		*/
	5, 1, 0, 			/* func 100		*/
	5, 1, 0, 			/* func 101		*/
	1, 1, 0, 			/* func 102		*/
	1, 1, 0, 			/* func 103		*/
	2, 5, 0, 			/* func 104		*/
	6, 1, 0, 			/* func 105		*/
	2, 1, 0, 			/* func 106		*/
	1, 1, 0, 			/* func 107		*/
	6, 5, 0, 			/* func 108		*/
	0, 0, 0, 			/* func 009		*/
/* Resource Manager		*/
	0, 1, 1, 			/* func 110		*/
	0, 1, 0, 			/* func 111		*/
	2, 1, 0, 			/* func 112		*/
	2, 1, 1, 			/* func 113		*/
	1, 1, 1, 			/* func 114		*/
	0, 0, 0, 			/* func 115		*/
	0, 0, 0, 			/* func 006		*/
	0, 0, 0, 			/* func 007		*/
	0, 0, 0, 			/* func 008		*/
	0, 0, 0, 			/* func 009		*/
/* Shell Manager		*/
	0, 1, 2, 			/* func 120		*/
	3, 1, 2, 			/* func 121		*/
	1, 1, 1, 			/* func 122		*/
	1, 1, 1, 			/* func 123		*/
	0, 1, 1, 			/* func 124		*/
	0, 1, 2, 			/* func 125		*/
	0, 1, 2, 			/* func 126		*/
	0, 1, 2, 			/* func 127		*/
	0, 0, 0, 			/* func 008		*/
	0, 0, 0, 			/* func 009		*/
/* Extended Graphics Manager	*/
	6, 6, 0,			/* func 130		*/
	9, 1, 0,			/* func 131		*/
	0, 0, 0,			/* func 132		*/
	0, 0, 0,			/* func 133		*/
	0, 0, 0,			/* func 134		*/
	0, 0, 0,			/* func 135		*/
	0, 0, 0,			/* func 136		*/
	0, 0, 0,			/* func 137		*/
	0, 0, 0,			/* func 138		*/
	0, 0, 0 			/* func 139		*/
};

/* GEM AES block */
typedef struct GEMBLK {
	void FAR *gb_pcontrol;
	void FAR *gb_pglobal;
	void FAR *gb_pintin;
	void FAR *gb_pintout;
	void FAR *gb_padrin;
	void FAR *gb_padrout;
} GEMBLK;

/* static GEM arrays and structures */
UWORD control[C_SIZE];
UWORD global[G_SIZE];
UWORD int_in[I_SIZE];
UWORD int_out[O_SIZE];
void FAR *addr_in[AI_SIZE];
void FAR *addr_out[AO_SIZE];

GEMBLK gb = {
	&control,
	&global,
	&int_in,
	&int_out,
	&addr_in,
	&addr_out
};

WORD gem(WORD opcode)
{
	union REGS r;
	struct SREGS s;
	WORD i;

	control[0] = opcode;

	for (i = 0; i < CTRL_CNT; i++)
		control[i + 1] = ctrl_cnts[((opcode - 10) * 3) + i];

	segread(&s);

	r.w.cx = 0x00C8;
	s.es = FP_SEG(&gb);
	r.w.bx = FP_OFF(&gb);

	int86x(0xEF, &r, &r, &s);

	return (WORD)RET_CODE;
}

WORD appl_init(void)
{
	return gem(APPL_INIT);
}

WORD appl_exit(void)
{
	return gem(APPL_EXIT);
}

WORD form_alert(WORD defbut, void FAR *astring)
{
	FM_DEFBUT = defbut;
	FM_ASTRING = astring;
	return gem(FORM_ALERT);
}
