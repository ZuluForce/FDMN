#include <stdio.h>
#include <string.h>

#include "color_out.h"

int print_color(const char *str, const termOpts options[], bool newline) {
	char format_str[MAX_FORMAT_SIZE];

	int i = 0;
	int format_len = 0, temp_len = 0;

	//Create the list of options
	while ( options[i] != EOO) {
		temp_len = format_len + strlen(color_strings[options[i]]);

		if (temp_len > MAX_FORMAT_SIZE ) {
			printf("Option list too larg: print_color\n");
			return -1;
		}

		strcpy(format_str + format_len, color_strings[options[i]]);
		format_str[temp_len] = ';'; //Separates the modifiers
		format_len = temp_len + 1;
		++i;
	}
	//Get rid of the extra ;
	format_str[format_len - 1] = '\0';

	printf("%s%sm%s%s0m", ANSI_ESC, format_str, str, ANSI_ESC);
	if ( newline )
		printf("\n");

	return 0;
}

/*
int main( int argc, char** argv) {
	//termOpts options[] = {cBlack, eULine, eStrike, EOO};

	termOpts colors[][5] =
	{	{cRed, bcBlack, eBlink, EOO},
		{cYellow,bcBlack, eBlink, EOO},
		{cGreen,bcBlack, eBlink, EOO},
		{cBlue,bcBlack, eBlink, EOO},
		{cMag,bcBlack, eBlink, EOO}
	};

	print_color(argv[1], colors[0], true);
	print_color(argv[1], colors[1], true);
	print_color(argv[1], colors[2], true);
	print_color(argv[1], colors[3], true);
	print_color(argv[1], colors[4], true);
	return 0;
} */
