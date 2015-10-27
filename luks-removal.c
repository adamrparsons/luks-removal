/**
* Luks Removal Tool
* Will search through your given device for the LUKS descriptor, and if found, shits all over it
* Like his reasoning for formatting someone elses USB, this program is fairly broken
* For fucks sake, don't actually run this...
* 
* Inspired by Tim McDonald, Written by Adam Parsons, 2015
*/

# include "luks-removal.h"

int main (int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Hey, I need a disk to fix, pass me a /dev/disk path to  your vital USB drive\n");
	}
	else if (argc > 2)
	{
		printf("Woah partner! I can only 'fix' one drive at a time!, please pass me a single disk path\n");
	}
	else 
	{
		fuckItUp(argv);
	}
	return 0; /* Always */
}

void fuckItUp(char** argv)
{
	FILE *blk_p = fopen(*(argv + 1), "r");
	int i, foo;
	char* searchterm = (char*)"LUKS"; /* Works only with 4 chars :^) */
	char ch = 1;
	/* Your luks header sits around the top of the drive, so who even needs that much buffer, right?*/
	char* buffer = malloc(1000 * 1000 * 1000 * sizeof(char)); /* THIS IS SO FUCKING EFFICIENT IM GOING SO FAST FUCKKKKKKKKK */
	for (i = 0; i < (1000 * 1000 * 1000); i++)
	{
		while (ch != EOF)
		{
			/* Arguably the fastest method to work on block storage devices */
			ch = fgetc(blk_p);
			if (ch != EOF)
				*(buffer + i) = (char)ch;
			printf("%c\n", (char)ch);
		}
	}
	fclose(blk_p);
	i = searchForTerm(buffer, searchterm);
	if (i != 0)
	{
		foo = i;
		printf("SICK BRO, I FOUND IT!\n");
		for (i = i; i < foo+4096; i++)
		{
			blastItWithPiss(buffer, i);
		}
	}
	else 
	{
		printf("FUck FAm, i cant see it, guess ill just fuck up ya whole flash drive instead, and hope for the best\n");
		for (i = 0; i < (1000 * 1000 * 1000); i++)
		{
			blastItWithPiss(buffer, i);
		}
	}

	writeSickBufferToDisk(buffer, argv);

	free (buffer);
}

int searchForTerm(char* buffer, char* term)
{
	int i;
	int result = 0;
	for (i = 0; i < (1000 * 1000 * 1000); i++)
	{
		/* SICK STRING SEARCH */
		if ( *(buffer + i) == *term) {
			if (*(buffer + i + 1) == *(term+1)) {
				if (*(buffer + i + 2) == *(term+2)) {
					if (*(buffer + i + 3) == *(term+3)) { 
						result = i;
					}
				}
			}
		}
	}
	return result;
}

void blastItWithPiss (char* buffer, int i)
{
	char* pissPhrase = (char*)"TimMcDonald";
	int len = strlen(pissPhrase);
	char pissFragment = *(pissPhrase + (i % len));
	*(buffer + i) = pissFragment;
	/* For those too lazy to figure it out, the above will mean that the pissPhrase
	will be written as many times as possible, ie TimMcDonaldTimMcDonaldTimMcDonald*/
}

void writeSickBufferToDisk (char* buffer, char **argv)
{
	int i;
	FILE *out_p = fopen(*(argv+1), "w");
	for (i=0; i< (1000 * 1000 * 1000); i++)
	{
		/* Another fully sick way to write really faste */
		fprintf(out_p, "%c", *(buffer+i));
	}
	fclose(out_p);
}
