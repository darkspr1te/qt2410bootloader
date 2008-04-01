#include "sys.h"
#include "usb.h"

//for ep3 variables
volatile u_int download_addr;
volatile u_char *downPt;
volatile u_int download_len;
volatile u_int totalDmaCount;
volatile u_short checkSum;


//common variables
u_char *UsbTxAddr=(u_char *)0x31000000;
u_int UsbState;
u_int UsbInLength;
u_int UsbFunction=0; //for test purpose

struct USB_SETUP_DATA descSetup;
struct USB_DEVICE_DESCRIPTOR descDev;
struct USB_CONFIGURATION_DESCRIPTOR descConf;
struct USB_INTERFACE_DESCRIPTOR descIf;
struct USB_ENDPOINT_DESCRIPTOR descEndpt0;
struct USB_ENDPOINT_DESCRIPTOR descEndpt1;
bool isUSBSet=false;
u_int ep0State;
//forward declaration
void ConfigUsbd(void);
extern void Ep0Handler(void);

void RdPktEp0(u_char *buf,int num)
{
    int i;
    	
    for(i=0;i<num;i++)
    {
        buf[i]=(u_char)rEP0_FIFO;	
    }
}
    

void WrPktEp0(u_char *buf,int num)
{
    int i;
    	
    for(i=0;i<num;i++)
    {
        rEP0_FIFO=buf[i];	
    }
}


void WrPktEp1(u_char *buf,int num)
{
    int i;
    	
    for(i=0;i<num;i++)
    {
        rEP1_FIFO=buf[i];	
    }
}


void WrPktEp2(u_char *buf,int num)
{
    int i;
    	
    for(i=0;i<num;i++)
    {
        rEP2_FIFO=buf[i];	
    }
}


void RdPktEp3(u_char *buf,int num)
{
    int i;
    	
    for(i=0;i<num;i++)
    {
        buf[i]=(u_char)rEP3_FIFO;	
    }
}


void RdPktEp4(u_char *buf,int num)
{
    int i;
    	
    for(i=0;i<num;i++)
    {
        buf[i]=(u_char)rEP4_FIFO;	
    }
}


void usbIRQ()
{
	u_char usbdIntpnd, epIntpnd;
    u_char saveIndexReg = rINDEX_REG;
    
    usbdIntpnd = rUSB_INT_REG;
    epIntpnd = rEP_INT_REG;    

    if(usbdIntpnd&SUSPEND_INT)
    {
    	rUSB_INT_REG = SUSPEND_INT;    	
    }
    if(usbdIntpnd&RESUME_INT)
    {
    	rUSB_INT_REG = RESUME_INT;    	
    }
    if(usbdIntpnd&RESET_INT)
    { 
    	ConfigUsbd();
    	rUSB_INT_REG = RESET_INT;  //RESET_INT should be cleared after ResetUsbd().   	
    }
    if(epIntpnd&EP0_INT)
    {
		rEP_INT_REG = EP0_INT;  
    	Ep0Handler();
    }
    if(epIntpnd&EP1_INT)
    {
    	rEP_INT_REG=EP1_INT;  
    	//Ep1Handler();
    }

    if(epIntpnd&EP2_INT)
    {
    	rEP_INT_REG = EP2_INT;  
    	//Ep2Handler();
    }

    if(epIntpnd&EP3_INT)
    {
    	rEP_INT_REG = EP3_INT;
    	Ep3Handler();
    }

    if(epIntpnd&EP4_INT)
    {
    	rEP_INT_REG = EP4_INT;    		
    	//Ep4Handler();
    }
    rINDEX_REG = saveIndexReg;
}
void ConfigUsbd(void)
{
	// *** End point information ***
//   EP0: control
//   EP1: bulk in end point
//   EP2: not used
//   EP3: bulk out end point
//   EP4: not used
    
    rPWR_REG=PWR_REG_DEFAULT_VALUE;	//disable suspend mode

    rINDEX_REG=0;	
    rMAXP_REG=FIFO_SIZE_8;   	//EP0 max packit size = 8 
    rEP0_CSR=EP0_SERVICED_OUT_PKT_RDY|EP0_SERVICED_SETUP_END;	
 				//EP0:clear OUT_PKT_RDY & SETUP_END
    rINDEX_REG=1;
    #if (EP1_PKT_SIZE==32)
        rMAXP_REG=FIFO_SIZE_32;	//EP1:max packit size = 32
    #else
	rMAXP_REG=FIFO_SIZE_64;	//EP1:max packit size = 64
    #endif	
    rIN_CSR1_REG=EPI_FIFO_FLUSH|EPI_CDT;	
    rIN_CSR2_REG=EPI_MODE_IN|EPI_IN_DMA_INT_MASK|EPI_BULK; //IN mode, IN_DMA_INT=masked    
    rOUT_CSR1_REG=EPO_CDT;   	
    rOUT_CSR2_REG=EPO_BULK|EPO_OUT_DMA_INT_MASK;   	

    rINDEX_REG=2;
    rMAXP_REG=FIFO_SIZE_64;	//EP2:max packit size = 64
    rIN_CSR1_REG=EPI_FIFO_FLUSH|EPI_CDT|EPI_BULK;
    rIN_CSR2_REG=EPI_MODE_IN|EPI_IN_DMA_INT_MASK; //IN mode, IN_DMA_INT=masked    
    rOUT_CSR1_REG=EPO_CDT;   	
    rOUT_CSR2_REG=EPO_BULK|EPO_OUT_DMA_INT_MASK;   	

    rINDEX_REG=3;
    #if (EP3_PKT_SIZE==32)
        rMAXP_REG=FIFO_SIZE_32;	//EP3:max packit size = 32
    #else
	rMAXP_REG=FIFO_SIZE_64;	//EP3:max packit size = 64
    #endif	
    rIN_CSR1_REG=EPI_FIFO_FLUSH|EPI_CDT|EPI_BULK;
    rIN_CSR2_REG=EPI_MODE_OUT|EPI_IN_DMA_INT_MASK; //OUT mode, IN_DMA_INT=masked    
    rOUT_CSR1_REG=EPO_CDT;   	
    //clear OUT_PKT_RDY, data_toggle_bit.
	//The data toggle bit should be cleared when initialization.
    rOUT_CSR2_REG=EPO_BULK|EPO_OUT_DMA_INT_MASK;   	

    rINDEX_REG=4;
    rMAXP_REG=FIFO_SIZE_64;	//EP4:max packit size = 64
    rIN_CSR1_REG=EPI_FIFO_FLUSH|EPI_CDT|EPI_BULK;
    rIN_CSR2_REG=EPI_MODE_OUT|EPI_IN_DMA_INT_MASK; //OUT mode, IN_DMA_INT=masked    
    rOUT_CSR1_REG=EPO_CDT;   	
    //clear OUT_PKT_RDY, data_toggle_bit.
	//The data toggle bit should be cleared when initialization.
    rOUT_CSR2_REG=EPO_BULK|EPO_OUT_DMA_INT_MASK;   	
    
    rEP_INT_REG=EP0_INT|EP1_INT|EP2_INT|EP3_INT|EP4_INT;
    rUSB_INT_REG=RESET_INT|SUSPEND_INT|RESUME_INT; 
    //Clear all usbd pending bits
    	
    //EP0,1,3 & reset interrupt are enabled
    rEP_INT_EN_REG=EP0_INT|EP1_INT|EP3_INT;
    rUSB_INT_EN_REG=RESET_INT;
    ep0State=EP0_STATE_INIT;
}

void InitDescriptorTable(void)
{	
    //Standard device descriptor
    descDev.bLength=0x12;	//EP0_DEV_DESC_SIZE=0x12 bytes    
    descDev.bDescriptorType=DEVICE_TYPE;         
    descDev.bcdUSBL=0x10;
    descDev.bcdUSBH=0x01; 	//Ver 1.10
    descDev.bDeviceClass=0xFF; //0x0          
    descDev.bDeviceSubClass=0x0;          
    descDev.bDeviceProtocol=0x0;          
    descDev.bMaxPacketSize0=0x8;         
    descDev.idVendorL=0x45;
    descDev.idVendorH=0x53;
    descDev.idProductL=0x34;
    descDev.idProductH=0x12;
    descDev.bcdDeviceL=0x00;
    descDev.bcdDeviceH=0x01;
    descDev.iManufacturer=0x1;  //index of string descriptor
    descDev.iProduct=0x2;	//index of string descriptor 
    descDev.iSerialNumber=0x0;
    descDev.bNumConfigurations=0x1;

    //Standard configuration descriptor
    descConf.bLength=0x9;    
    descConf.bDescriptorType=CONFIGURATION_TYPE;         
    descConf.wTotalLengthL=0x20; //<cfg desc>+<if desc>+<endp0 desc>+<endp1 desc>
    descConf.wTotalLengthH=0;
    descConf.bNumInterfaces=1;
	//dbg    descConf.bConfigurationValue=2;  //why 2? There's no reason.
    descConf.bConfigurationValue=1;  
    descConf.iConfiguration=0;
    descConf.bmAttributes=CONF_ATTR_DEFAULT;  //bus powered only.
    descConf.maxPower=25; //draws 50mA current from the USB bus.          

    //Standard interface descriptor
    descIf.bLength=0x9;    
    descIf.bDescriptorType=INTERFACE_TYPE;         
    descIf.bInterfaceNumber=0x0;
    descIf.bAlternateSetting=0x0; //?
    descIf.bNumEndpoints=2;	//# of endpoints except EP0
    descIf.bInterfaceClass=0xff; //0x0 ?
    descIf.bInterfaceSubClass=0x0;  
    descIf.bInterfaceProtocol=0x0;
    descIf.iInterface=0x0;

    //Standard endpoint0 descriptor
    descEndpt0.bLength=0x7;    
    descEndpt0.bDescriptorType=ENDPOINT_TYPE;         
    descEndpt0.bEndpointAddress=1|EP_ADDR_IN;   // 2400Xendpoint 1 is IN endpoint.
    descEndpt0.bmAttributes=EP_ATTR_BULK;
    descEndpt0.wMaxPacketSizeL=EP1_PKT_SIZE; //64
    descEndpt0.wMaxPacketSizeH=0x0;
    descEndpt0.bInterval=0x0; //not used

    //Standard endpoint1 descriptor
    descEndpt1.bLength=0x7;    
    descEndpt1.bDescriptorType=ENDPOINT_TYPE;         
    descEndpt1.bEndpointAddress=3|EP_ADDR_OUT;   // 2400X endpoint 3 is OUT endpoint.
    descEndpt1.bmAttributes=EP_ATTR_BULK;
    descEndpt1.wMaxPacketSizeL=EP3_PKT_SIZE; //64
    descEndpt1.wMaxPacketSizeH=0x0;
    descEndpt1.bInterval=0x0; //not used 
}

void usbInit()
{
	rGPHCON = rGPHCON&~(0xf<<18)|(0x5<<18);
	rGPGCON &= 0xfff3ffff;	//GPG9 input
	rUPLLCON = (40<<12) | (1<<4) | 2;
	InitDescriptorTable();
	ConfigUsbd();
	Delay(1000);
	rGPGCON |= 0x00040000;	
	rGPGDAT |= 0x0200;		//GPG9 ouput 1
	UsbState=0;//I don't know what is this variable for
	
}

void usbTest()
{
	u_char tempMem[16];
	u_short dnCS;    
	
	checkSum = 0;    
	downPt   = tempMem;	//This address is used for receiving first 8 byte.
	download_addr  =0; //_RAM_STARTADDRESS;
	download_len = 0;
	
	printf("Wait for USB connection\n\r");
	while(!isUSBSet);
    printf("USB Connected\n\r");
    while(download_len==0);
    
    printf("Now, Downloading [ADDRESS:%xh,TOTAL:%d]\n\r",download_addr, download_len);	

	
    //checkSum was calculated including dnCS. So, dnCS should be subtracted.
	printf("Calculating checksum\n\r");
	checkSum=checkSum - *((unsigned char *)(download_addr+download_len-8-2))- *( (unsigned char *)(download_addr+download_len-8-1));
	
	dnCS=*((unsigned char *)(download_addr+download_len-8-2))+(*((unsigned char *)(download_addr+download_len-8-1))<<8);

    if(checkSum!=dnCS)
    {
		printf("Error!!! MEM:%x DN:%x\n\r", checkSum, dnCS);
		return;
    }
	
	printf("CheckSum Ok\n\r");
	
}
