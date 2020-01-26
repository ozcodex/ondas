#include <allegro.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define PI 3.141592
#define DELAY 60
#define INC_T 0.1
#define VERSION 1.2
#define NOTAS 5

int main() 
{	
    //Copy&Paste de lo que siempte va
	allegro_init();
	install_keyboard();
	install_mouse();
	install_timer();

	//ventana del programa
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 500, 0, 0);
	
	//Mapa de bits
	BITMAP *buffer = create_bitmap(800, 600);
	clear_to_color(buffer, 0x333333);
	PALETTE pal;
    get_palette(pal);
	
	show_mouse(screen);
	
	////////////////////AQUI VA EL PROGRAMA\\\\\\\\\\\\\\\\\\\\
	
	int x=0,s=0,exit=0,temp=0,i=0,punto=0,menos=0,nota=0,color=0;
	char c[11]="0000000000";
	char c2[11]="0000000000";
    float t=0;
    float y1, y2, yr;
    float A1=3, k1=4, w1=1.6, f1=(-PI/2);
    float A2=4, k2=5, w2=-2, f2=0;
    int y1_=1, y2_=1, yr_=1;
		
    while(!key[KEY_ESC] && exit==0){
        sleep(DELAY);
                         
    	//GUI (Parte visible)
    	rectfill(buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(100,100,100));  //fondo
    	rectfill(buffer, 200, 20, 600, 80, makecol(0,0,0));          //titulo
    	textprintf_centre(buffer,font,400,30,makecol(0,255,0),"Superposicion de Ondas Sinusoidales");
    	textprintf_centre(buffer,font,400,40,makecol(0,255,0),"version %.1f ",VERSION);
    	textprintf_centre(buffer,font,400,60,makecol(0,255,0),"Oscar Eduardo Bernal ");
    	
    	rectfill(buffer, 100, 130, 390, 160, makecol(0,0,0));   //funcion onda 1
    	textprintf(buffer,font,101,131,makecol(255,0,0),"Onda 1");
    	textprintf(buffer,font,101,150,makecol(0,0,255),"y=%.2f*sen(%.2fx-%.2ft-%.2f)",A1,k1,w1,f1);
    	
    	rectfill(buffer, 410, 130, 700, 160, makecol(0,0,0));   //funcion onda 2
    	textprintf(buffer,font,411,131,makecol(255,0,0),"Onda 2");
    	textprintf(buffer,font,411,150,makecol(0,0,255),"y=%.2f*sen(%.2fx-%.2ft-%.2f)",A2,k2,w2,f2);
    	
    	rectfill(buffer, 610, 200, 620, 210, makecol(0,0,0)); //cuadros color
    	rectfill(buffer, 612, 202, 618, 208, makecol(250,250,250)); //cuadros color
    	rectfill(buffer, 610, 220, 620, 230, makecol(0,0,0));
        rectfill(buffer, 612, 222, 618, 228, makecol(0,128,0));
        
    	rectfill(buffer, 195, 195, 605, 405, makecol(0,0,0));   //graficador
    	if(color==0)
        rectfill(buffer, 200, 200, 600, 400, makecol(250,250,250));
        if(color!=0)
    	rectfill(buffer, 200, 200, 600, 400, makecol(0,80,0));
    	
    	for(x=0;x<400;x+=10){
              if(color==0)
              line(buffer,200+x,200,200+x,400,makecol(200,200,200));   
              if(color==1)
              line(buffer,200+x,200,200+x,400,makecol(0,120,0));        
        }
        for(x=0;x<200;x+=10){
              if(color==0)
              line(buffer,200,200+x,600,200+x,makecol(200,200,200));   
              if(color==1)
              line(buffer,200,200+x,600,200+x,makecol(0,120,0));   
        }           
        line(buffer,200,300,600,300,makecol(150,150,150));  //eje x
        
        //Menu inferior
        rectfill(buffer, 155, 420, 245, 450, makecol(0,0,0)); //boton y1
        if(y1_==0)
        textprintf_centre(buffer,font,200,431,makecol(255,0,0),"Onda 1");
        else
        textprintf_centre(buffer,font,200,431,makecol(0,255,0),"Onda 1");
        
        rectfill(buffer, 255, 420, 345, 450, makecol(0,0,0)); //boton y2
        if(y2_==0)
        textprintf_centre(buffer,font,300,431,makecol(255,0,0),"Onda 2");
        else
        textprintf_centre(buffer,font,300,431,makecol(0,255,0),"Onda 2");
        rectfill(buffer, 355, 420, 445, 450, makecol(0,0,0)); //boton yr
        if(yr_==0)
        textprintf_centre(buffer,font,400,431,makecol(255,0,0),"Onda R");
        else
        textprintf_centre(buffer,font,400,431,makecol(0,255,0),"Onda R");
        rectfill(buffer, 455, 420, 545, 450, makecol(0,0,0)); //boton Modificaciones
        
        textprintf_centre(buffer,font,500,431,makecol(255,0,0),"Mod. Ec.");
        rectfill(buffer, 555, 420, 645, 450, makecol(0,0,0)); //boton Comenzar
        if(s==0)
        textprintf_centre(buffer,font,600,431,makecol(255,0,0),"Comenzar");
        else
        textprintf_centre(buffer,font,600,431,makecol(0,255,0),"Comenzar");
        //notas
        rectfill(buffer, 0,490, 800, 500, makecol(0,0,0));          //ayuda que cambia cada vez q da clic          
          switch(nota%NOTAS){
             case 0:
                  textprintf(buffer,font,1,491,makecol(255,128,0),"Para salir pulse la tecla ESC");
                  break;
             case 1:
                  textprintf(buffer,font,1,491,makecol(255,128,0),"Al terminar de escribir el numero pulse ENTER y asi podra continuar con el siguiente valor");
    	          break;
             case 2:
    	          textprintf(buffer,font,1,491,makecol(255,128,0),"Si deja en blanco el valor de una variable esta tomara el valor de 0");
                  break;
             case 3:
                  textprintf(buffer,font,1,491,makecol(255,128,0),"No ponga signos de negacion (-) en medio de un numero");
                  break;
             case 4:
                  textprintf(buffer,font,1,491,makecol(255,128,0),"Este programa maneja el punto flotante con (.), sin embargo la coma (,) tambien pude ser usada");
                  break;
             case 5:
                  textprintf(buffer,font,1,491,makecol(255,128,0),"Neque porro quisquam est qui dolorem ipsum quia dolor sit amet");
                  break;       
          }
        //aqui van los botones
        
        if(mouse_b){
          
          rectfill(buffer, 0,490, 800, 500, makecol(0,0,0));          //ayuda que cambia cada vez q da clic 
          nota++;
          //sleep(100);
          if( ( mouse_x > 155 && mouse_x < 245 ) && ( mouse_y > 420 &&  mouse_y < 450 ) ){ // se pulso boton onda 1
             if(y1_==0) y1_=1;else y1_=0;
             }
          if( ( mouse_x > 255 && mouse_x < 345 ) && ( mouse_y > 420 &&  mouse_y < 450 ) ){ // se pulso boton onda 2
             if(y2_==0) y2_=1;else y2_=0;
             }
          if( ( mouse_x > 355 && mouse_x < 445 ) && ( mouse_y > 420 &&  mouse_y < 450 ) ){ // se pulso boton onda r
             if(yr_==0) yr_=1;else yr_=0;
             }
          if( ( mouse_x > 610 && mouse_x < 620 ) && ( mouse_y > 200 &&  mouse_y < 210 ) ){ // se pulso boton blanco
              color=0;
          }
          if( ( mouse_x > 610 && mouse_x < 620 ) && ( mouse_y > 220 &&  mouse_y < 230 ) ){ // se pulso boton verde
              color=1;
          }
          if( ( mouse_x > 455 && mouse_x < 545 ) && ( mouse_y > 420 &&  mouse_y < 450 ) ){ // se pulso boton mod. ec.
             textprintf_centre(buffer,font,500,431,makecol(0,255,0),"Mod. Ec.");
             rectfill(buffer, 200, 200, 600, 400, makecol(0,0,0));  //se crea un recuadro negro en el area de dibujo
             s=0; //hacemos 0 el booleano s (comenzar) para que la grafica no se mueva
             
             //aqui se modifica las ecuaciones
             //modificacion onda 1
             textprintf(buffer,font,201,220,makecol(0,128,255),"Ingrese los parametros de la Ecuacion de la onda 1");
             textprintf(buffer,font,201,230,makecol(0,128,255),"y1=A*sen(kx-wt-f)");
             textprintf(buffer,font,201,240,makecol(0,128,255),"A=");
             
             //////////Comenzamos a modificar A1//////////
             
             //se lee tecla a tecla lo que el usuario escribe, verifica si es valido (0-9,punto,menos)
             draw_sprite (screen, buffer, 0,0);  //para que muestre algo antes de pulsar tecla
             for(i=0;i<11;i++)c[i]='0';  //reiniciamos la cadena en "0000000000"
             temp=0; i=0; punto=0; menos=0;  //reinicializacion de variables
          while(temp!=17165 && i<9){
             temp=readkey();
             if(temp==18476)temp=18734; //convertimos coma en punto
             if(temp==18734)punto++; //cuenta cada vez que se pone un punto
             if(temp==18989)menos++; //cuenta cada vez que se pone un punto
             //super if con los valores aceptados
             if(
             temp==7217 ||
             temp==7474 ||
             temp==7731 ||
             temp==7988 ||
             temp==8245 ||
             temp==8502 ||
             temp==8759 ||
             temp==9016 ||
             temp==9273 ||
             temp==6960 ||
             (temp==18734 && punto<=1) ||        //(para q no se pongan mas puntos o giones de los q se deben)
             (temp==18989 && menos<=1)){          
                 
                 
                 textprintf(buffer,font,220+(i*8),240,makecol(0,128,255),"%c",(char)temp);
                 c[i]=(char)temp;
                 draw_sprite (screen, buffer, 0,0);  //debe ir dentro de cada while para q muestre algo
                 i++;
                 }
             }
             if(punto==0){
                 c[i]='.';
                 punto++;
                 }
             A1=(float)strtod(c,&c2);
             
             //////////Terminamos de modificar A1//////////
             
             textprintf(buffer,font,201,250,makecol(0,128,255),"k=");
             
             //////////Comenzamos a modificar k1//////////
             
             //se lee tecla a tecla lo que el usuario escribe, verifica si es valido (0-9,punto,menos)
             draw_sprite (screen, buffer, 0,0);  //para que muestre algo antes de pulsar tecla
             for(i=0;i<11;i++)c[i]='0';  //reiniciamos la cadena en "0000000000"
             temp=0; i=0; punto=0; menos=0;  //reinicializacion de variables
          while(temp!=17165 && i<9){
             temp=readkey();
             if(temp==18476)temp=18734; //convertimos coma en punto
             if(temp==18734)punto++; //cuenta cada vez que se pone un punto
             if(temp==18989)menos++; //cuenta cada vez que se pone un punto
             //super if con los valores aceptados
             if(
             temp==7217 ||
             temp==7474 ||
             temp==7731 ||
             temp==7988 ||
             temp==8245 ||
             temp==8502 ||
             temp==8759 ||
             temp==9016 ||
             temp==9273 ||
             temp==6960 ||
             (temp==18734 && punto<=1) ||        //(para q no se pongan mas puntos o giones de los q se deben)
             (temp==18989 && menos<=1)){          
                 
                 
                 textprintf(buffer,font,220+(i*8),250,makecol(0,128,255),"%c",(char)temp);
                 c[i]=(char)temp;
                 draw_sprite (screen, buffer, 0,0);  //debe ir dentro de cada while para q muestre algo
                 i++;
                 }
             }
             if(punto==0){
                 c[i]='.';
                 punto++;
                 }
             k1=(float)strtod(c,&c2);
             
             //////////Terminamos de modificar k1//////////
             
             textprintf(buffer,font,201,260,makecol(0,128,255),"w=");
             
             //////////Comenzamos a modificar w1//////////
             
             //se lee tecla a tecla lo que el usuario escribe, verifica si es valido (0-9,punto,menos)
             draw_sprite (screen, buffer, 0,0);  //para que muestre algo antes de pulsar tecla
             for(i=0;i<11;i++)c[i]='0';  //reiniciamos la cadena en "0000000000"
             temp=0; i=0; punto=0; menos=0;  //reinicializacion de variables
          while(temp!=17165 && i<9){
             temp=readkey();
             if(temp==18476)temp=18734; //convertimos coma en punto
             if(temp==18734)punto++; //cuenta cada vez que se pone un punto
             if(temp==18989)menos++; //cuenta cada vez que se pone un punto
             //super if con los valores aceptados
             if(
             temp==7217 ||
             temp==7474 ||
             temp==7731 ||
             temp==7988 ||
             temp==8245 ||
             temp==8502 ||
             temp==8759 ||
             temp==9016 ||
             temp==9273 ||
             temp==6960 ||
             (temp==18734 && punto<=1) ||        //(para q no se pongan mas puntos o giones de los q se deben)
             (temp==18989 && menos<=1)){          
                 
                 
                 textprintf(buffer,font,220+(i*8),260,makecol(0,128,255),"%c",(char)temp);
                 c[i]=(char)temp;
                 draw_sprite (screen, buffer, 0,0);  //debe ir dentro de cada while para q muestre algo
                 i++;
                 }
             }
             if(punto==0){
                 c[i]='.';
                 punto++;
                 }
             w1=(float)strtod(c,&c2);
             
             //////////Terminamos de modificar w1//////////
             
             textprintf(buffer,font,201,270,makecol(0,128,255),"f=");
             
             //////////Comenzamos a modificar f1//////////
             
             //se lee tecla a tecla lo que el usuario escribe, verifica si es valido (0-9,punto,menos)
             draw_sprite (screen, buffer, 0,0);  //para que muestre algo antes de pulsar tecla
             for(i=0;i<11;i++)c[i]='0';  //reiniciamos la cadena en "0000000000"
             temp=0; i=0; punto=0; menos=0;  //reinicializacion de variables
          while(temp!=17165 && i<9){
             temp=readkey();
             if(temp==18476)temp=18734; //convertimos coma en punto
             if(temp==18734)punto++; //cuenta cada vez que se pone un punto
             if(temp==18989)menos++; //cuenta cada vez que se pone un punto
             //super if con los valores aceptados
             if(
             temp==7217 ||
             temp==7474 ||
             temp==7731 ||
             temp==7988 ||
             temp==8245 ||
             temp==8502 ||
             temp==8759 ||
             temp==9016 ||
             temp==9273 ||
             temp==6960 ||
             (temp==18734 && punto<=1) ||        //(para q no se pongan mas puntos o giones de los q se deben)
             (temp==18989 && menos<=1)){          
                 
                 
                 textprintf(buffer,font,220+(i*8),270,makecol(0,128,255),"%c",(char)temp);
                 c[i]=(char)temp;
                 draw_sprite (screen, buffer, 0,0);  //debe ir dentro de cada while para q muestre algo
                 i++;
                 }
             }
             if(punto==0){
                 c[i]='.';
                 punto++;
                 }
             f1=(float)strtod(c,&c2);
             
             //////////Terminamos de modificar f1//////////
             
             
             //modificacion onda 1
             textprintf(buffer,font,201,290,makecol(0,128,255),"Ingrese los parametros de la Ecuacion de la onda 2");
             textprintf(buffer,font,201,300,makecol(0,128,255),"y2=A*sen(kx-wt-f)");
             textprintf(buffer,font,201,310,makecol(0,128,255),"A=");
             
             //////////Comenzamos a modificar A2//////////
             
             //se lee tecla a tecla lo que el usuario escribe, verifica si es valido (0-9,punto,menos)
             draw_sprite (screen, buffer, 0,0);  //para que muestre algo antes de pulsar tecla
             for(i=0;i<11;i++)c[i]='0';  //reiniciamos la cadena en "0000000000"
             temp=0; i=0; punto=0; menos=0;  //reinicializacion de variables
          while(temp!=17165 && i<9){
             temp=readkey();
             if(temp==18476)temp=18734; //convertimos coma en punto
             if(temp==18734)punto++; //cuenta cada vez que se pone un punto
             if(temp==18989)menos++; //cuenta cada vez que se pone un punto
             //super if con los valores aceptados
             if(
             temp==7217 ||
             temp==7474 ||
             temp==7731 ||
             temp==7988 ||
             temp==8245 ||
             temp==8502 ||
             temp==8759 ||
             temp==9016 ||
             temp==9273 ||
             temp==6960 ||
             (temp==18734 && punto<=1) ||        //(para q no se pongan mas puntos o giones de los q se deben)
             (temp==18989 && menos<=1)){          
                 
                 
                 textprintf(buffer,font,220+(i*8),310,makecol(0,128,255),"%c",(char)temp);
                 c[i]=(char)temp;
                 draw_sprite (screen, buffer, 0,0);  //debe ir dentro de cada while para q muestre algo
                 i++;
                 }
             }
             if(punto==0){
                 c[i]='.';
                 punto++;
                 }
             A2=(float)strtod(c,&c2);
             
             //////////Terminamos de modificar A2//////////
             
             textprintf(buffer,font,201,320,makecol(0,128,255),"k=");
             
             //////////Comenzamos a modificar k2//////////
             
             //se lee tecla a tecla lo que el usuario escribe, verifica si es valido (0-9,punto,menos)
             draw_sprite (screen, buffer, 0,0);  //para que muestre algo antes de pulsar tecla
             for(i=0;i<11;i++)c[i]='0';  //reiniciamos la cadena en "0000000000"
             temp=0; i=0; punto=0; menos=0;  //reinicializacion de variables
          while(temp!=17165 && i<9){
             temp=readkey();
             if(temp==18476)temp=18734; //convertimos coma en punto
             if(temp==18734)punto++; //cuenta cada vez que se pone un punto
             if(temp==18989)menos++; //cuenta cada vez que se pone un punto
             //super if con los valores aceptados
             if(
             temp==7217 ||
             temp==7474 ||
             temp==7731 ||
             temp==7988 ||
             temp==8245 ||
             temp==8502 ||
             temp==8759 ||
             temp==9016 ||
             temp==9273 ||
             temp==6960 ||
             (temp==18734 && punto<=1) ||        //(para q no se pongan mas puntos o giones de los q se deben)
             (temp==18989 && menos<=1)){          
                 
                 
                 textprintf(buffer,font,220+(i*8),320,makecol(0,128,255),"%c",(char)temp);
                 c[i]=(char)temp;
                 draw_sprite (screen, buffer, 0,0);  //debe ir dentro de cada while para q muestre algo
                 i++;
                 }
             }
             if(punto==0){
                 c[i]='.';
                 punto++;
                 }
             k2=(float)strtod(c,&c2);
             
             //////////Terminamos de modificar k2//////////
             
             textprintf(buffer,font,201,330,makecol(0,128,255),"w=");
             
             //////////Comenzamos a modificar w2//////////
             
             //se lee tecla a tecla lo que el usuario escribe, verifica si es valido (0-9,punto,menos)
             draw_sprite (screen, buffer, 0,0);  //para que muestre algo antes de pulsar tecla
             for(i=0;i<11;i++)c[i]='0';  //reiniciamos la cadena en "0000000000"
             temp=0; i=0; punto=0; menos=0;  //reinicializacion de variables
          while(temp!=17165 && i<9){
             temp=readkey();
             if(temp==18476)temp=18734; //convertimos coma en punto
             if(temp==18734)punto++; //cuenta cada vez que se pone un punto
             if(temp==18989)menos++; //cuenta cada vez que se pone un punto
             //super if con los valores aceptados
             if(
             temp==7217 ||
             temp==7474 ||
             temp==7731 ||
             temp==7988 ||
             temp==8245 ||
             temp==8502 ||
             temp==8759 ||
             temp==9016 ||
             temp==9273 ||
             temp==6960 ||
             (temp==18734 && punto<=1) ||        //(para q no se pongan mas puntos o giones de los q se deben)
             (temp==18989 && menos<=1)){          
                 
                 
                 textprintf(buffer,font,220+(i*8),330,makecol(0,128,255),"%c",(char)temp);
                 c[i]=(char)temp;
                 draw_sprite (screen, buffer, 0,0);  //debe ir dentro de cada while para q muestre algo
                 i++;
                 }
             }
             if(punto==0){
                 c[i]='.';
                 punto++;
                 }
             w2=(float)strtod(c,&c2);
             
             //////////Terminamos de modificar w2//////////
             
             textprintf(buffer,font,201,340,makecol(0,128,255),"f=");
             
             //////////Comenzamos a modificar f2//////////
             
             //se lee tecla a tecla lo que el usuario escribe, verifica si es valido (0-9,punto,menos)
             draw_sprite (screen, buffer, 0,0);  //para que muestre algo antes de pulsar tecla
             for(i=0;i<11;i++)c[i]='0';  //reiniciamos la cadena en "0000000000"
             temp=0; i=0; punto=0; menos=0;  //reinicializacion de variables
          while(temp!=17165 && i<9){
             temp=readkey();
             if(temp==18476)temp=18734; //convertimos coma en punto
             if(temp==18734)punto++; //cuenta cada vez que se pone un punto
             if(temp==18989)menos++; //cuenta cada vez que se pone un punto
             //super if con los valores aceptados
             if(
             temp==7217 ||
             temp==7474 ||
             temp==7731 ||
             temp==7988 ||
             temp==8245 ||
             temp==8502 ||
             temp==8759 ||
             temp==9016 ||
             temp==9273 ||
             temp==6960 ||
             (temp==18734 && punto<=1) ||        //(para q no se pongan mas puntos o giones de los q se deben)
             (temp==18989 && menos<=1)){          
                 
                 
                 textprintf(buffer,font,220+(i*8),340,makecol(0,128,255),"%c",(char)temp);
                 c[i]=(char)temp;
                 draw_sprite (screen, buffer, 0,0);  //debe ir dentro de cada while para q muestre algo
                 i++;
                 }
             }
             if(punto==0){
                 c[i]='.';
                 punto++;
                 }
             f2=(float)strtod(c,&c2);
             
             //////////Terminamos de modificar f2//////////
             
             //terminan aqui las modificaciones realizadas
             
             //continuamos todo normalmente
             textprintf_centre(buffer,font,500,431,makecol(255,0,0),"Mod. Ec.");
             }
          if( ( mouse_x > 555 && mouse_x < 645 ) && ( mouse_y > 420 &&  mouse_y < 450 ) ){ // se pulso boton start
             if(s==0) s=1;else s=0; //invertimos el booleano s (comenzar)
             }
          
          
          }
          
        //fin botones
        
        //funcion que grafica
        for(x = 200; x <= 600; x++)
               {
                   y1 =A1*sin(k1*((float)x/50)-w1*t-f1) *10;
                   y2 =A2*sin(k2*((float)x/50)-w2*t-f2) *10;
                   yr=y1+y2;
                   if(y1_==1){
                              if(color==0)
                              putpixel(buffer, x, 300 + y1, makecol(65,0,0) );  //graficar el valor de y1 
                              if(color==1)
                              putpixel(buffer, x, 300 + y1, makecol(200,200,0) );  //graficar el valor de y1   
                   }
                   if(y2_==1){
                              if(color==0)
                              putpixel(buffer, x, 300 + y2, makecol(0,65,0) );  //graficar el valor de y2 
                              if(color==1)
                              putpixel(buffer, x, 300 + y2, makecol(0,200,0) );  //graficar el valor de y2 
                   }
                   if(yr_==1){
                              if(color==0)
                              putpixel(buffer, x, 300 + yr, makecol(0,0,65) );  //graficar el valor de yr 
                              if(color==1)
                              putpixel(buffer, x, 300 + yr, makecol(100,200,200) );  //graficar el valor de yr
                   } 
               } //fin de la graficada
    draw_sprite (screen, buffer, 0,0);
    if(s==1)t+=INC_T;    
    }
    
	////////////////////AQUI TERMINA EL PROGRAMA\\\\\\\\\\\\\\\\\\\\
	readkey();	
	destroy_bitmap(buffer);
	return 0;
}
END_OF_MAIN();
