#include<math.h>
#include<dos.h>
#include<conio.h>
#include<stdio.h>

#include "d:\c4v4\f.h"
main()
{

 int i, it;
 real a,b,c;

 clrscr();
      printf("\n calcula el metodo de biseccion" );
      printf("\n dada la ecuacion xό+4xύ-10 y el intervalo [a,b]");
      printf("\n introduce el valor de a:");
      scanf("%lf", &a);
      printf("\n introduce el valor de b:");
      scanf("%lf", &b);

      printf("\n Cuantas interaciones son en total? ");
      scanf("%d", &it);
      clrscr();
      textcolor(15);
      cprintf("ΙΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝ»");
      textcolor(15);
      cprintf("\n\rΊ i         a        c        b        fa        fc        fb    Ί");
      printf("\n");
      textcolor(15);
      cprintf("ΜΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΉ");

  for (i=0; i<=it+1; i++)
  {

      printf("\nΊ %d \t", i);
      textcolor(2);
      cprintf("%2.2lf", a);
	    c=(a+b)/2;
      textcolor(14);
      cprintf("   %2.2lf", c);
      textcolor(3);
      cprintf("   %2.2lf", b);

      textcolor(5);
      cprintf("     %3.2lf",f(a));
      textcolor(15);
      cprintf("    %3.2lf",f(c));
      textcolor(6);
      cprintf("   %3.2lf Ί ",f(b));


      if (f(a)<0 && f(c)>0)
	{
	  a=a;
	  b=c;
	}
      else if(f(c)<0 && f(b)>0)
       {
	  a=c;
	  b=b;
       }
  }

  textcolor(15);
  cprintf("\n\rΘΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΝΌ");


   sound(400);
   delay(200);
   sound(500);
   delay(300);
   sound(600);
   delay(200);
   sound(500);
   delay(300);
   nosound();


  textcolor(137);
  cprintf("\n\r La raiz de la Ecuacion es: ");
  textcolor(138);
  cprintf("%2.5lf",c);
  getch();
}
