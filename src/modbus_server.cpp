



#include "modbus_server.h"


modbus_server::modbus_server(uint16_t address)
{
  _Modbus_Server_address=address;
}

void modbus_server::configureCoils(bool coils[], uint16_t numCoils) {
  _coils = coils;
  _numCoils = numCoils;
}

void modbus_server::configureDiscreteInputs(bool discreteInputs[], uint16_t numDiscreteInputs) {
  _discreteInputs = discreteInputs;
  _numDiscreteInputs = numDiscreteInputs;
}

void modbus_server::configureHoldingRegisters(uint16_t holdingRegisters[], uint16_t numHoldingRegisters) {
  _holdingRegisters = holdingRegisters;
  _numHoldingRegisters = numHoldingRegisters;
}

void modbus_server::configureInputRegisters(uint16_t inputRegisters[], uint16_t numInputRegisters) {
  _inputRegisters = inputRegisters;
  _numInputRegisters = numInputRegisters;
}

void modbus_server::PDU(Stream & dataStream,uint8_t * PDU_buff,int  PDU_length, int address)
{
    if(address != _Modbus_Server_address) return; // should write error code to stream.

      switch (PDU_buff[0]) {
        case MODBUS_FC_READ_COILS:
          _processReadCoils(PDU_buff);
          break;
        case MODBUS_FC_READ_DISCRETE_INPUTS:
          _processReadDiscreteInputs(PDU_buff);
          break;
        case MODBUS_FC_READ_HOLDING_REGISTERS:
          _processReadHoldingRegisters(PDU_buff);
          break;
        case MODBUS_FC_READ_INPUT_REGISTERS:
          _processReadInputRegisters(PDU_buff);
          break;
        case MODBUS_FC_WRITE_SINGLE_COIL:
          _processWriteSingleCoil(PDU_buff);
          break;
        case MODBUS_FC_WRITE_SINGLE_REGISTER:
          _processWriteSingleHoldingRegister(PDU_buff);
          break;
        case MODBUS_FC_WRITE_MULTIPLE_COILS:
          _processWriteMultipleCoils(PDU_buff);
          break;
        case MODBUS_FC_WRITE_MULTIPLE_REGISTERS:
          _processWriteMultipleHoldingRegisters(PDU_buff);
          break;
        case MODBUS_FC_Interface:
          _process_RW_Interface(PDU_buff);
          break;
        default:
          _exceptionResponse(1,PDU_buff);
          break;
      }
}




void modbus_server::_exceptionResponse(uint8_t code,uint8_t * PDU_buff) {
  PDU_buff[0] |= 0x80;
  PDU_buff[1] = code;
  //_writeResponse(3);
}





/// @brief _processReadCoils//////////
/// @param PDU_buff ///
void modbus_server::_processReadCoils(uint8_t * PDU_buff) {
 // uint16_t startAddress = bytes_2_Word(PDU_buff[1], PDU_buff[2]);
 // uint16_t quantity = bytes_2_Word(PDU_buff[3], PDU_buff[4]);
  uint16_t startAddress,quantity;
   _Header(PDU_buff, startAddress, quantity);
  if (!_coils || _numCoils == 0) _exceptionResponse(1,PDU_buff);
  else if (quantity == 0 || quantity > 2000) _exceptionResponse(3,PDU_buff);
  else if (quantity > _numCoils || startAddress > (_numCoils - quantity)) _exceptionResponse(2,PDU_buff);
  else {
    PDU_buff[1] = _div8RndUp(quantity);
    for (uint16_t i = 0; i < quantity; i++) {
      bitWrite(PDU_buff[2 + (i >> 3)], i & 7, _coils[startAddress + i]);
    }
    //_writeResponse(3 + PDU_buff[1],PDU_buff);
  }
}

void modbus_server::_processReadDiscreteInputs(uint8_t * PDU_buff ) {
 // uint16_t startAddress = bytes_2_Word(PDU_buff[2], PDU_buff[3]);
 // uint16_t quantity = bytes_2_Word(PDU_buff[4], PDU_buff[5]);
   uint16_t startAddress,quantity;
   _Header(PDU_buff, startAddress, quantity);
  if (!_discreteInputs || _numDiscreteInputs == 0) _exceptionResponse(1,PDU_buff);
  else if (quantity == 0 || quantity > 2000) _exceptionResponse(3,PDU_buff);
  else if (quantity > _numDiscreteInputs || startAddress > (_numDiscreteInputs - quantity)) _exceptionResponse(2,PDU_buff);
  else {
    PDU_buff[2] = _div8RndUp(quantity);
    for (uint16_t i = 0; i < quantity; i++) {
      bitWrite(PDU_buff[3 + (i >> 3)], i & 7, _discreteInputs[startAddress + i]);
    }
    //_writeResponse(3 + _buf[2]);
  }
}

void modbus_server::_processReadHoldingRegisters(uint8_t * PDU_buff ) {
 // uint16_t startAddress = bytes_2_Word(_buf[2], _buf[3]);
 // uint16_t quantity = bytes_2_Word(_buf[4], _buf[5]);
   uint16_t startAddress,quantity;
   _Header(PDU_buff, startAddress, quantity);
  if (!_holdingRegisters || _numHoldingRegisters == 0) _exceptionResponse(1,PDU_buff);
  else if (quantity == 0 || quantity > 125) _exceptionResponse(3,PDU_buff);
  else if (quantity > _numHoldingRegisters || startAddress > (_numHoldingRegisters - quantity)) _exceptionResponse(2,PDU_buff);
  else {
    PDU_buff[2] = quantity * 2;
    for (uint16_t i = 0; i < quantity; i++) {
      PDU_buff[3 + (i * 2)] = highByte(_holdingRegisters[startAddress + i]);
      PDU_buff[4 + (i * 2)] = lowByte(_holdingRegisters[startAddress + i]);
    }
    //_writeResponse(3 + _buf[2]);
  }
}

void modbus_server::_processReadInputRegisters(uint8_t * PDU_buff ) {
 // uint16_t startAddress = bytes_2_Word(_buf[2], _buf[3]);
 // uint16_t quantity = bytes_2_Word(_buf[4], _buf[5]);
  uint16_t startAddress,quantity;
   _Header(PDU_buff, startAddress, quantity);
  if (!_inputRegisters || _numInputRegisters == 0) _exceptionResponse(1,PDU_buff);
  else if (quantity == 0 || quantity > 125) _exceptionResponse(3,PDU_buff);
  else if (quantity > _numInputRegisters || startAddress > (_numInputRegisters - quantity)) _exceptionResponse(2,PDU_buff);
  else {
    PDU_buff[2] = quantity * 2;
    for (uint16_t i = 0; i < quantity; i++) {
      PDU_buff[3 + (i * 2)] = highByte(_inputRegisters[startAddress + i]);
      PDU_buff[4 + (i * 2)] = lowByte(_inputRegisters[startAddress + i]);
    }
    //_writeResponse(3 + _buf[2]);
  }
}

void modbus_server::_processWriteSingleCoil(uint8_t * PDU_buff ) {
 // uint16_t address = bytes_2_Word(_buf[2], _buf[3]);
 // uint16_t value = bytes_2_Word(_buf[4], _buf[5]);
  uint16_t address,value;
   _Header(PDU_buff, address, value);
  if (!_coils ||_numCoils == 0) _exceptionResponse(1,PDU_buff);
  else if (value != 0 && value != 0xFF00) _exceptionResponse(3,PDU_buff);
  else if (address >= _numCoils) _exceptionResponse(2,PDU_buff);
  else {
    _coils[address] = value;
   // _writeResponse(6);
  }
}

void modbus_server::_processWriteSingleHoldingRegister(uint8_t * PDU_buff ) {
 // uint16_t address = bytes_2_Word(_buf[2], _buf[3]);
 // uint16_t value = bytes_2_Word(_buf[4], PDU_buff[5]);
  uint16_t address,value;
   _Header(PDU_buff, address, value);
  if (!_holdingRegisters || _numHoldingRegisters == 0) _exceptionResponse(1,PDU_buff);
  else if (address >= _numHoldingRegisters) _exceptionResponse(2,PDU_buff);
  else {
    _holdingRegisters[address] = value;
   // _writeResponse(6);
  }
}

void modbus_server::_processWriteMultipleCoils(uint8_t * PDU_buff ) {
  //uint16_t startAddress = bytes_2_Word(_buf[2], _buf[3]);
  //uint16_t quantity = bytes_2_Word(_buf[4], _buf[5]);
   uint16_t startAddress,quantity;
   _Header(PDU_buff, startAddress, quantity);
  if (!_coils || _numCoils == 0) _exceptionResponse(1,PDU_buff);
  else if (quantity == 0 || quantity > 1968 || PDU_buff[6] != _div8RndUp(quantity)) _exceptionResponse(3,PDU_buff);
  else if (quantity > _numCoils || startAddress > (_numCoils - quantity)) _exceptionResponse(2,PDU_buff);
  else {
    for (uint16_t i = 0; i < quantity; i++) {
      _coils[startAddress + i] = bitRead(PDU_buff[7 + (i >> 3)], i & 7);
    }
   // _writeResponse(6);
  }
}

void modbus_server::_processWriteMultipleHoldingRegisters(uint8_t * PDU_buff ) {
  //uint16_t startAddress = bytes_2_Word(_buf[2], _buf[3]);
  //uint16_t quantity = bytes_2_Word(_buf[4], _buf[5]);
   uint16_t startAddress,quantity;
   _Header(PDU_buff, startAddress, quantity);
  if (!_holdingRegisters || _numHoldingRegisters == 0) _exceptionResponse(1,PDU_buff);
  else if (quantity == 0 || quantity > 123 || PDU_buff[6] != (quantity * 2)) _exceptionResponse(3,PDU_buff);
  else if (quantity > _numHoldingRegisters || startAddress > (_numHoldingRegisters - quantity)) _exceptionResponse(2,PDU_buff);
  else {
    for (uint16_t i = 0; i < quantity; i++) {
      _holdingRegisters[startAddress + i] = bytes_2_Word(PDU_buff[i * 2 + 7], PDU_buff[i * 2 + 8]);
    }
   // _writeResponse(6);
  }
}

void modbus_server::_process_RW_Interface(uint8_t * PDU_buff )
{
    switch (PDU_buff[1]){

        case  0x0E:  // Read device identification
        break;
         case 0x0F:  //0x10  //Get Date and Time
          //
          break;
        case 0x10:  //0x10  //Set Date and Time
          //Time object
          break;
        default:
          _exceptionResponse(1,PDU_buff);
          break;
    }

}

void modbus_server::_Header(uint8_t * PDU_buff, uint16_t & startAddress, uint16_t & quantity) {
    startAddress = bytes_2_Word(PDU_buff[2], PDU_buff[3]);
    quantity = bytes_2_Word(PDU_buff[4], PDU_buff[5]);
}

uint16_t modbus_server::bytes_2_Word(uint8_t high, uint8_t low) {
  return ((uint16_t)high << 8) | low;
}

uint16_t modbus_server::_div8RndUp(uint16_t value) {
  return (value + 7) >> 3;
}
