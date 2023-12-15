#ifndef ModbusServerTCP_h
#define ModbusServerTCP_h
#include <Arduino.h>


#include "modbus_server.h"


//TCP 
// MBAP + PDU
//MBAP header (Modbus Application Header) for the TCP
struct MBAP{
    uint16 Trasaction_ID =0;
    uint16 Protocol_ID =0;
    uint16 Message_Length =0;
    uint8  Server_Address =0;  
};

modbus_tcp(stream & dataStream,modbus_server & server)
{
MBAP header;
uint16_t high=0;uint16_t low=0;
high = dataStream.read();
low = dataStream.read();
header.Trasaction = high<<8 | low;
high = dataStream.read();
low = dataStream.read();
header.Protocol_ID = high<<8 | low;
high = dataStream.read();
low = dataStream.read();
header.Message_Length = high<<8 | low;
header.Server_Address = dataStream.read();
uint8_t PDU_buff[header.Message_Length];
for(int i; i<header.Message_Length;i++)
PDU_buff[i]=dataStream.read();

modbus_server.PDU(dataStream,PDU_buff,header.Server_Address);
}



#endif