#ifndef ModbusServer_h
#define ModbusServer_h

#include <Arduino.h>






/* Modbus function codes */
#define MODBUS_FC_READ_COILS                0x01
#define MODBUS_FC_READ_DISCRETE_INPUTS      0x02
#define MODBUS_FC_READ_HOLDING_REGISTERS    0x03
#define MODBUS_FC_READ_INPUT_REGISTERS      0x04
#define MODBUS_FC_WRITE_SINGLE_COIL         0x05
#define MODBUS_FC_WRITE_SINGLE_REGISTER     0x06
#define MODBUS_FC_READ_EXCEPTION_STATUS     0x07
#define MODBUS_FC_WRITE_MULTIPLE_COILS      0x0F
#define MODBUS_FC_WRITE_MULTIPLE_REGISTERS  0x10
#define MODBUS_FC_REPORT_SLAVE_ID           0x11
#define MODBUS_FC_MASK_WRITE_REGISTER       0x16
#define MODBUS_FC_WRITE_AND_READ_REGISTERS  0x17
#define MODBUS_FC_Interface                 0x2B







class modbus_server
{

    public:
        modbus_server(uint16_t address);
        ~modbus_server();

    
        void configureCoils(bool coils[], uint16_t numCoils);
        void configureDiscreteInputs(bool discreteInputs[], uint16_t numDiscreteInputs);
        void configureHoldingRegisters(uint16_t holdingRegisters[], uint16_t numHoldingRegisters);
        void configureInputRegisters(uint16_t inputRegisters[], uint16_t numInputRegisters);

        void  PDU(Stream & dataStream, uint8_t * PDU_buff,int PDU_length,int address);
        uint16_t bytes_2_Word(uint8_t high, uint8_t low) ;

    private:
    uint16_t _Modbus_Server_address=1;

        bool       *_coils;
        bool        *_discreteInputs;
        uint16_t *  _holdingRegisters;
        uint16_t *  _inputRegisters;
        uint16_t     _numCoils = 0;
        uint16_t    _numDiscreteInputs = 0;
        uint16_t    _numHoldingRegisters = 0;
        uint16_t    _numInputRegisters = 0;
        uint8_t _id;

        void _processReadCoils(uint8_t * PDU_buff );
        void _processReadDiscreteInputs(uint8_t * PDU_buff );
        void _processReadHoldingRegisters(uint8_t * PDU_buff );
        void _processReadInputRegisters(uint8_t * PDU_buff );
        void _processWriteSingleCoil(uint8_t * PDU_buff );
        void _processWriteSingleHoldingRegister(uint8_t * PDU_buff );
        void _processWriteMultipleCoils(uint8_t * PDU_buff );
        void _processWriteMultipleHoldingRegisters(uint8_t * PDU_buff );
        void _process_RW_Interface(uint8_t * PDU_buff);

        void _exceptionResponse(uint8_t code,uint8_t * PDU_buff);
        void _Header(uint8_t * PDU_buff, uint16_t & startAddress, uint16_t & quantity) ;
        uint16_t _div8RndUp(uint16_t value);



};







  

  #endif
