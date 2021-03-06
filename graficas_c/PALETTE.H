/*
  斃様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様与
  � Palette.h  (versi�n 0.1)                                               �
  �                                                                        �
  � Librer�a gr�fica para el tratamiento de la paleta                      �
  �                                                                        �
  � Se incluyen funciones para cambiar los colores de la paleta o          �
  � efectos como fundidos o rotaci�n de paleta.                            �
  �                                                                        �
  � Para incluirla en cualquier programa C basta con usar la orden         �
  � #include "Palette.h"                 al principio del mismo.           �
  �                                                                        �
  � Nota : Para utilizar esta libreria es necesario compilar con la        �
  �        opci�n del compilador '-1' para que utilice las instrucciones   �
  �        del 286.    ( bcc -1 nombre.c )                                 �
  �                                                                        �
  � C�digo y texto: 陳�] Bizarre inc. [陳�  de Compiler SoftWare.          �
  斥様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様�1997 C.S.踊
*/

#ifndef __DOS_H
  #include <dos.h>
#endif                            /* si no est� incluida dos.h, incluirla */
			  

/* 陳陳陳陳陳陳陳陳陳陳陳 Funciones implementadas: 陳陳陳陳陳陳陳陳陳陳� */

void SetPaletteC(char, char, char, char );
			/* Cambia un color con funciones C */
void GetPaletteC(char, char *, char *, char *);
			/* Captura un color con funciones C  */
void SetPaletteBIOS( char far * );
			/* Cambia la paleta entera con interrupciones  */
void GetPaletteBIOS( char far * );
			/* Captura la paleta entera con interrupciones */
void SetPalette( char far * );
			/* Cambia la paleta entera con puertos         */
void GetPalette( char far * );
			/* Captura la paleta entera con puertos        */

void SetRGBValue( char, char, char, char );
			/* Cambia un solo valor con puertos            */
void GetRGBValue( char, char *, char *, char * );
			/* Captura un solo valor con puertos           */

/*void WaitVRetraceC(void); /* ** */
			/* Se espera an retrazo vertical con func. C   */
/*void WaitVRetrace(void);
			/* Se espera al retrazo con ensamblador        */

void FadeOut( void );   /* Realiza un fundido a negro                  */
void FadeIn( char * );  /* Hace un fundido del negro a una paleta      */
void FadeTo( char * );  /* Hace un fundido desde una paleta a otra     */
void RotatePaletteLeft ( char * );  /* Rota la paleta                  */
void RotatePaletteRight( char * );  /* Rota la paleta                  */

void NegativePalette ( char * );    /* Hace el negativo de una imagen    */
void GreyPalette (char *);          /* Pasa la paleta a escala de grises */

/* 様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様� */
/* 様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様様� */

/* 陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳� */
void SetPaletteC ( char color, char r, char g, char b)
{
   outportb (0x3C8, color);
   outportb (0x3C9, r);
   outportb (0x3C9, g);
   outportb (0x3C9, b);
}

/* 陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳� */
void GetPaletteC ( char color, char *r,  char *g,  char *b)
{
   outportb (0x3C7, color);
   *r = inportb (0x3C9);
   *g = inportb (0x3C9);
   *b = inportb (0x3C9);
}

/* 陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳� */
void SetPaletteBIOS  ( char far *paleta)
{
   asm {
	les dx, [paleta]
	mov ax, 0x1012
	mov bx, 0
	mov cx, 256
	int 0x10
       }
}

/* 陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳� */
void GetPaletteBIOS  ( char far *paleta)
{
   asm {
	les dx, [paleta]
	mov ax, 0x1017
	mov bx, 0
	mov cx, 256
	int 0x10
       }
}

/* 陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳� */
void SetPalette  ( char far *paleta)
{
   asm {
	push ds
	lds si, [paleta]
	mov cx, 256*3
	mov al, 0
	mov dx, 3c8h
	out dx, al
	inc dx
	rep outsb
	pop ds
       }
}

/* 陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳� */
void GetPalette  ( char far *paleta)
{
   asm {
	les di, [paleta]
	mov cx, 256*3
	mov al, 0
	mov dx, 3c7h
	out dx, al
	add dx, 2
	rep insb
       }
}

/* 陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳� */
void SetRGBValue(  char color, char r, char g, char b )
{
  asm {
      mov dx, 0x3C8
      mov al, [color]
      out dx, al
      inc dx
      mov al, [r]
      out dx, al
      mov al, [g]
      out dx, al
      mov al, [b]
      out dx, al
  }
}

/* 陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳� */
void SetRGBPalette(  char *paleta )
{
   int x;

  outportb (0x3C8, 0);
  
  for (x=0;x<768;x++)
    outportb (0x3C9, paleta[x]);
}

/* 陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳� */
void GetRGBValue(  char color,  char *r,  char *g,  char *b )
{
  asm {
      mov dx, 0x3C7
      mov al, [color]
      out dx, al
      add dx, 2
      in al, dx
      mov bl, al
      in al, dx
      mov bh, al
      in al, dx
      mov cl, al
      }
  *r = _BL;
  *g = _BH;
  *b = _CL;
}

/* 陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳� 
void WaitVRetraceC(void)
{
  while ((inportb(0x03DA) & 8) != 0);
  while ((inportb(0x03DA) & 8) == 0);
} */

/* 陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳� 
void WaitVRetrace (void)
{
asm   mov dx, 0x03DA
Retrazo1:
asm {
	in      al, dx
	test    al, 8
	jnz     Retrazo1
    }
Retrazo2:
asm {
	in      al, dx
	test    al, 8
	jz      Retrazo2
    }
}*/

/* 陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳� */
/*
   陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
	Hace un fundido a negro desde la paleta que est� en el DAC
   陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
*/
void FadeOut(void)
{
   char paleta[768];
   int x, y;

  GetPalette (paleta);

  for (y=0; y<63; y++)
  {
      for (x=0;x<768;x++)
	if (paleta[x] > 0) paleta[x]--;
      WaitVRetrace ();
      SetPalette(paleta);
  }
}

/* 陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳� */
/*
  陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    Hace un fundido desde negros hasta la paleta que se le indique como 
	  par�metro. La paleta debe tener como m�nimo 768 bytes
  陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
*/
void FadeIn ( char *paleta )
{
   char pal[768];
   int x, y;

  for (y=0;y<768;y++) pal[y] = 0;

  for (y=0; y<63; y++)
  {
      for (x=0;x<768;x++)
	if (pal[x] < paleta[x]) pal[x]++;

  WaitVRetrace();
  SetPalette(pal);
  }
}

/* 陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳� */
/*
  陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
   Hace un fundido desde la paleta actual (del DAC) hasta la paleta que
   se pase como par�metro. Esta debe tener un tama�o minimo de 768 bytes
  陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
*/
void FadeTo ( char *paleta)
{
   char pal[768];
   int x, y;

  GetPalette (pal);

  for (y=0;y<63;y++)
  {
      for (x=0;x<768;x++)
      {
	if (pal[x] < paleta[x]) pal[x]++;
	if (pal[x] > paleta[x]) pal[x]--;
      }
  WaitVRetrace();
  WaitVRetrace();
  SetPalette(pal);
  }
}
/* 陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳� */
/*
  陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    Rota la paleta hacia la derecha una posici�n cada vez que es llamada
			       la funci�n
  陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
*/

void RotatePaletteLeft ( char *paleta)
{
   char r, g, b;
   int x;

    r = paleta[0];
    g = paleta[1];
    b = paleta[2];
    for (x=0;x<765;x+=3)
    {
    paleta[x] = paleta[x+3];
    paleta[x+1] = paleta[x+4];
    paleta[x+2] = paleta[x+5];
    }
    paleta[765] = r;
    paleta[766] = g;
    paleta[767] = b;

    WaitVRetrace();
    SetPalette (paleta);
}
/* 陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳� */
/*
  陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
    Rota la paleta hacia la izquierda una posici�n cada vez que es
			llamada la funci�n
  陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
*/

void RotatePaletteRight ( char *paleta)
{
   char r, g, b;
   int x;

    r = paleta[765];
    g = paleta[766];
    b = paleta[767];
    for (x=767;x>3;x-=3)
    {
    paleta[x] = paleta[x-3];
    paleta[x-1] = paleta[x-4];
    paleta[x-2] = paleta[x-5];
    }
    paleta[0] = r;
    paleta[1] = g;
    paleta[2] = b;

    WaitVRetrace();
    SetPalette (paleta);
}
/* 陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳� */
/*
  陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
		     Realiza el negativo de la  paleta
  陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
*/

void NegativePalette ( char *paleta )
{
  int x;
  for (x=0;x<768;x+=3) 
	{
	 paleta[x] = 63-paleta[x];
	 paleta[x+1] = 63 - paleta[x+1];
	 paleta[x+2] = 63 - paleta[x+2];
	}
  SetPalette (paleta);
}

/* 陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳� */
/*
  陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
		     Pasa la paleta a escala de grises
  陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳�
*/

void GreyPalette (char *paleta)
{
  int x, y;
  int media;

  for (x=0;x<768;x+=3)
  {
     media = (paleta[x] + paleta[x+1] + paleta[x+2]) / 3;
     paleta[x] = media;
     paleta[x+1] = media;
     paleta[x+2] = media;
  }
  SetPalette (paleta);
}

/*
+-----------------------------------------------------------------------+
|                          Fin de fichero                               |
+------------------------------------------------------- E.S.I.M.E -----+
*/
