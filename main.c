#include <unistd.h>
#include <stdio.h>

typedef enum {false, true} boolean;

#define READ_COUNT 16

/* From FMPMD2000 source code (Copyright C60, Twitter @c60fmp) */
/* 0x85XX */
const char * ZEN2_CONV_TABLE_85[] = {
	/* 0x40 - 0x4F */
	"\x81\x49", "\x81\x68", "\x81\x94", "\x81\x90", "\x81\x93", "\x81\x95", "\x81\x66", "\x81\x69",
	"\x81\x6A", "\x81\x96", "\x81\x7B", "\x81\x43", "\x81\x7C", "\x81\x44", "\x81\x5E", "\x82\x4F",
	/* 0x50 - 0x5F */
	"\x82\x50", "\x82\x51", "\x82\x52", "\x82\x53", "\x82\x54", "\x82\x55", "\x82\x56", "\x82\x57",
	"\x81\x58", "\x81\x46", "\x81\x47", "\x81\x83", "\x81\x81", "\x81\x84", "\x81\x48", "\x81\x97",
	/* 0x60 - 0x6F */
	"\x82\x60", "\x82\x61", "\x82\x62", "\x82\x63", "\x82\x64", "\x82\x65", "\x82\x66", "\x82\x67",
	"\x82\x68", "\x82\x68", "\x82\x6A", "\x82\x6B", "\x82\x6C", "\x82\x6D", "\x82\x6E", "\x82\x6F",
	/* 0x70 - 0x7F */
	"\x82\x70", "\x82\x71", "\x82\x72", "\x82\x73", "\x82\x74", "\x82\x75", "\x82\x76", "\x82\x77",
	"\x82\x78", "\x82\x79", "\x81\x6D", "\x81\x8F", "\x81\x6E", "\x81\x4F", "\x81\x51", "\x81\x4D",
	/* 0x80 - 0x8F */
	"\x81\x4D", "\x82\x81", "\x82\x82", "\x82\x83", "\x82\x84", "\x82\x85", "\x82\x86", "\x82\x87",
	"\x82\x88", "\x82\x89", "\x82\x8A", "\x82\x8B", "\x82\x8C", "\x82\x8D", "\x82\x8E", "\x82\x8F",
	/* 0x90 - 0x9F */
	"\x82\x90", "\x82\x91", "\x82\x92", "\x82\x93", "\x82\x94", "\x82\x95", "\x82\x96", "\x82\x97",
	"\x82\x98", "\x82\x99", "\x82\x9A", "\x81\x6F", "\x81\x62", "\x81\x70", "\x81\x50", "\x81\x42",
	/* 0xA0 - 0xAF */
	"\x81\x75", "\x81\x76", "\x81\x41", "\x81\x45", "\x83\x92", "\x83\x40", "\x83\x42", "\x83\x44",
	"\x83\x46", "\x83\x48", "\x83\x83", "\x83\x85", "\x83\x87", "\x83\x62", "\x81\x5B", "\x83\x41",
	/* 0xB0 - 0xBF */
	"\x83\x43", "\x83\x45", "\x83\x47", "\x83\x49", "\x83\x4A", "\x83\x4C", "\x83\x4E", "\x83\x50",
	"\x83\x52", "\x83\x54", "\x83\x56", "\x83\x58", "\x83\x5A", "\x83\x5C", "\x83\x5E", "\x83\x60",
	/* 0xC0 - 0xCF */
	"\x83\x63", "\x83\x65", "\x83\x67", "\x83\x69", "\x83\x6A", "\x83\x6B", "\x83\x6C", "\x83\x6D",
	"\x83\x6E", "\x83\x71", "\x83\x74", "\x83\x77", "\x83\x7A", "\x83\x7D", "\x83\x7E", "\x83\x80",
	/* 0xD0 - 0xDF */
	"\x83\x81", "\x83\x82", "\x83\x84", "\x83\x86", "\x83\x88", "\x83\x89", "\x83\x8A", "\x83\x8B",
	"\x83\x8C", "\x83\x8D", "\x83\x8F", "\x83\x93", "\x81\x4A", "\x81\x8B", "\x83\x90", "\x83\x91",
	/* 0xE0 - 0xEF */
	"\x83\x8E", "\x83\x95", "\x83\x96", "\x83\x94", "\x83\x4B", "\x83\x4D", "\x83\x4F", "\x83\x51",
	"\x83\x53", "\x83\x55", "\x83\x57", "\x83\x59", "\x83\x5B", "\x83\x5D", "\x83\x5F", "\x83\x61",
	/* 0xF0 - 0xFC */
	"\x83\x64", "\x83\x66", "\x83\x68", "\x83\x6F", "\x83\x70", "\x83\x72", "\x83\x73", "\x83\x75",
	"\x83\x76", "\x83\x78", "\x83\x79", "\x83\x7B", "\x83\x7C"
};

/* 0x86XX */
const char * ZEN2_CONV_TABLE_86[] = {
	/* 0x40 - 0x4F */
	"\x81\x40", "\x81\x68", "\x81\x68", "\x86\xA2", "\x86\xA3", "\x86\xA4", "\x86\xA5", "\x86\xA6",
	"\x86\xA7", "\x86\xA8", "\x86\xA9", "\x86\xAA", "\x86\xAB", "\x86\xAC", "\x86\xAD", "\x86\xAE",
	/* 0x50 - 0x5F */
	"\x86\xAF", "\x86\xB0", "\x86\xB1", "\x86\xB2", "\x86\xB3", "\x86\xB4", "\x86\xB5", "\x86\xB6",
	"\x86\xB7", "\x86\xB8", "\x86\xB9", "\x86\xBA", "\x86\xBB", "\x86\xBC", "\x86\xBD", "\x86\xBE",
	/* 0x60 - 0x6F */
	"\x86\xBF", "\x86\xC0", "\x86\xC1", "\x86\xC2", "\x86\xC3", "\x86\xC4", "\x86\xC5", "\x86\xC6",
	"\x86\xC7", "\x86\xC8", "\x86\xC9", "\x86\xCA", "\x86\xCB", "\x86\xCC", "\x86\xCD", "\x86\xCE",
	/* 0x70 - 0x7F */
	"\x86\xCF", "\x86\xD0", "\x86\xD1", "\x86\xD2", "\x86\xD3", "\x86\xD4", "\x86\xD5", "\x86\xD6",
	"\x86\xD7", "\x86\xD8", "\x86\xD9", "\x86\xDA", "\x86\xDB", "\x86\xDC", "\x86\xDD", "\x81\x40",
	/* 0x80 - 0x8F */
	"\x86\xDE", "\x86\xDF", "\x86\xE0", "\x86\xE1", "\x86\xE2", "\x86\xE3", "\x86\xE4", "\x86\xE5",
	"\x86\xE6", "\x86\xE7", "\x86\xE8", "\x86\xE9", "\x86\xEA", "\x86\xEB", "\x86\xEC", "\x81\xED",
	/* 0x90 - 0x9F */
	"\x91\x4C", "\x81\x4E", "\x81\x65", "\x81\x67", "\x81\x6B", "\x81\x6C", "\x81\x71", "\x81\x72",
	"\x81\x73", "\x81\x74", "\x81\x77", "\x81\x78", "\x81\x79", "\x81\x7A", "\x81\x7C"
};

unsigned char holdback = 0x00;

void convertZen2 (const unsigned char buffer[READ_COUNT], int readAmount) {
	int i;
	for (i = 0; i < readAmount; ++i) {
		if (holdback == 0x00) {
			if (buffer[i] == 0x85 || buffer[i] == 0x86) {
				holdback = buffer[i];
			} else {
				printf ("%c", buffer[i]);
			}
		} else {
			if (holdback == 0x85 && (buffer[i] >= 0x40 && buffer[i] <= 0xFC)) {
				printf ("%s", ZEN2_CONV_TABLE_85[buffer[i] - 0x40]);
			} else if (holdback == 0x86 && (buffer[i] >= 0x40 && buffer[i] <= 0x9F)) {
				printf ("%s", ZEN2_CONV_TABLE_86[buffer[i] - 0x40]);
			} else {
				printf ("%c%c", holdback, buffer[i]);
			}
			holdback = 0x00;
		}
	}
}

int main() {
	unsigned char buffer[READ_COUNT];
	int readAmount;

	while (true) {
		readAmount = read (STDIN_FILENO, &buffer, READ_COUNT);
		if (readAmount != 0) {
			convertZen2 (buffer, readAmount);
		} else {
			break;
		}
	}

	if (holdback != 0x00) {
		printf ("%c", holdback);
	}

	return 0;
}
