#ifndef COLOR_OUT_H_INCLUDED
#define COLOR_OUT_H_INCLUDED

#define MAX_FORMAT_SIZE 20

#ifndef _cplusplus
//typedef enum {false, true} bool;
#endif

typedef enum enum_termOpts {
	/* Text Colors */
	cBlack,
	cRed,
	cGreen,
	cYellow,
	cBlue,
	cMag,
	cCyan,
	cWhite,

	/* Background Colors */
	bcBlack,
	bcRed,
	bcGreen,
	bcYellow,
	bcBlue,
	bcMag,
	bcCyan,
	bcWhite,

	/* Effects */
	eBold,
	eWeak,
	eItalic,
	eULine,
	eBlink,
	eNeg,
	eStrike,

	/* End Of Options */
	EOO
} termOpts;

/* Pre-Defined Sytles */
const termOpts redError[] = { cRed, EOO};
const termOpts redErrorStrong[] = { cRed, eBold, eULine, EOO};

static const char* ANSI_ESC = "\033[";

static const char* color_strings[] =
{
	/* Text Color Values */
	"30","31","32","33",
	"34","35","36","37",

	/* Background Color Values */
	"40","41","42","43",
	"44","45","46","47",

	/* Effect Values */
	"1","2","3","4","5",
	"7","9"
};


int print_color(const char *str, const termOpts options[], bool newline);
int print_color_file(const char *str, const termOpts options[], bool newline, FILE *file);
char* makeColorString(const char *str, char *output, termOpts options[]);
ssize_t find_end_length(const char *str, termOpts options[]);

#endif // COLOR_OUT_H_INCLUDED
