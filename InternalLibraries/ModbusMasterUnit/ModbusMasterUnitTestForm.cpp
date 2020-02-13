#include "ModbusMasterUnitTestForm.h"
#include "ui_ModbusMasterUnitTestForm.h"

//------------------------------------------------------------------------------------
//!
ModbusMasterUnitTestForm::ModbusMasterUnitTestForm(QWidget *parent)
                         :QWidget(parent),
                          ui(new Ui::ModbusMasterUnitTestForm)
{
    ui->setupUi(this);




}
//------------------------------------------------------------------------------------
//!
ModbusMasterUnitTestForm::~ModbusMasterUnitTestForm()
{
    delete ui;
}
//------------------------------------------------------------------------------------
//!
//------------------------------------------------------------------------------------
#ifdef __arm__
//------------------------------------------------------------------------------------
    #ifndef NATIVE_MODBUS_HANDLER
//------------------------------------------------------------------------------------
void ModbusMasterUnitTestForm::setup(const int baudRate,
                                     const uint8_t &slaveAddress,
                                     const int &functionCode,
                                     QList< std::tuple<int, QString, QString> > &registerList)
{
    ModbusMaster485 *m_mm485 = new ModbusMaster485(slaveAddress);

    m_mm485->begin(baudRate);

    // result = 0 : no errors
    // result = 1 : error occurred
    uint8_t result;

    uint16_t address;
    uint16_t quantity;

    uint16_t readAddress;
    uint16_t readQuantity;
    uint16_t writeAddress;
    uint16_t writeQuantity;

    switch (functionCode)
    {
        case 0x01: result = m_mm485->readCoils(address, quantity); break;
        case 0x02: result = m_mm485->readDiscreteInputs(address, quantity); break;
        case 0x03: result = m_mm485->readHoldingRegisters(address, quantity); break;
        case 0x04: result = m_mm485->readInputRegisters(address, quantity); break;
        case 0x05: result = m_mm485->writeSingleCoil(address, quantity); break;
        case 0x06: result = m_mm485->writeSingleRegister(address, quantity); break;
        case 0x0F: result = m_mm485->writeMultipleCoils(address, quantity); break;
        //case value: result = m_mm485->writeMultipleCoils(); break;
        case 0x10: result = m_mm485->writeMultipleRegisters(address, quantity); break;
        //case value: result = m_mm485->writeMultipleRegisters(); break;
        //case 0x16: result = m_mm485->maskWriteRegister(uint16_t, uint16_t, uint16_t); break;
        case 0x17: result = m_mm485->readWriteMultipleRegisters(readAddress, readQuantity, writeAddress, writeQuantity); break;
        //case 0x17: result = m_mm485->readWriteMultipleRegisters(address, quantity); break;

        default: break;
    }

    if (result != 0)
    {
        // If no response from the slave, print an error message
        SEND_TO_LOG(QString("Communication error. Couldn't read from temperature sensor"));
    } else {
        // If all OK
        SEND_TO_LOG(QString("read from slave [%1]: %2").arg(slaveAddress).arg(m_mm485->getResponseBuffer(0)));
    }

    // Clear the response buffer
    m_mm485->clearResponseBuffer();

    m_mm485->clearTransmitBuffer();
}
//------------------------------------------------------------------------------------
    #endif // !NATIVE_MODBUS_HANDLER
//------------------------------------------------------------------------------------
#endif // __arm__
//------------------------------------------------------------------------------------


