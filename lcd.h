// == Params == //
#define CLKVAL_TFT_240320	(4) 	
#define MVAL		(13)
#define MVAL_USED 	(0)

//Timing parameter for LTS350Q1(SAMSUNG) 
#define VBPD_240320		((2-1)&0xff)
#define VFPD_240320		((3)&0xff)
#define VSPW_240320		((2) &0x3f)
#define HBPD_240320		((12)&0x7f)
#define HFPD_240320		((12)&0xff)
#define HSPW_240320		((30)&0xff)

#define M5D(n) ((n) & 0x1fffff)	// To get lower 21bits
//TFT240320
#define HOZVAL_TFT_240320	(LCD_XSIZE_TFT_240320-1)
#define LINEVAL_TFT_240320	(LCD_YSIZE_TFT_240320-1)
//TFT 240320
#define LCD_XSIZE_TFT_240320 	(240)	
#define LCD_YSIZE_TFT_240320 	(320)

//#define SCR_XSIZE_TFT_240320 	(LCD_XSIZE_TFT_240320*2)
//#define SCR_YSIZE_TFT_240320 	(LCD_YSIZE_TFT_240320*2)
#define SCR_XSIZE_TFT_240320 	(240)
#define SCR_YSIZE_TFT_240320 	(320)

// LCD Params
u_int (*frameBuffer8BitTft240320)[SCR_XSIZE_TFT_240320/4];

#define LCDFRAMEBUFFER 0x33800000 //_NONCACHE_STARTADDRESS 
