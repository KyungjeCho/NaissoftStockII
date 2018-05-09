#define DEFAULT_COLOR 7 

typedef enum {
	NOCURSOR,
	SOLIDCURSOR,
	NORMALCURSOR
} CURSOR_TYPE;

void gotoxy(int, int);

void textcolor(int);

void setcursortype(CURSOR_TYPE);

void type_effect(char *, int);

void clearbuffer();

void titleLine(const char *);