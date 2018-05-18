#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"


int main(int argc, char **argv)
{
	srand(clock());
	int keylen = 0;
	if (argc == 1)
		keylen = 64;
	else
	{
		keylen = atoi(argv[1]);
		if (keylen == 0)
		{
			printf("INPUT ERROR!\n");
			return 0;
		}
	}
	char keybuf[] =
		"\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6A"
		"\x6B\x6C\x6D\x6E\x6F\x70\x71\x72\x73\x74"
		"\x75\x76\x77\x78\x79\x7A\x41\x42\x43\x44"
		"\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E"
		"\x4F\x50\x51\x52\x53\x54\x55\x56\x57\x58"
		"\x59\x5A\x30\x31\x32\x33\x34\x35\x36\x37"
		"\x38\x39\x21\x40\x23\x25\x2A\x28\x29\x2E"
		;
	int rd1 = 0, rd2 = 0;
	int tempbuf = 0;

	for (int k2 = 0; k2 < keylen; k2++)
	{
		for (int k1 = 0; k1 < 70; k1++)
		{
			rd1 = rand() % 70;
			tempbuf = keybuf[rd1];
			keybuf[rd1] = keybuf[k1];
			keybuf[k1] = tempbuf;
		}
		rd2 = rand() % 70;
		printf("%c", keybuf[rd2]);
	}
	return 0;
}