#include"Header_Slave.h"

void main() {

uint8_t SendData =0;
uint8_t ReceiveData =0;


       RCC_AHB1ENR |= (1<<1)  ;       //enable clock port B
       GPIOB_MODER  = 0x55555555;     //enable Port B as OUTPUT
      Init_SPI();    //initial conditions for SPI1



      while(1)
      {
             SPI_Begin();  //Enable SPI1 Bus

              SPI_BeginTransaction(MSBFIRST, BITS_8, SPI_DIV16, SPI_MODE0);

              //Receive DATA
                 SPI_RecieveData(&ReceiveData);
                 GPIOB_ODR |= (ReceiveData <<2) ;      //show data on portB pin 2
                 
                 SPI_EndTransaction();
                 SPI_End();               //disable SPI1 BUS

}
}