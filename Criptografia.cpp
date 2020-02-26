/*-------------------------------------------------------------------------------
   Pequeno criptador e descriptador
   versão 1.0
  
   Autor : Mauricio Taffarel
   O programa é como uma ferramenta de estudo à nova linguagem
  
 --------------------------------------------------------------------------------

   Características e funcionalidades:

   O progama criptografa avancando 26 na tabela ASCII
   Código totalmente livre para editar mantendo este título
   IMPORTANTE - Caso progama não compile baixe todas as bibiotecas abaixo  
   
 ---------------------------------------------------------------------------------  
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.c>

#define ENTER 13
#define BACKSPACE 8


char NE=191,SE=217,SO=192,NO=218,LINHA_HORIZONTAL=196,LINHA_VERTICAL=179;
int PX_MENU=6, PY_MENU=11, COMPRIMENTO_MENU=19, ALTURA_MENU=12;
int PX_MENUi=20, PY_MENUi=11, COMPRIMENTO_MENUi=40, ALTURA_MENUi=12;
char escolha=1,caractere ;
int laco_maior=1;

FILE *Arquivo;

int cabecalho()
{

	int i,j;

	//Cores
	textbackground(BLACK);
	system("CLS");
	textcolor(GREEN);
	
	//Desenho maior
	for(i=1;i<=7;i++)
	{
    for(j=1;j<=80;j++)
	   {
          gotoxy(j,i); printf("%c",219);
       }
    }
    
    //Linhas da borda
	textcolor(WHITE);
    for(i=1;i<=80;i++)
    {
    	gotoxy(i,1); printf("%c",219);
    	gotoxy(i,8); printf("%c",219);
    }
    for(i=2;i<=7;i++)
    {
    	gotoxy(1,i); printf("%c",219);
    	gotoxy(80,i); printf("%c",219);
    }
    
    //Nome grandão
 	textbackground(GREEN);
	gotoxy(10,3);printf("  ___ ___ ___ ___ _____ ___   ___ ___    _   ___ ___   _   ");
    gotoxy(10,4);printf(" / __| _ \\_ _| _ \\_   _/ _ \\ / __| _ \\  /_\\ | __|_ _| /_\\  ");
    gotoxy(10,5);printf("| (__|   /| ||  _/ | || (_) | (_ |   / / _ \\| _| | | / _ \\ ");
    gotoxy(10,6);printf(" \\___|_|_\\___|_|   |_| \\___/ \\___|_|_\\/_/ \\_\\_| |___/_/ \\_\\");
   
	gotoxy(80,25);
	textbackground(BLACK);
	return(0);	
}

int criptar()
{
	  int c,v;
	  float por;
	  
	  textbackground(BLACK);
	  for (c=14;c<=20;c++)
	  {
	  	for(v=19;v<=61;v++)
	  	{
	  		
			  
			  if ((v==19) || (v==61) || (c==14) || (c==20)) 
				{
				 gotoxy(v,c); textbackground(WHITE); textcolor(WHITE); printf("%c",219);
			    }
				else
				{
				gotoxy(v,c); textbackground(BLACK);textcolor(RED); printf(" ");
			    }
			  
			  
			  
			  
			  
			  
	  	}
	  }
	  
	  textbackground(BLACK);
	  gotoxy(35,15);
      textcolor(WHITE);
      printf("Criptando ");
      textcolor(RED);
      for(v=20;v<=60;v++)
      {
      	gotoxy(v,17);
      	printf("%c",LINHA_HORIZONTAL);
      	gotoxy(v,19);
      	printf("%c",LINHA_HORIZONTAL);
      }
      gotoxy(20,17); printf("%c",NO);
      gotoxy(20,19); printf("%c",SO);
      gotoxy(60,17); printf("%c",NE);
      gotoxy(60,19); printf("%c",SE);
      
      gotoxy(20,18); printf("%c",LINHA_VERTICAL);
      gotoxy(60,18); printf("%c",LINHA_VERTICAL);
      
      for (c=21;c<=59;c++)
      {
        textcolor(GREEN);
        Sleep(25);
        gotoxy(c,18); printf("%c",219);
        gotoxy(80,25);
      }
      
      gotoxy(35,15);
      textcolor(WHITE);
      printf("Criptado!");
      gotoxy(80,25);
      Sleep(1200);
	  textbackground(BLUE);   

}

int descriptar()
{
	  int c,v;
	  float por;
	  
	  textbackground(BLACK);
	  for (c=14;c<=20;c++)
	  {
	  	for(v=19;v<=61;v++)
	  	{
	  		
			  
			  if ((v==19) || (v==61) || (c==14) || (c==20)) 
				{
				 gotoxy(v,c); textbackground(WHITE); textcolor(WHITE); printf("%c",219);
			    }
				else
				{
				gotoxy(v,c); textbackground(BLACK);textcolor(RED); printf(" ");
			    }
			  
			  
			  
			  
			  
			  
	  	}
	  }
	  
	  textbackground(BLACK);
	  gotoxy(33,15);
      textcolor(WHITE);
      printf("Descriptando");
      textcolor(RED);
      for(v=20;v<=60;v++)
      {
      	gotoxy(v,17);
      	printf("%c",LINHA_HORIZONTAL);
      	gotoxy(v,19);
      	printf("%c",LINHA_HORIZONTAL);
      }
      gotoxy(20,17); printf("%c",NO);
      gotoxy(20,19); printf("%c",SO);
      gotoxy(60,17); printf("%c",NE);
      gotoxy(60,19); printf("%c",SE);
      
      gotoxy(20,18); printf("%c",LINHA_VERTICAL);
      gotoxy(60,18); printf("%c",LINHA_VERTICAL);
      
      for (c=21;c<=59;c++)
      {
        textcolor(GREEN);
        Sleep(25);
        gotoxy(c,18); printf("%c",219);
        gotoxy(80,25);
      }
      
      gotoxy(33,15);
      textcolor(WHITE);
      printf("Descriptado!");
      gotoxy(80,25);
      Sleep(1200);
	  textbackground(BLUE);   

}


int menu()
{
	int i,j,k,l;
	
	//Desenho dos botões
	textcolor(GREEN);
	l=7;
	for(k=1;k<=3;k++)
	{
		for(i=l;i<=(l+17);i++)
		{
			for(j=12;j<=22;j++)
			{	
				gotoxy(i,j);
				if ((i==l) || (j==12) || (j==22) || (i==l+17)) 
				{
				textcolor(WHITE); printf("%c",219);
			    }
				else
				{
				textcolor(GREEN); printf("%c",219);
			    }
			}		
		}
		l=l+25;
    }
    
    //Desenho interno dos botões
    textbackground(GREEN);
    textcolor(BROWN);
    
    //CADEADO
    gotoxy(13,16); printf("%c%c%c%c%c%c",219,219,219,219,219,219);
    gotoxy(13,17); printf("%c%c%c%c%c%c",219,219,219,219,219,219);
    gotoxy(13,18); printf("%c%c%c%c%c%c",219,219,219,219,219,219);
    
	textcolor(YELLOW);
	gotoxy(13,15); printf("%c",219);
    gotoxy(18,15); printf("%c",219);
    gotoxy(14,14); printf("%c%c%c%c",219,219,219,219);
   
    //CADEADO ABERTO 
    textcolor(BROWN);
    gotoxy(38,16); printf("%c%c%c%c%c%c",219,219,219,219,219,219);
    gotoxy(38,17); printf("%c%c%c%c%c%c",219,219,219,219,219,219);
    gotoxy(38,18); printf("%c%c%c%c%c%c",219,219,219,219,219,219);
    
	textcolor(YELLOW);
    gotoxy(38,15); printf("%c",219);
    gotoxy(39,14); printf("%c%c%c%c%c",219,219,219,219,219);
    textcolor(WHITE);
    
    textcolor(RED);
    gotoxy(65,16); printf("%c",219);
    gotoxy(64,15); printf("%c",219);
    gotoxy(63,14); printf("%c",219);
    gotoxy(66,15); printf("%c",219);
    gotoxy(67,14); printf("%c",219);
    gotoxy(64,17); printf("%c",219);
    gotoxy(63,18); printf("%c",219);
    gotoxy(66,17); printf("%c",219);
    gotoxy(67,18); printf("%c",219);
   
    
    //Nomes do botão
    textbackground(GREEN);
    textcolor(WHITE);
    gotoxy(13,20); printf("CRIPTAR");
    gotoxy(36,20); printf("DESCRIPTAR");
    gotoxy(64,20); printf("SAIR");
    
    //Nomes de baixo      
   gotoxy(80,25); 
   textbackground(BLACK);
   textcolor(WHITE); 
   return(0);	
}

int quadradoselecao_menu()
{
	int i;
	char SELECAO_MENU='v';
 
	 //Quinas
    gotoxy(PX_MENU,PY_MENU); printf("%c",NO); //NO
    gotoxy(PX_MENU,PY_MENU+ALTURA_MENU); printf("%c",SO); //SO
    
    
	//Linhas horizontais
	for(i=PX_MENU+1;i<=PX_MENU+COMPRIMENTO_MENU-1;i++)
	{
		gotoxy(i,PY_MENU); printf("%c",LINHA_HORIZONTAL);
		gotoxy(i,PY_MENU+ALTURA_MENU); printf("%c",LINHA_HORIZONTAL);
    }
    
    //Linhas verticais
    for(i=PY_MENU+1;i<=PY_MENU+ALTURA_MENU-1;i++)
    {
        gotoxy(PX_MENU,i); printf("%c",LINHA_VERTICAL);
		gotoxy(PX_MENU+COMPRIMENTO_MENU,i); printf("%c",LINHA_VERTICAL);	
    }
    
    //Quinas
	gotoxy(PX_MENU+COMPRIMENTO_MENU,PY_MENU); printf("%c",NE); //NE
	gotoxy(PX_MENU+COMPRIMENTO_MENU,PY_MENU+ALTURA_MENU); printf("%c",SE); //SE
    gotoxy(80,25);
  
}

int lugar_texto()
{
int i,j;
	textcolor(WHITE);
	system("CLS");
	cabecalho();
	 //Quinas
    gotoxy(PX_MENUi,PY_MENUi); printf("%c",219); //NO
    gotoxy(PX_MENUi,PY_MENUi+ALTURA_MENUi); printf("%c",219); //SO
    
    
	//Linhas horizontais
	for(i=PX_MENUi+1;i<=PX_MENUi+COMPRIMENTO_MENUi-1;i++)
	{
		gotoxy(i,PY_MENUi); printf("%c",219);
		gotoxy(i,PY_MENUi+ALTURA_MENUi); printf("%c",219);
    }
    
    //Linhas verticais
    for(i=PY_MENUi+1;i<=PY_MENUi+ALTURA_MENUi-1;i++)
    {
        gotoxy(PX_MENUi,i); printf("%c",219);
		gotoxy(PX_MENUi+COMPRIMENTO_MENUi,i); printf("%c",219);	
    }
    
    //Quinas
	gotoxy(PX_MENUi+COMPRIMENTO_MENUi,PY_MENUi); printf("%c",219); //NE
	gotoxy(PX_MENUi+COMPRIMENTO_MENUi,PY_MENU+ALTURA_MENUi); printf("%c",219); //SE
    gotoxy(80,25);
    
    textbackground(GREEN);
	for(j=21;j<=59;j++)
    {
    	for(i=12;i<=22;i++)
    	{
    		gotoxy(j,i); printf(" ");	
    	}
    }

	textbackground(BLACK);
	textcolor(YELLOW); gotoxy(22,25); printf("Tecle ENTER ap%cs digitar sua mensagem",162);
	
}

int inserir_texto()
{
	int i,j,k;
	char caractere;
	Arquivo = fopen ("Cripografado.txt","w");
	if (Arquivo == NULL) 
	{
	gotoxy(22,25);
 	printf("Arquivo nao pode ser aberto!");
 	getch();
 	}
	else 
	{	
		textbackground(GREEN);
	
		
		for(j=13;j<=21;j++)
   		 {
    		for(i=22;i<=58;i++)
    		
				{	
    				
    				gotoxy(i,j);
    				caractere=getche();
    				if (caractere==ENTER) 
					{	
						escolha=0;
						
						break;
					}									
    			
				/*
				
					if (caractere==BACKSPACE) 
    				{
    					i--;
    					gotoxy(i,j); printf(" ");
						i--;
						caractere=' ';
																		
    				}
    				
    			*/
    				
				    putc(caractere+26, Arquivo);
				    putc(caractere+46, Arquivo);
				    putc(caractere+51, Arquivo);
				    putc(caractere+70, Arquivo);
					putc(caractere+47, Arquivo);
				    putc(caractere+52, Arquivo);
				    putc(caractere+69, Arquivo);
				    putc(caractere+48, Arquivo);
				    putc(caractere+10, Arquivo);
				    putc(caractere+75, Arquivo);
				    putc(caractere+146, Arquivo);
				    putc(caractere+151, Arquivo);
				    putc(caractere+170, Arquivo);
					putc(caractere+147, Arquivo);
				    putc(caractere+152, Arquivo);
				    putc(caractere+169, Arquivo);
				    putc(caractere+148, Arquivo);
				    putc(caractere+110, Arquivo);
				    putc(caractere+175, Arquivo);
				    putc(caractere+126, Arquivo);
				    putc(caractere+146, Arquivo);
				    putc(caractere+151, Arquivo);
				    putc(caractere+170, Arquivo);
					putc(caractere+147, Arquivo);
				    putc(caractere+152, Arquivo);
				    putc(caractere+169, Arquivo);
				    putc(caractere+148, Arquivo);
				    putc(caractere+110, Arquivo);
				    putc(caractere+175, Arquivo);
				    putc(caractere+6, Arquivo);
				    putc(caractere+1, Arquivo);
				    putc(caractere+7, Arquivo);
					putc(caractere+7, Arquivo);
				    putc(caractere+2, Arquivo);
				    putc(caractere+9, Arquivo);
				    putc(caractere+8, Arquivo);
				    putc(caractere+1, Arquivo);
				    putc(caractere+7, Arquivo);
				    
    			}
    			
 			  if (escolha==0) break;   		
				
    	 }
		
	fclose(Arquivo);
			
    }
}


int movimentoquadrado_menu()
{
	 char opcao;
	 int i,j; 
	escolha=1;
	while (escolha)
	{	
			
		opcao=getch();
		
	//DIREITA	
	if ((opcao=='D')||(opcao=='d'))  
	{	
		if (escolha!=3)		
	    {
	    NE=32;
		SE=32;
		SO=32;
		NO=32;
		LINHA_HORIZONTAL=32;
		LINHA_VERTICAL=32;
	    quadradoselecao_menu();
	
	    NE=191;
		SE=217;
		SO=192;
		NO=218;
		LINHA_HORIZONTAL=196;
		LINHA_VERTICAL=179;
		PX_MENU=PX_MENU+25;
	    quadradoselecao_menu();
		escolha=escolha+1;
		gotoxy(80,25);
			
		}
		else 
		{
		}	 
	}
	
	//ESQUERDA
	else if ((opcao=='A')||(opcao=='a'))  
	{
     if (escolha!=1)		
	    {
	    NE=32;
		SE=32;
		SO=32;
		NO=32;
		LINHA_HORIZONTAL=32;
		LINHA_VERTICAL=32;
	    quadradoselecao_menu();
	    
	    NE=191;
		SE=217;
		SO=192;
		NO=218;
		LINHA_HORIZONTAL=196;
		LINHA_VERTICAL=179;
		PX_MENU=PX_MENU-25;
	    quadradoselecao_menu();
		escolha=escolha-1;
		gotoxy(80,25);
		;		
		}
		
	}
	
	 else if (opcao==ENTER)	
	 
	 {
     	if (escolha==3)
     	{
     		exit(0);
     	}
	
	 	if (escolha==2)
	 	{
	 		int i=22,j=13;
	 		descriptar();
	 		lugar_texto();
	 		gotoxy(22,25); printf("                                      ");
	 		textbackground(GREEN);
			Arquivo = fopen ("Cripografado.txt","r");
			while( (caractere=fgetc(Arquivo))!= EOF )
			{
					
					gotoxy(i,j);
					putchar(caractere-26);
					putc(caractere-46, Arquivo);
				    putc(caractere-51, Arquivo);
				    putc(caractere-70, Arquivo);
					putc(caractere-47, Arquivo);
				    putc(caractere-52, Arquivo);
				    putc(caractere-69, Arquivo);
				    putc(caractere-48, Arquivo);
				    putc(caractere-10, Arquivo);
				    putc(caractere-75, Arquivo);
				    putc(caractere-106, Arquivo);
				    putc(caractere-151, Arquivo);
				    putc(caractere-170, Arquivo);
					putc(caractere-147, Arquivo);
				    putc(caractere-152, Arquivo);
				    putc(caractere-169, Arquivo);
				    putc(caractere-148, Arquivo);
				    putc(caractere-110, Arquivo);
				    putc(caractere-175, Arquivo);
				    putc(caractere-126, Arquivo);
				    putc(caractere-146, Arquivo);
				    putc(caractere-151, Arquivo);
				    putc(caractere-170, Arquivo);
					putc(caractere-147, Arquivo);
				    putc(caractere-152, Arquivo);
				    putc(caractere-169, Arquivo);
				    putc(caractere-148, Arquivo);
				    putc(caractere-110, Arquivo);
				    putc(caractere-175, Arquivo);
				    putc(caractere-6, Arquivo);
				    putc(caractere-1, Arquivo);
				    putc(caractere-7, Arquivo);
					putc(caractere-7, Arquivo);
				    putc(caractere-2, Arquivo);
				    putc(caractere-9, Arquivo);
				    putc(caractere-8, Arquivo);
				    putc(caractere-1, Arquivo);
				    putc(caractere-7, Arquivo);
				    
												
					i++;
					if(i==58) 
					{
					i=22;
					j++;
					}
	
				
			
			}
		getch();
		PX_MENU=6;
		break;				
	 	}
	 	
	 	if (escolha==1);
		{	
			lugar_texto();
			inserir_texto();
			criptar(); 
			fclose(Arquivo);
		} 
	 	
		
      }
    
     }
	
} 



int main()
{
	
	while (laco_maior)
	{
	escolha=1;	
	cabecalho();
	menu();
	quadradoselecao_menu();
	movimentoquadrado_menu();
    }
	textbackground(BLACK);
	gotoxy(80,25);
	
	
}
