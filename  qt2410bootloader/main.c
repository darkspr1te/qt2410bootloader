#include <stdio.h>
#include "isr.h"
#include "sys.h"

extern void mmu_tlb_init(void);
extern void CleanMMUTable(void);
extern void StartMMU(unsigned int mmu_base);
extern void PortInit(void);
extern void InitIRQDevices(void);
extern void setupIRQEnv(void);
extern void Test_Adc(void);

int main(void)
{
 	char ch;
 	
 	PortInit();
 	CleanMMUTable();
 	mmu_tlb_init();
 	StartMMU(MMU_TABLE_BASE);
 	setupIRQEnv();
 	InitIRQDevices();		  		
 	printf("Joey Software-Reset bootloader Test\n\r");
 	//Test_Adc();
 	//Test_DMA();
 	//NAND FLASH TEST
 	NandFlashInit();	
	NANDFlashTest();
 	while (1)
  	{
 		scanf("%c",&ch);
 		printf("%c",ch);
  	}
}