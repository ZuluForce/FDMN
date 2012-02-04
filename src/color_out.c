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

int print_color_file(const char *str, const termOpts options[], bool newline, FILE *file) {
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

	fprintf(file, "%s%sm%s%s0m", ANSI_ESC, format_str, str, ANSI_ESC);
	if ( newline )
		fprintf(file, "\n");

	return 0;
}

char* makeColorString(const char *str, char *output, termOpts options[]) {
	char format_str[MAX_FORMAT_SIZE];

	int i = 0;
	int format_len = 0, temp_len = 0;

	//Create the list of options
	while ( options[i] != EOO) {
		temp_len = format_len + strlen(color_strings[options[i]]);

		if (temp_len > MAX_FORMAT_SIZE ) {
			printf("Option list too larg: print_color\n");
			return NULL;
		}

		strcpy(format_str + format_len, color_strings[options[i]]);
		format_str[temp_len] = ';'; //Separates the modifiers
		format_len = temp_len + 1;
		++i;
	}
	//Get rid of the extra ;
	format_str[format_len - 1] = '\0';

	sprintf(output, "%s%sm%s%s0m", ANSI_ESC, format_str, str, ANSI_ESC);

	return output;
}


ssize_t find_end_length(const char *str, termOpts options[]) {
	int i = 0;
	int temp_len = 0, format_len = 0;

	while ( options[i] != EOO ) {
		temp_len = format_len + strlen(color_strings[options[i]]);

		if ( temp_len > MAX_FORMAT_SIZE ) {
			return -1; //Won't be able to format
		}

		format_len = temp_len + 1;
		++i;
	}

	int total_size = format_len;
	total_size += 2 * strlen(ANSI_ESC);
	total_size += strlen(str);

	return total_size;
}

void strip_color(char *str) {

	return;
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
