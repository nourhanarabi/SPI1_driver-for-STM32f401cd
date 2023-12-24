 #ifndef SPI_H_
#define SPI_H_

#include<stdint.h>

#define MSBFIRST        0
#define LSBFIRST        1

#define BITS_8        0
#define BITS_16       1

#define SPI_MODE0       0
#define SPI_MODE1       1
#define SPI_MODE2       2
#define SPI_MODE3       3

#define SPI_DIV2        0
#define SPI_DIV4        1
#define SPI_DIV8        2
#define SPI_DIV16       3
#define SPI_DIV32       4
#define SPI_DIV64       5
#define SPI_DIV128      6
#define SPI_DIV256      7


void Init_SPI (void);
void setDataMode(uint8_t mode, uint8_t clockMode);
void setClockDivider(uint8_t freqDivider);
void SPI_SetBitOrder(uint8_t byteOrder);
void SPI_End(void);
void SPI_Begin(void);
void SPI_BeginTransaction(uint8_t byteOrder, uint8_t dataMode, uint8_t baudRate, uint8_t clockMode);
void SPI_EndTransaction(void);
void SPI_SendData(uint8_t *DataTransfered);
void SPI_RecieveData(uint8_t *DataTransfered);



#endif