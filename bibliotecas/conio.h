/* Implementación de conio segun especificaciones de Borland
 * para Mingw/Dev-C++.
 *
 * Por:
 * Salvador Pozo Coronado <salvador@conclase.net>
 * C++ con Clase: http://c.conclase.net
 * Versión 1.0 Abril de 2003.
 * Versión 1.1 Agosto de 2003 (fru <elfrucool@yahoo.com.mx>)
 * Se adapta el código a ANSI C (la versión anterior contiene
 * muchos errores debido al uso de características C++).
 * Versión 1.2 Abril de 2004.
 * Se corrige bug en función void _setcursortype(int cur_t);
 * que no funcionaba correctemente con la opción _NOCURSOR
 * Versión 1.3 Agosto de 2004
 * Se usa el nombre libconio.a para facilitar el enlace estático.
 *
 * Para dominio público sin ninguna garantía.
 */

#ifndef _CONIO_H_
#define _CONIO_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BLINK 0

typedef
struct text_info {
   unsigned char winleft;        /* left window coordinate */
   unsigned char wintop;         /* top window coordinate */
   unsigned char winright;       /* right window coordinate */
   unsigned char winbottom;      /* bottom window coordinate */
   unsigned char attribute;      /* text attribute */
   unsigned char normattr;       /* normal attribute */
   unsigned char currmode;       /* BW40, BW80, C40, C80, or C4350 */
   unsigned char screenheight;   /* text screen's height */
   unsigned char screenwidth;    /* text screen's width */
   unsigned char curx;           /* x-coordinate in current window */
   unsigned char cury;           /* y-coordinate in current window */
} text_info;

typedef enum {
   BLACK,
   BLUE,
   GREEN,
   CYAN,
   RED,
   MAGENTA,
   BROWN,
   LIGHTGRAY,
   DARKGRAY,
   LIGHTBLUE,
   LIGHTGREEN,
   LIGHTCYAN,
   LIGHTRED,
   LIGHTMAGENTA,
   YELLOW,
   WHITE
} COLORS;

enum text_modes {  
   LASTMODE=-1,
   BW40=0,
   C40,
   BW80,
   C80,
   MONO=7,
   C4350=64 
};

#define _NOCURSOR      0
#define _SOLIDCURSOR   1
#define _NORMALCURSOR  2

#define cscanf	scanf

/* Funciones de conio según Borland: */
char *cgets(char *str);
void clreol(void);
void clrscr(void);
int cprintf(const char *format, ...);
int cputs(const char *str);
//int cscanf(char *format, ...);
void delline(void);
int getch(void);
int getche(void);
char *getpass(const char *prompt);
int _gettext(int left, int top, int right, int bottom, void *destin);
void gettextinfo(struct text_info *r);
void gotoxy(int, int);
void highvideo(void);
//inp
//inport
//inportb
//inpw
void insline(void);
int kbhit(void);
void lowvideo(void);
int movetext(int left, int top, int right, int bottom, int destleft, int desttop);
void normvideo(void);
//outp
//outport
//outportb
//outpw
int putch(int c);
int puttext(int left, int top, int right, int bottom, void *source);
void _setcursortype(int cur_t);
void textattr(int newattr);
void textbackground(int newcolor);
void textcolor(int newcolor);
void textmode(int newmode);
int ungetch(int ch);
int wherex(void);
int wherey(void);
void window(int left, int top, int right, int bottom);

#ifdef __cplusplus
}
#endif

#endif /* _CONIO_H_ */
