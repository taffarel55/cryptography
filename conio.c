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
 * Versión 1.31 Agosto de 2005
 * Se corrige el error en la función kbhit para que sólo busque
 * eventos de teclas pulsadas, e ignore los de tecla soltada.
 * 
 * Para dominio público sin ninguna garantía.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <string.h>
#include <stdarg.h>
#include "conio.h"

#ifdef __cplusplus
extern "C" {
#endif

// Declaramos una estructura text_info para almacenar la información
// sobre la ventana actual.
text_info vActual = {0, 0, 79, 24, WHITE, WHITE, C80, 25, 80, 1, 1};

// Reads a string from the console.
// cgets reads a string of characters from the console, storing the string 
// (and the string length) in the location pointed to by str.
// cgets reads characters until it encounters a carriage-return/linefeed 
// (CR/LF) combination, or until the maximum allowable number of characters 
// have been read. If cgets reads a CR/LF combination, it replaces the 
// combination with a \0 (null terminator) before storing the string.
// Before cgets is called, set str[0] to the maximum length of the string to 
// be read. On return, str[1] is set to the number of characters actually 
// read. The characters read start at str[2] and end with a null terminator. 
// Thus, str must be at least str[0] plus 2 bytes long.
char *cgets(char *str)
{
   DWORD longitud = 0;
   DWORD leidos, modo;
   
   GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &modo);   
   SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), modo & !ENABLE_ECHO_INPUT);
   do {
      ReadConsole(GetStdHandle(STD_INPUT_HANDLE), &str[2+longitud], 1,
		  &leidos, NULL);
      if(str[2+longitud] != '\r') putch(str[2+longitud++]);
   } while(longitud < str[0] && str[2+longitud] != '\r');
   str[1] = longitud;
   str[2+longitud] = 0;
   SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), modo);   
   return &str[2];   
}

// Clears to end of line in text window.
// clreol clears all characters from the cursor position to the end of the 
// line within the current text window, without moving the cursor.
// Borrar hasta el final de la línea requiere borrar tanto los caracteres
// como los atributos.
void clreol ()
{
   COORD coord;
   DWORD escrito;

   coord.X = vActual.winleft+vActual.curx-1;
   coord.Y = vActual.wintop+vActual.cury-1;
   
   FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 
      vActual.screenwidth - vActual.curx + 1, coord, &escrito);
   FillConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
      vActual.attribute, vActual.screenwidth - vActual.curx + 1, 
      coord, &escrito);
   gotoxy(vActual.curx, vActual.cury);
}

// Clears the text-mode window.
// clrscr clears the current text window and places the cursor in the upper 
// left corner (at position 1,1). 
// La consola en algunos sistemas operativos no está limitada a 80*25
// caracteres, como en MSDOS, obtenemos el tamaño actual de la consola y la 
// borramos entera, usando los valores de atributos actuales.
void clrscr ()
{
   DWORD escrito;
   int i;

   for( i = 0; i < vActual.screenheight; i++) {
      FillConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
         vActual.attribute, vActual.screenwidth,
         (COORD) {vActual.winleft, vActual.wintop+i}, &escrito);
      FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ',
         vActual.screenwidth,
         (COORD) {vActual.winleft, vActual.wintop+i}, &escrito);
   }
   gotoxy(vActual.curx, vActual.cury);
}

// Writes formatted output to the screen.
// cprintf accepts a series of arguments, applies to each a format specifier 
// contained in the format string pointed to by format, and outputs the 
// formatted data directly to the current text window on the screen. There 
// must be the same number of format specifiers as arguments. 
// For details details on format specifiers, see printf Format Specifiers.
// The string is written either directly to screen memory or by way of a 
// BIOS call, depending on the value of the global variable _directvideo.
// Unlike fprintf and printf, cprintf does not translate linefeed characters 
// (\n) into carriage-return/linefeed character pairs (\r\n). Tab characters 
// (specified by \t) are not expanded into spaces.
int cprintf(const char *format, ...)
{
  // char *buffer;		// this is not "c" (this is c++).
  char buffer[1024] = { 0 };
  va_list p; 
  int n;

  // buffer = new char[1024];	// this is not "c" (this is c++).
  // buffer = (char *)malloc(1024);
  va_start(p, format); 
  n = vsprintf(buffer, format, p);
  cputs(buffer);
  // delete[] buffer;		// this is not "c" (this is c++).
  // free( buffer );  // usar si buffer = malloc
  return n;
}

// Writes a string to the screen.
// cputs writes the null-terminated string str to the current text 
// window. It does not append a newline character.
// The string is written either directly to screen memory or by way of a 
// BIOS call, depending on the value of the global variable _directvideo. 
// Unlike puts, cputs does not translate linefeed characters (\n) into 
// carriage-return/linefeed character pairs (\r\n).
int cputs(const char *str) // repasar
{
   DWORD escritos;
   int n = 0;
   int resto = vActual.screenwidth-vActual.curx+1;
   
   do {
      if(strlen(&str[n]) < resto) resto = strlen(&str[n]);
      gotoxy(vActual.curx, vActual.cury);
      WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), &str[n], resto, &escritos,
		   NULL);
      n+=resto;
      vActual.curx+=resto;
      if(vActual.curx > vActual.screenwidth) {
         vActual.curx -= vActual.screenwidth;
         resto = vActual.screenwidth-vActual.curx+1;
         vActual.cury++;
         resto = vActual.screenwidth;
         if(vActual.cury > vActual.screenheight) {
            vActual.cury--;
            movetext(1, 2, vActual.screenwidth, vActual.screenheight, 1, 1);
         }
      }
   } while(str[n]);
   return strlen(str);
}

// Scans and formats input from the console.
// cscanf scans a series of input fields one character at a time, reading 
// directly from the console. Then each field is formatted according to a 
// format specifier passed to cscanf in the format string pointed to by format.
// Finally, cscanf stores the formatted input at an address passed to it as 
// an argument following format, and echoes the input directly to the screen. 
// There must be the same number of format specifiers and addresses as there 
// are input fields. 
// Note:	For details on format specifiers, see scanf Format Specifiers.
// cscanf might stop scanning a particular field before it reaches the normal 
// end-of-field (whitespace) character, or it might terminate entirely for a 
// number of reasons. See scanf for a discussion of possible causes.
/*int cscanf(char *format, ...)
{
   char *buffer;
   va_list p; 
   int n;
   DWORD leidos;

   buffer = new char[260];
   buffer[0] = 255;
   cgets(buffer);
   va_start(p, format); 
   printf("#%s#%s#\n", &buffer[2], format);
   n = sscanf(&buffer[2], format, p);
   delete[] buffer;
   return n;
}*/

// Deletes line in text window.
// delline deletes the line containing the cursor and moves all lines below 
// it one line up. delline operates within the currently active text window.
void delline()
{
   COORD coord;
   SMALL_RECT origen;
   SMALL_RECT clip;
   CHAR_INFO ci;

   origen.Left = vActual.winleft;
   origen.Top = vActual.wintop+vActual.cury;
   origen.Right = vActual.winright;
   origen.Bottom = vActual.winbottom;
   coord.X = vActual.winleft;
   coord.Y = vActual.wintop+vActual.cury-1;
   clip.Left = vActual.winleft;
   clip.Top = vActual.wintop;
   clip.Right = vActual.winright;
   clip.Bottom = vActual.winbottom;
   ci.Char.AsciiChar = ' ';
   ci.Attributes = vActual.attribute;
   ScrollConsoleScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE),
      &origen, &clip, coord, &ci);
   vActual.curx = 1;
   gotoxy(vActual.curx, vActual.cury);
}

// Gets character from keyboard, does not echo to screen.
// getch reads a single character directly from the keyboard, without 
// echoing to the screen.
int getch(void)
{
   int car;
   DWORD leidos, modo;
   
   GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &modo);   
   SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), modo & !ENABLE_ECHO_INPUT & !ENABLE_PROCESSED_INPUT);
   ReadConsole(GetStdHandle(STD_INPUT_HANDLE), &car, 1, &leidos, NULL);
   SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), modo);   
   return car;   
}

// Gets character from the keyboard, echoes to screen.
// getche reads a single character from the keyboard and echoes it to the 
// current text window using direct video or BIOS.
int getche(void)
{
   int car;
   DWORD leidos, modo;
   
   GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &modo);   
   SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), modo & !ENABLE_ECHO_INPUT & !ENABLE_PROCESSED_INPUT);
   ReadConsole(GetStdHandle(STD_INPUT_HANDLE), &car, 1, &leidos, NULL);
   putch(car);
   SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), modo);   
   return car;   
}

// Reads a password.
// getpass reads a password from the system console after prompting with 
// the null-terminated string prompt and disabling the echo. A pointer is 
// returned to a null-terminated string of up to eight characters (not 
// counting the null-terminator).
char *getpass(const char *prompt)
{
   static char pass[9];
   DWORD longitud = 0;
   DWORD leidos, modo;

   cputs(prompt);
   GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &modo);   
   SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), modo & !ENABLE_ECHO_INPUT);
   do {
      ReadConsole(GetStdHandle(STD_INPUT_HANDLE), &pass[longitud], 1, &leidos,
		  NULL);
      if(pass[longitud] != '\r') longitud++;
   } while(longitud < 8 && pass[longitud] != '\r');
   pass[longitud] = 0;
   SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), modo);   
   return pass;      
}

// Copies text from text mode screen to memory.
// gettext stores the contents of an onscreen text rectangle defined by left, 
// top, right, and bottom into the area of memory pointed to by destin.
// All coordinates are absolute screen coordinates not window-relative. The 
// upper left corner is (1,1). gettext reads the contents of the rectangle 
// into memory sequentially from left to right and top to bottom.
// Each position onscreen takes 2 bytes of memory: The first byte is the 
// character in the cell and the second is the cell's video attribute. The 
// space required for a rectangle w columns wide by h rows high is defined as 
//    bytes = (h rows) x (w columns) x 2
int _gettext(int left, int top, int right, int bottom, void *destin)
{
   PCHAR_INFO buffer;
   char *pantalla = (char *)destin;
   int retval,i;
   
   COORD cSize = {1+right-left, 1+bottom-top};
   COORD cDest = {0,0};
   SMALL_RECT rect = {vActual.winleft+left-1, vActual.wintop+top-1, 
      vActual.winleft+right-1, vActual.wintop+bottom-1};
   // buffer = new CHAR_INFO[cSize.X * cSize.Y];
   buffer = (PCHAR_INFO)malloc(cSize.X*cSize.Y*sizeof(CHAR_INFO));
   
   retval = ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE),
      buffer, cSize, cDest, &rect);
   for( i = 0; i < cSize.X * cSize.Y; i++) {
      pantalla[2*i] = buffer[i].Char.AsciiChar;
      pantalla[2*i + 1] = buffer[i].Attributes & 0xff;
   }
   // delete[] buffer;
   free( buffer );
   return retval;
}

// Gets text mode video information.
// gettextinfo fills in the text_info structure pointed to by r with the 
// current text video information.
void gettextinfo(struct text_info *r)
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

   *r = vActual;
}

// Positions cursor in text window.
// gotoxy moves the cursor to the given position in the current text window. 
// If the coordinates are in any way invalid the call to gotoxy is ignored. 
// An example of this is a call to gotoxy(40,30) when (35,25) is the bottom 
// right position in the window. Neither argument to gotoxy can be zero.
void gotoxy(int x, int y)
{
   COORD c;

   if(x < 1 || x > vActual.screenwidth || 
      y < 1 || y > vActual.screenheight) return;
   vActual.curx = x;
   vActual.cury = y;
   c.X = vActual.winleft + x - 1;
   c.Y = vActual.wintop + y - 1;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// Selects high-intensity characters.
// highvideo selects high-intensity characters by setting the high-intensity 
// bit of the currently selected foreground color.
// This function does not affect any characters currently onscreen, but does 
// affect those displayed by functions (such as cprintf) that perform direct 
// video, text mode output after highvideo is called.
void highvideo(void)
{
   vActual.attribute |= FOREGROUND_INTENSITY;
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), vActual.attribute);
}

// Funciones no permitidas en Windows:
//inp
//inport
//inportb
//inpw

// Inserts a blank line in the text window.
// insline inserts an empty line in the text window at the cursor position 
// using the current text background color. All lines below the empty one move 
// down one line, and the bottom line scrolls off the bottom of the window.
void insline(void)
{
   COORD coord;
   SMALL_RECT origen;
   SMALL_RECT clip;
   CHAR_INFO ci;

   origen.Left = vActual.winleft;
   origen.Top = vActual.wintop+vActual.cury-1;
   origen.Right = vActual.winright;
   origen.Bottom = vActual.winbottom;
   coord.X = vActual.winleft;
   coord.Y = vActual.wintop+vActual.cury;
   clip.Left = vActual.winleft;
   clip.Top = vActual.wintop;
   clip.Right = vActual.winright;
   clip.Bottom = vActual.winbottom;
   ci.Char.AsciiChar = ' ';
   ci.Attributes = vActual.attribute;
   ScrollConsoleScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE),
      &origen, &clip, coord, &ci);
   vActual.curx = 1;
   gotoxy(vActual.curx, vActual.cury);
}

// Checks for currently available keystrokes.
// kbhit checks to see if a keystroke is currently available. Any available 
// keystrokes can be retrieved with getch or getche.
int kbhit(void)
{
   DWORD nEventos;
   INPUT_RECORD *eventos;
   DWORD leidos;
   int retval = 0;
   int i;
   
   GetNumberOfConsoleInputEvents(GetStdHandle(STD_INPUT_HANDLE),
      &nEventos);
   // eventos = new INPUT_RECORD[nEventos];
   eventos = (INPUT_RECORD *)malloc(nEventos*sizeof(INPUT_RECORD));
   PeekConsoleInput(GetStdHandle(STD_INPUT_HANDLE),
      eventos, nEventos, &leidos);
   for(i = 0;  i < nEventos; i++)
      if(eventos[i].EventType == KEY_EVENT && eventos[i].Event.KeyEvent.bKeyDown) retval = 1;
   // delete[] eventos;
   free( eventos );
   return retval;
}

// Selects low-intensity characters.
// lowvideo selects low-intensity characters by clearing the high-intensity 
// bit of the currently selected foreground color.
// This function does not affect any characters currently onscreen. It affects 
// only those characters displayed by functions that perform text mode, direct 
// console output after this function is called.
void lowvideo(void)
{
   vActual.attribute &= ~FOREGROUND_INTENSITY;
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), vActual.attribute);
}

// Copies text onscreen from one rectangle to another.
// movetext copies the contents of the onscreen rectangle defined by left, 
// top, right, and bottom to a new rectangle of the same dimensions. The new 
// rectangle's upper left corner is position (destleft, desttop).
// All coordinates are absolute screen coordinates. Rectangles that overlap 
// are moved correctly.
// movetext is a text mode function performing direct video output.
int movetext(int left, int top, int right, int bottom, int destleft,
	     int desttop)
{
   COORD coord;
   SMALL_RECT origen;
   CHAR_INFO ci;

   origen.Left   = vActual.winleft+left-1;
   origen.Top    = vActual.wintop+top-1;
   origen.Right  = vActual.winleft+right-1;
   origen.Bottom = vActual.wintop+bottom-1;
   coord.X       = vActual.winleft+destleft-1;
   coord.Y       = vActual.wintop+desttop-1;
   ci.Char.AsciiChar = ' ';
   ci.Attributes = vActual.attribute;
   ScrollConsoleScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE),
      &origen, NULL, coord, &ci);
   return 0;
}

// Selects normal-intensity characters.
// normvideo selects normal characters by returning the text attribute 
// (foreground and background) to the value it had when the program started.
// This function does not affect any characters currently on the screen, only 
// those displayed by functions (such as cprintf) performing direct console 
// output functions after normvideo is called.
void normvideo(void)
{
   vActual.attribute = vActual.normattr;
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), vActual.attribute);
}

// Funciones no permitidas en Windows:
//outp
//outport
//outportb
//outpw

// Outputs character to screen.
// putch outputs the character c to the current text window. It is a text mode 
// function performing direct video output to the console. putch does not 
// translate linefeed characters (\n) into carriage-return/linefeed pairs.
// The string is written either directly to screen memory or by way of a BIOS 
// call, depending on the value of the global variable _directvideo.
int putch(int c)
{
   DWORD escritos;
   
   gotoxy(vActual.curx, vActual.cury);
   WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), (char*)&c, 1, &escritos,
		NULL);
   vActual.curx++;
   if(vActual.curx > vActual.screenwidth) {
      vActual.curx -= vActual.screenwidth;
      vActual.cury++;
      if(vActual.cury > vActual.screenheight) {
         vActual.cury--;
         movetext(1, 2, vActual.screenwidth, vActual.screenheight, 1, 1);
      }
   }
   return 0;
}

// Copies text from memory to the text mode screen.
// puttext writes the contents of the memory area pointed to by source out to 
// the onscreen rectangle defined by left, top, right, and bottom.
// All coordinates are absolute screen coordinates, not window-relative. The 
// upper left corner is (1,1).
// puttext places the contents of a memory area into the defined rectangle 
// sequentially from left to right and top to bottom.
// Each position onscreen takes 2 bytes of memory: The first byte is the 
// character in the cell, and the second is the cell's video attribute. The 
// space required for a rectangle w columns wide by h rows high is defined as
//   bytes = (h rows) x (w columns) x 2
// puttext is a text mode function performing direct video output.
int puttext(int left, int top, int right, int bottom, void *source)
{
   PCHAR_INFO buffer;
   char *pantalla = (char *)source;
   int retval,i;
   
   COORD cSize = {1+right-left, 1+bottom-top};
   COORD cDest = {0,0};
   SMALL_RECT rect = {vActual.winleft+left-1, vActual.wintop+top-1, 
      vActual.winleft+right-1, vActual.wintop+bottom-1};
   // buffer = new CHAR_INFO[cSize.X * cSize.Y];
   buffer = (PCHAR_INFO)malloc(sizeof(CHAR_INFO)*cSize.X * cSize.Y);

   for( i = 0; i < cSize.X * cSize.Y; i++) {
      buffer[i].Char.AsciiChar = pantalla[2*i];
      buffer[i].Attributes = (WORD)pantalla[2*i + 1];
   }
   
   retval = WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE),
      buffer, cSize, cDest, &rect);
   // delete[] buffer;   
   free(buffer);
   return retval;
}

// Selects cursor appearance.
// Sets the cursor type to
//
// _NOCURSOR	Turns off the cursor
// _NORMALCURSOR	Normal underscore cursor
// _SOLIDCURSOR	Solid block cursor
void _setcursortype(int cur_t)
{
   CONSOLE_CURSOR_INFO cci;

   switch(cur_t) {
      case _NOCURSOR:
         cci.dwSize = 100;
         cci.bVisible = FALSE;
         break;
      case _SOLIDCURSOR:
         cci.dwSize = 100;
         cci.bVisible = TRUE;
         break;
      case _NORMALCURSOR:
         cci.dwSize = 10;
         cci.bVisible = TRUE;
         break;
   }
   SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

// Sets text attributes.
// textattr lets you set both the foreground and background colors in a 
// single call. (Normally, you set the attributes with textcolor and 
// textbackground.)
// This function does not affect any characters currently onscreen; it affects 
// only those characters displayed by functions (such as cprintf) performing 
// text mode, direct video output after this function is called.
// Windows no permite colores parpadeantes (BLINK), en su lugar es posible
// usar 16 colores para el fondo, en lugar de los 8 de DOS
void textattr(int newattr)
{
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), newattr);
   vActual.attribute = newattr;
}

// Selects new text background color.
// textbackground selects the background color. This function works for 
// functions that produce output in text mode directly to the screen. 
// newcolor selects the new background color. You can set newcolor to an 
// integer from 0 to 7, or to one of the symbolic constants defined in 
// conio.h. If you use symbolic constants, you must include conio.h.
// Once you have called textbackground, all subsequent functions using direct 
// video output (such as cprintf) will use newcolor. textbackground does not 
// affect any characters currently onscreen.
// En windows se permiten colores del 0 al 15 para el fondo.
void textbackground(int newcolor)
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
      (csbi.wAttributes & 0x0f) | (newcolor << 4));
   vActual.attribute = (csbi.wAttributes & 0x0f) | (newcolor << 4);
}

// Selects new character color in text mode.
// textcolor selects the foreground character color. This function works for 
// the console output functions. newcolor selects the new foreground color. 
// You can set newcolor to an integer as given in the table below, or to one 
// of the symbolic constants defined in conio.h. If you use symbolic constants, 
// you must include conio.h.
// Once you have called textcolor, all subsequent functions using direct video 
// output (such as cprintf) will use newcolor. textcolor does not affect any 
// characters currently onscreen.
void textcolor(int newcolor)
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
      (csbi.wAttributes & 0xf0) | newcolor);
   vActual.attribute = (csbi.wAttributes & 0xf0) | newcolor;
}

// Puts screen in text mode.
void textmode(int newmode)
{
}

// Pushes a character back to the keyboard buffer.
// ungetch pushes the character ch back to the console, causing ch to be the 
// next character read. The ungetch function fails if it is called more than 
// once before the next read.
int ungetch(int ch)
{
   INPUT_RECORD ir[2];
   DWORD escritos;
   
   ir[0].EventType = KEY_EVENT;
   ir[0].Event.KeyEvent.bKeyDown = TRUE;
   ir[0].Event.KeyEvent.wRepeatCount = 1;
   ir[0].Event.KeyEvent.wVirtualKeyCode = 0;
   ir[0].Event.KeyEvent.wVirtualScanCode = 0;
   ir[0].Event.KeyEvent.uChar.AsciiChar = ch;
   ir[0].Event.KeyEvent.dwControlKeyState = 0;
   ir[1].EventType = KEY_EVENT;
   ir[1].Event.KeyEvent.bKeyDown = FALSE;
   ir[1].Event.KeyEvent.wRepeatCount = 1;
   ir[1].Event.KeyEvent.wVirtualKeyCode = 0;
   ir[1].Event.KeyEvent.wVirtualScanCode = 0;
   ir[1].Event.KeyEvent.uChar.AsciiChar = ch;
   ir[1].Event.KeyEvent.dwControlKeyState = 0;
   if(WriteConsoleInput(GetStdHandle(STD_INPUT_HANDLE),
      ir, 2, &escritos)) return ch;
   return EOF;   
}

// Gives horizontal cursor position within window.
// wherex returns the x-coordinate of the current cursor position (within the 
// current text window).
int wherex(void)
{
   return vActual.curx;
}

// Gives vertical cursor position within window.
// wherey returns the y-coordinate of the current cursor position (within the 
// current text window).
int wherey(void)
{
   return vActual.cury;
}

// Defines active text mode window.
// window defines a text window onscreen. If the coordinates are in any way 
// invalid, the call to window is ignored.
// left and top are the screen coordinates of the upper left corner of the 
// window.
// right and bottom are the screen coordinates of the lower right corner.
// The minimum size of the text window is one column by one line. The default 
// window is full screen, with the coordinates:
//   1,1,C,R
// where C is the number of columns in the current video mode, and R is the 
// number of rows.
void window(int left, int top, int right, int bottom)
{
   vActual.winleft   = left-1;
   vActual.wintop    = top-1;
   vActual.winright  = right-1;
   vActual.winbottom = bottom-1;
   vActual.screenheight = 1+bottom-top;
   vActual.screenwidth  = 1+right-left;
   vActual.curx = 1;
   vActual.cury = 1;
   clrscr();
}

#ifdef __cplusplus
}
#endif
