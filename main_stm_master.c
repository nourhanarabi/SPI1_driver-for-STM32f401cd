#include"header_file.h"

void main() {

uint8_t SendData =0;
uint8_t ReceiveData =0;



      Init_SPI();    //initial conditions for SPI1
      

      
      while(1)
      {
             SPI_Begin();  //Enable SPI1 Bus
             
              SPI_BeginTransaction(MSBFIRST, BITS_8, SPI_DIV16, SPI_MODE0);
              
              //SEND DATA
              SendData = 0x00;
              SPI_SendData(&SendData);
              DELAY_MS(3000);
              
              
              SendData = 0x01;
              SPI_SendData(&SendData);
              DELAY_MS(3000);

              
              //RECIEVE DATA
             // SPI_RecieveData(&ReceiveData);
              
              SPI_EndTransaction();
              SPI_End();               //disable SPI1 BUS

}
}
