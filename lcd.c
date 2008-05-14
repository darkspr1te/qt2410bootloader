#include "sys.h"
#include "graph1.h"
#include "lcd.h"


u_char *LCD_BUFER = (u_char *)LCDFRAMEBUFFER;


/*void PutPixel(u_int x,u_int y,u_int c)
{
    u_int result=0;
    if(x<SCR_XSIZE_TFT_240320 && y<SCR_YSIZE_TFT_240320)
    {
        frameBuffer8BitTft240320[(y)][(x)/4]=( frameBuffer8BitTft240320[(y)][x/4] & ~(0xff000000>>((x)%4)*8) ) | ( (c&0x000000ff)<<((4-1-((x)%4))*8) );
     //result=(result& ~(0xff000000>>((x)%4)*8) ) |( (c&0x000000ff)<<((4-1-((x)%4))*8) );
     //printf("result %d\n\r",frameBuffer8BitTft240320[(y)][(x)/4]);
     }

}*/

void PutPixel(u_int x,u_int y, u_int c )
{
	if ( (x < SCR_XSIZE_TFT_240320) && (y < SCR_YSIZE_TFT_240320) )
		LCD_BUFER[ y*SCR_XSIZE_TFT_240320 + x ] = c;
}

void Glib_Line(int x1,int y1,int x2,int y2,int color)
{
	int dx,dy,e;
	dx=x2-x1; 
	dy=y2-y1;
    
	if(dx>=0)
	{
		if(dy >= 0) // dy>=0
		{
			if(dx>=dy) // 1/8 octant
			{
				e=dy-dx/2;
				while(x1<=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1+=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			}
			else		// 2/8 octant
			{
				e=dx-dy/2;
				while(y1<=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1+=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		}
		else		   // dy<0
		{
			dy=-dy;   // dy=abs(dy)

			if(dx>=dy) // 8/8 octant
			{
				e=dy-dx/2;
				while(x1<=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1-=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			}
			else		// 7/8 octant
			{
				e=dx-dy/2;
				while(y1>=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1+=1;e-=dy;}	
					y1-=1;
					e+=dx;
				}
			}
		}	
	}
	else //dx<0
	{
		dx=-dx;		//dx=abs(dx)
		if(dy >= 0) // dy>=0
		{
			if(dx>=dy) // 4/8 octant
			{
				e=dy-dx/2;
				while(x1>=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1+=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			}
			else		// 3/8 octant
			{
				e=dx-dy/2;
				while(y1<=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1-=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		}
		else		   // dy<0
		{
			dy=-dy;   // dy=abs(dy)

			if(dx>=dy) // 5/8 octant
			{
				e=dy-dx/2;
				while(x1>=x2)
				{
					PutPixel(x1,y1,color);
					if(e>0){y1-=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			}
			else		// 6/8 octant
			{
				e=dx-dy/2;
				while(y1>=y2)
				{
					PutPixel(x1,y1,color);
					if(e>0){x1-=1;e-=dy;}	
					y1-=1;
					e+=dx;
				}
			}
		}	
	}
}

void PrintBMP(u_int x0,u_int y0,u_char bmp[])
{
    int x,y;
    int p=0;
    int i=0;
    
     for( y = y0 ; y < 320 ; y++ )
    {
    	for( x = x0 ; x < 240 ; x++ )
    	{
   			if(x<SCR_XSIZE_TFT_240320 && y<SCR_YSIZE_TFT_240320)
    		{
        		
       			
       			//LCD_BUFER[y*SCR_XSIZE_TFT_240320+x] = bmp[p+3];
       			//LCD_BUFER[y*SCR_XSIZE_TFT_240320+x+1] = bmp[p+2];
       			//LCD_BUFER[y*SCR_XSIZE_TFT_240320+x+2] = bmp[p+1];
       			//LCD_BUFER[y*SCR_XSIZE_TFT_240320+x+3] = bmp[p];
       			//p+=4;
       			//*LCD_BUFER=bmp[p];
       			LCD_BUFER[y*SCR_XSIZE_TFT_240320+x+3] = bmp[p];
       			p+=1;
       		}
       	}
    }
}

void LCDInit()
{
	int i;
	u_int* palette;
	
	frameBuffer8BitTft240320=(u_int (*)[SCR_XSIZE_TFT_240320/4])LCDFRAMEBUFFER;
	//===========Lcd port init==========//
    rGPCUP=0xffffffff; // Disable Pull-up register
    rGPCCON=0xaaaaaaaa; //Initialize VD[7:0],LCDVF[2:0],VM,VFRAME,VLINE,VCLK,LEND 
    rGPDUP=0xffffffff; // Disable Pull-up register
    rGPDCON=0xaaaaaaaa; //Initialize VD[23:8]
    
    
    //==========Lcd_Palette8Bit_Init==========//   
    rLCDCON5|=(1<<11); // 5:6:5 Palette Setting
    palette=(u_int *)(PALETTE);
    for(i=0;i<256;i++)
	//*palette++=Colorsk[i];    
	*palette++=Colorsk[i];   
	
	 //===========Lcd init==========//
    //frameBuffer8BitTft240320=(u_int (*)[SCR_XSIZE_TFT_240320/4])LCDFRAMEBUFFER;
   	rLCDCON1=(CLKVAL_TFT_240320<<8)|(MVAL_USED<<7)|(3<<5)|(11<<1)|0;
        // TFT LCD panel,8bpp TFT,ENVID=off
	rLCDCON2=(VBPD_240320<<24)|(LINEVAL_TFT_240320<<14)|(VFPD_240320<<6)|(VSPW_240320);
	rLCDCON3=(HBPD_240320<<19)|(HOZVAL_TFT_240320<<8)|(HFPD_240320);
	rLCDCON4=(MVAL<<8)|(HSPW_240320);
	rLCDCON5=(1<<11)|(1<<9)|(1<<8)|1<<1;	//FRM5:6:5,HSYNC and VSYNC are inverted,turn on BSWP
	//scroll size is defined
	//rLCDSADDR1=(((u_int)LCD_BUFER>>22)<<21)|M5D((u_int)LCD_BUFER>>1);
	//rLCDSADDR2=M5D((u_int)LCD_BUFER+(120+120)*320);
	//offsize+page width
	//rLCDSADDR3=(((SCR_XSIZE_TFT_240320-LCD_XSIZE_TFT_240320)/2)<<11)|(LCD_XSIZE_TFT_240320/2);
	
	//no scroll size defined 
	/*Example 3. LCD panel = 320*240, color, single scan
	Frame start address = 0x0c500000
	Offset dot number = 1024 dots ( 512 half words )
	LINEVAL = 240-1 = 0xef
	PAGEWIDTH = 320*8/16 = 0xa0
	OFFSIZE = 512 = 0x200
	LCDBANK = 0x0c500000 >> 22 = 0x31
	LCDBASEU = 0x100000 >> 1 = 0x80000
	LCDBASEL = 0x80000 + ( 0xa0 + 0x200 ) * ( 0xef + 1 ) = 0xa7600 */
	rLCDSADDR1=(((u_int)LCD_BUFER>>22)<<21)|M5D((u_int)LCD_BUFER>>1);
	rLCDSADDR2=M5D((u_int)LCD_BUFER>>1)+(0+LCD_XSIZE_TFT_240320/2)*(LINEVAL_TFT_240320+1);
	rLCDSADDR3=(((LCD_XSIZE_TFT_240320-LCD_XSIZE_TFT_240320))<<11)|(LCD_XSIZE_TFT_240320/2);
	
	rLCDINTMSK|=(3); // MASK LCD Sub Interrupt
	rLPCSEL&=(~7); // Disable LPC3600
	rTPAL=0; // Disable Temp Palette
	//rLCDINTPND=3;	 
	//============Lcd PowerEnable===========//
		    //GPG4 is setted as LCD_PWREN
	rGPGUP=rGPGUP&(~(1<<4))|(1<<4); // Pull-up disable
	rGPGCON=rGPGCON&(~(3<<8))|(3<<8); //GPG4=LCD_PWREN	    
	    	//Enable LCD POWER ENABLE Function
	rLCDCON5=rLCDCON5&(~(1<<3))|(1<<3);   // PWREN
	rLCDCON5=rLCDCON5&(~(1<<5))|(0<<5);   // INVPWREN   	
   			// ENVID=ON,enable the LCD output    
    rLCDCON1|=1;   	
}


void LCDClear( u_int c )
{	
	unsigned int x,y ;
		
    for( y = 0 ; y < SCR_YSIZE_TFT_240320 ; y++ )
    {
    	for( x = 0 ; x < SCR_XSIZE_TFT_240320 ; x++ )
    	{
			LCD_BUFER[y*SCR_XSIZE_TFT_240320+x] = c;
    	}
    }
}

void lcdplay(void)
{
	int i,j,k;       		      
	
	LCDClear(0xff);
	Glib_Line(0,0,240,320,0x8);
	//PrintBMP(0,0,(u_char *)ackj);	      
	/*for(k=0,j=0;j<320;j++)
       for(i=0;i<240;i++)
       {       		      
	   	PutPixel(i,j,ackj[k++]);	      
       }*/
}



