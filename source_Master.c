#include"Header_Master.h"

          /*
            **Description:
               * This function used first to implement the intial condition for SPI1
            **Parameters:
               * No parameters used in this function
            **Return Value:
               * No Returned Value 
          */
void Init_SPI (void)
{
   RCC_AHB1ENR |= (1<<0)  ;       //enable clock port A
   Rcc_APB2ENR |= (1<<12) ;        //enable clock SPI1

   GPIOA_MODER &= ~ ((3 <<(2*4))             //Reset pin4
                    |(3<<(2*5))              //Reset pin5
                    |(3<<(2*6))              //Reset pin6
                    |(3<<(2*7)));            //Reset pin7


   GPIOA_MODER |=   ((2 <<(2*4))             //Enable AF
                    |(2<<(2*5))              //Enable AF
                    |(2<<(2*6))              //Enable AF
                    |(2<<(2*7)));            //Enable AF


  GPIOA_AFRL &= ~ ((15<<(4*4))
                  |(15<<(4*5))
                  |(15<<(4*6))
                  |(15<<(4*7)));             //clear Af

  GPIOA_AFRL |=  ((5<<(4*4))        //SS
                 |(5<<(4*5))        //SCLK
                 |(5<<(4*6))        //MISO
                 |(5<<(4*7)));     // MOSI     --->Af5 for SPI1
                 
  SPI1_CR1 =0;                       //SET CR1

   SPI1_CR1 &= ~ (1<<10);           //FULL_DUBLEX MODE

   SPI1_CR1 |= (1<<2) ;              //Master mode

   SPI1_CR1 |= (1<<9);               // software slave management

   SPI1_CR1 &= ~ (1<<15);            // 2-line unidirectional data mode selected

   SPI1_CR2 =0;                      //Reset CR2

}


       /*
            **Description:
               * This function used to select the first bit will transfer (MSB)or (LSB)
            **Parameters:
               * (byteOrder)----> is the parameter used 
            **Return Value:
               * No Returned Value 
          */
void SPI_SetBitOrder(uint8_t byteOrder)
{
   if( byteOrder ==MSBFIRST)
{

   SPI1_CR1 &= ~(1<< 7);
}

else if(byteOrder ==LSBFIRST)
{
  SPI1_CR1 |= (1<<7);
}
}

       /*
            **Description:
               * This function used to select the desired data mode and the clock mode
            **Parameters:
               * (mode)----> is the parameter used for data mode transfer (8_bits) or (16_bits) 
	       * (clockMode)-----> is the second to select the clock mode desired 
            **Return Value:
               * No Returned Value 
          */

void setDataMode(uint8_t mode, uint8_t clockMode) {
//SELECT DATA MODE

if (mode ==BITS_8)
{
    SPI1_CR1 &= ~(1<<11);

}

else if(mode ==BITS_16)
{
    SPI1_CR1 |=(1<<11);

}

// SELECT CLOCK MODE
switch (clockMode)
{
   case SPI_MODE0:
        SPI1_CR1 &= ~(1<<1) ;            //clock polarity CPOL =0
        SPI1_CR1 &= ~ (1<<0);           //clock Phase   CPHA =0
        break;

  case SPI_MODE1:
       SPI1_CR1  &= ~ (1<<1) ;           //CPOL=0
       SPI1_CR1  |=(1<<0);               // CPHA=1
        break;

  case SPI_MODE2:
       SPI1_CR1  |= (1<<1) ;            //CPOL=1
       SPI1_CR1  &= ~(1<<0) ;            // CPHA=0
       break;

 case SPI_MODE3:
       SPI1_CR1  |= (1<<1)   ;           //CPOL=1
       SPI1_CR1  |= (1<<0)    ;          // CPHA=1
       break;
}
}
        /*
            **Description:
               * This function used to select the desired frequency divider 
            **Parameters:
               * (freqDivider)----> is the parameter used for choosing the frequency divider desired 
            **Return Value:
               * No Returned Value 
          */
void setClockDivider(uint8_t freqDivider) {

// Clear previous divider value
    SPI1_CR1 &= ~(1<<3);

switch(freqDivider)
{
  case SPI_DIV2:
    SPI1_CR1 |= (0<<3);
    break;

 case SPI_DIV4:
    SPI1_CR1 |= (1<<3);
    break;

 case SPI_DIV8:
    SPI1_CR1 |= (2<<3);
    break;

 case SPI_DIV16:
    SPI1_CR1 |= (3<<3);
    break;

 case SPI_DIV32:
    SPI1_CR1 |= (4<<3);
    break;

 case SPI_DIV64:
    SPI1_CR1 |= (5<<3);
    break;

 case SPI_DIV128:
    SPI1_CR1 |= (6<<3);
    break;


case SPI_DIV256:
    SPI1_CR1 |= (7<<3);
    break;

}
}
         /*
            **Description:
               * This function used to disable SPI1 Bus
            **Parameters:
               * No parameter required
            **Return Value:
               * No Returned Value 
          */

void SPI_End(void)
{
   SPI1_CR1 &= ~(1<<6);    //disable SPI   --->SBE = 0

}

        /*
            **Description:
               * This function used to enable SPI1 Bus
            **Parameters:
               * No parameter required
            **Return Value:
               * No Returned Value 
          */


void SPI_Begin(void)
{
   SPI1_CR1 |= (1<<6);    //Enable SPI   --->SBE = 1

}

         /*
            **Description:
               * This function used to send data from master to slave
            **Parameters:
               * (DataTransfered)--> is the adrress of data wanted to be sended to slave 
            **Return Value:
               * No Returned Value 
          */


void SPI_SendData(uint8_t *DataTransfered)
{
     //for Send DATA
	SPI1_DR = *DataTransfered;
	while(!(SPI1_SR&(1<<1)));
}

         /*
            **Description:
               * This function used to receive data from slave to master
            **Parameters:
               * (DataTransfered)--> is the adrress of data wanted to be received from master 
            **Return Value:
               * No Returned Value 
          */

void SPI_RecieveData (uint8_t *DataTransfered)
{
        //For Recieve DATA
         while(!(SPI1_SR&(1<<0)));
	*DataTransfered = SPI1_DR;

}

         /*
            **Description:
               * This function include (setDataMode),(setClockDivider)and(SPI_SetBitOrder)
	         like a setting function 
            **Parameters:
                * (byteOrder)----> is the parameter used 
		*(dataMode)-----> paramter of (setDataMode) function
                *(clockMode)----->the second paramter of (setDataMode) function
		*(baudRate)----->the parameter of (setClockDivider) function
            **Return Value:
               * No Returned Value 
          */

void SPI_BeginTransaction(uint8_t byteOrder, uint8_t dataMode, uint8_t baudRate, uint8_t clockMode)
{

   setDataMode(dataMode,clockMode);
   setClockDivider(baudRate);
   SPI_SetBitOrder(byteOrder);

}

        /*
            **Description:
               * This function is empty to end 
            **Parameters:
               * No parameter required
            **Return Value:
               * No Returned Value 
          */



void SPI_EndTransaction(void)
{
   //nothing done in thiss function
}
