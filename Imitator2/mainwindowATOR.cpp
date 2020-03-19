/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the QtSerialBus module.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindowATOR.h"
#include "ui_mainwindowATOR.h"

#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QStatusBar>
#include <QUrl>

enum ModbusConnection {
    Serial,
    Tcp
};

MainWindowATOR::MainWindowATOR(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowATOR)
{
    ui->setupUi(this);

#if (defined (_WIN32) || defined (_WIN64))
    //ui->portEdit->setText("\\\\.\\COM5");
#else
    ui->portEdit->setText("/dev/ttyUSB1");
#endif

    // Modbus virtual network creation
    modnet = new ModbusNetwork(this);

    connect(modnet, &ModbusNetwork::logPrint, this, &MainWindowATOR::logPring);

    // Connection button config
    connect(ui->connectButton, &QPushButton::released,
            this, &MainWindowATOR::onConnectionRelease);

    setupWidgetContainers();

//#if QT_CONFIG(modbus_serialport)
    ui->connectType->setCurrentIndex(0);
    //onCurrentConnectTypeChanged(0);
//#else
//    // lock out the serial port option
//    ui->connectType->setCurrentIndex(1);
//    onCurrentConnectTypeChanged(1);
//    ui->connectType->setEnabled(false);
//#endif

    //m_settingsDialog = new SettingsDialog(this);
    initActions();
    initVVODigIn();
    initVVODigOut();
}

MainWindowATOR::~MainWindowATOR()
{/*
    if (modbusDevice)
        modbusDevice->disconnectDevice();
    delete modbusDevice;*/
    delete modnet;

    delete ui;
}

void MainWindowATOR::onConnectionRelease()
{
    if (modnet->isConnected())
    {
        modnet->closeConnection();

        ui->connectButton->setText("Connect");
        //logPring("OK: Device is disconnected");
        statusBar()->showMessage("OK: Device is disconnected");
    }
    else
    {
        serial_config_t sp_config;

        //sp_config.portName = ui->cbPortName->currentText();
        //sp_config.baudrate = ui->cbBaubrate->currentText().toInt();
        //sp_config.dataBits = ui->cbDataBits->currentText().toInt();
        //sp_config.stopBits = ui->cbStopBits->currentText().toInt();
        //sp_config.parity = ui->cbParity->currentText();
        sp_config.portName = ui->portEdit->text();
        sp_config.baudrate = 9600;
        sp_config.dataBits = 8;
        sp_config.stopBits = 1;
        sp_config.parity = "None";

        modnet->init(sp_config);
        modnet->openConnection();

        ui->connectButton->setText("Disconnect");
        //logPring("OK: Device is connected");
        statusBar()->showMessage("OK: Device is connected");
    }
}

void MainWindowATOR::initActions()
{
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionExit->setEnabled(true);
    ui->actionOptions->setEnabled(true);

//    connect(ui->connectButton, &QPushButton::clicked,
//            this, &MainWindowATOR::onConnectButtonClicked);
//    connect(ui->actionConnect, &QAction::triggered,
//            this, &MainWindowATOR::onConnectButtonClicked);
//    connect(ui->actionDisconnect, &QAction::triggered,
//            this, &MainWindowATOR::onConnectButtonClicked);
//    connect(ui->connectType, QOverload<int>::of(&QComboBox::currentIndexChanged),
//            this, &MainWindowATOR::onCurrentConnectTypeChanged);

    connect(ui->actionExit, &QAction::triggered, this, &QMainWindow::close);
    //connect(ui->actionOptions, &QAction::triggered, m_settingsDialog, &QDialog::show);
}

void MainWindowATOR::initVVODigIn()
{
    connect(ui->inReg_8_0, &QLineEdit::textChanged,
            this,        &MainWindowATOR::onVVODigIn);

    connect(ui->cbU3000, &QAbstractButton::clicked,
            this,        &MainWindowATOR::onVVOReg0);
    connect(ui->cbVVO_1, &QAbstractButton::clicked,
            this,        &MainWindowATOR::onVVOReg0);
    connect(ui->cbVVO_2, &QAbstractButton::clicked,
            this,        &MainWindowATOR::onVVOReg0);
    connect(ui->cbNVO, &QAbstractButton::clicked,
            this,        &MainWindowATOR::onVVOReg0);
    connect(ui->cbGen, &QAbstractButton::clicked,
            this,        &MainWindowATOR::onVVOReg0);
    connect(ui->cbAuto, &QAbstractButton::clicked,
            this,        &MainWindowATOR::onVVOReg0);
    connect(ui->cbCrash, &QAbstractButton::clicked,
            this,        &MainWindowATOR::onVVOReg0);
    connect(ui->cbEO, &QAbstractButton::clicked,
            this,        &MainWindowATOR::onVVOReg0);
    connect(ui->cbCondF, &QAbstractButton::clicked,
            this,        &MainWindowATOR::onVVOReg0);
    connect(ui->cbCont2F, &QAbstractButton::clicked,
            this,        &MainWindowATOR::onVVOReg0);
    connect(ui->cbCont1F, &QAbstractButton::clicked,
            this,        &MainWindowATOR::onVVOReg0);
    connect(ui->cbCondW, &QAbstractButton::clicked,
            this,        &MainWindowATOR::onVVOReg0);
    connect(ui->cbCooling, &QAbstractButton::clicked,
            this,        &MainWindowATOR::onVVOReg0);
    connect(ui->cbHeater, &QAbstractButton::clicked,
            this,        &MainWindowATOR::onVVOReg0);
    connect(ui->cbUmax_zrk, &QAbstractButton::clicked,
            this,        &MainWindowATOR::onVVOReg0);
    connect(ui->cbRizol, &QAbstractButton::clicked,
            this,        &MainWindowATOR::onVVOReg0);
}

void MainWindowATOR::onVVODigIn(const QString &text)
{
    ui->cbU3000->setChecked(    text.toInt() & 0x0001 );
    ui->cbVVO_1->setChecked(    text.toInt() & 0x0002 );
    ui->cbVVO_2->setChecked(    text.toInt() & 0x0004 );
    ui->cbNVO->setChecked(      text.toInt() & 0x0008 );
    ui->cbGen->setChecked(      text.toInt() & 0x0010 );
    ui->cbAuto->setChecked(     text.toInt() & 0x0020 );
    ui->cbCrash->setChecked(    text.toInt() & 0x0040 );
    ui->cbEO->setChecked(       text.toInt() & 0x0080 );
    ui->cbCondF->setChecked(    text.toInt() & 0x0100 );
    ui->cbCont2F->setChecked(   text.toInt() & 0x0200 );
    ui->cbCont1F->setChecked(   text.toInt() & 0x0400 );
    ui->cbCondW->setChecked(    text.toInt() & 0x0800 );
    ui->cbCooling->setChecked(  text.toInt() & 0x1000 );
    ui->cbHeater->setChecked(   text.toInt() & 0x2000 );
    ui->cbUmax_zrk->setChecked( text.toInt() & 0x4000 );
    ui->cbRizol->setChecked(    text.toInt() & 0x8000 );
}

void MainWindowATOR::onVVOReg0()
{
    unsigned u = 0;
    u |= ui->cbU3000->isChecked()    ? 0x0001 : 0 ;
    u |= ui->cbVVO_1->isChecked()    ? 0x0002 : 0 ;
    u |= ui->cbVVO_2->isChecked()    ? 0x0004 : 0 ;
    u |= ui->cbNVO->isChecked()      ? 0x0008 : 0 ;
    u |= ui->cbGen->isChecked()      ? 0x0010 : 0 ;
    u |= ui->cbAuto->isChecked()     ? 0x0020 : 0 ;
    u |= ui->cbCrash->isChecked()    ? 0x0040 : 0 ;
    u |= ui->cbEO->isChecked()       ? 0x0080 : 0 ;
    u |= ui->cbCondF->isChecked()    ? 0x0100 : 0 ;
    u |= ui->cbCont2F->isChecked()   ? 0x0200 : 0 ;
    u |= ui->cbCont1F->isChecked()   ? 0x0400 : 0 ;
    u |= ui->cbCondW->isChecked()    ? 0x0800 : 0 ;
    u |= ui->cbCooling->isChecked()  ? 0x1000 : 0 ;
    u |= ui->cbHeater->isChecked()   ? 0x2000 : 0 ;
    u |= ui->cbUmax_zrk->isChecked() ? 0x4000 : 0 ;
    u |= ui->cbRizol->isChecked()    ? 0x8000 : 0 ;

    ui->inReg_8_0->setText(QString("%1").arg( u ));
}

void MainWindowATOR::initVVODigOut()
{
    connect(ui->holdReg_8_0, &QLineEdit::textChanged,
            this,          &MainWindowATOR::onVVODigOut);
}

void MainWindowATOR::onVVODigOut(const QString &text)
{
    ui->cbVvo1On->setChecked(   text.toInt() & 0x0001 );
    ui->cbVvo2On->setChecked(   text.toInt() & 0x0002 );
    ui->cbPompOn->setChecked(   text.toInt() & 0x0004 );
    ui->cbNvoOn->setChecked(    text.toInt() & 0x0008 );
    ui->cbFaultOn->setChecked(  text.toInt() & 0x0010 );
    ui->cbBpOn->setChecked(     text.toInt() & 0x0020 );
    ui->cbPvvOn->setChecked(    text.toInt() & 0x0400 );

    //Формирование отклика
    if (ui->cbRespNVO->isChecked())
    {
        if ( ui->cbNVO->isChecked() != ui->cbNvoOn->isChecked() )
        {
            ui->cbNVO->setChecked( ui->cbNvoOn->isChecked() );
            onVVOReg0();
        }
    }
    if (ui->cbRespVVO1->isChecked())
    {
        if ( ui->cbVVO_1->isChecked() != ui->cbVvo1On->isChecked() )
        {
            ui->cbVVO_1->setChecked( ui->cbVvo1On->isChecked() );
            onVVOReg0();
        }

    }
    if (ui->cbRespVVO2->isChecked())
    {
        if ( ui->cbVVO_2->isChecked() != ui->cbVvo2On->isChecked() )
        {
            ui->cbVVO_2->setChecked( ui->cbVvo2On->isChecked() );
            onVVOReg0();
        }
    }

}
/*
void MainWindowATOR::onCurrentConnectTypeChanged(int index)
{
    if (modbusDevice) {
        modbusDevice->disconnect();
        delete modbusDevice;
        modbusDevice = nullptr;
    }

    auto type = static_cast<ModbusConnection>(index);
    if (type == Serial) {
//#if QT_CONFIG(modbus_serialport)
        modbusDevice = new QModbusRtuSerialSlave(this);
//#endif
    } else if (type == Tcp) {
        modbusDevice = new QModbusTcpServer(this);
        if (ui->portEdit->text().isEmpty())
            ui->portEdit->setText(QLatin1String("127.0.0.1:502"));
    }
    ui->listenOnlyBox->setEnabled(type == Serial);

    if (!modbusDevice) {
        ui->connectButton->setDisabled(true);
        if (type == Serial)
            statusBar()->showMessage(tr("Could not create Modbus slave."), 5000);
        else
            statusBar()->showMessage(tr("Could not create Modbus server."), 5000);
    } else {
        QModbusDataUnitMap reg;

        reg.insert(QModbusDataUnit::InputRegisters,     { QModbusDataUnit::InputRegisters,      0, 50 });
        reg.insert(QModbusDataUnit::HoldingRegisters,   { QModbusDataUnit::HoldingRegisters,    0, 50 });

        modbusDevice->setMap(reg);

        connect(modbusDevice, &QModbusServer::dataWritten,
                this, &MainWindowATOR::updateWidgets);
        connect(modbusDevice, &QModbusServer::stateChanged,
                this, &MainWindowATOR::onStateChanged);
        connect(modbusDevice, &QModbusServer::errorOccurred,
                this, &MainWindowATOR::handleDeviceError);

        connect(ui->listenOnlyBox, &QCheckBox::toggled, this, [this](bool toggled) {
            if (modbusDevice)
                modbusDevice->setValue(QModbusServer::ListenOnlyMode, toggled);
        });
        emit ui->listenOnlyBox->toggled(ui->listenOnlyBox->isChecked());
        //connect(ui->setBusyBox, &QCheckBox::toggled, this, [this](bool toggled) {
        //    if (modbusDevice)
        //        modbusDevice->setValue(QModbusServer::DeviceBusy, toggled ? 0xffff : 0x0000);
        //});
        //emit ui->setBusyBox->toggled(ui->setBusyBox->isChecked());

        setupDeviceData();
    }
}

void MainWindowATOR::handleDeviceError(QModbusDevice::Error newError)
{
    if (newError == QModbusDevice::NoError || !modbusDevice)
        return;

    statusBar()->showMessage(modbusDevice->errorString(), 5000);
}

void MainWindowATOR::onConnectButtonClicked()
{
    bool intendToConnect = (modbusDevice->state() == QModbusDevice::UnconnectedState);

    statusBar()->clearMessage();

    if (intendToConnect) {
        if (static_cast<ModbusConnection>(ui->connectType->currentIndex()) == Serial) {
            modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,
                ui->portEdit->text());
//#if QT_CONFIG(modbus_serialport)
            modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,
                m_settingsDialog->settings().parity);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,
                m_settingsDialog->settings().baud);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,
                m_settingsDialog->settings().dataBits);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,
                m_settingsDialog->settings().stopBits);
//#endif
        } else {
            const QUrl url = QUrl::fromUserInput(ui->portEdit->text());
            modbusDevice->setConnectionParameter(QModbusDevice::NetworkPortParameter, url.port());
            modbusDevice->setConnectionParameter(QModbusDevice::NetworkAddressParameter, url.host());
        }
        modbusDevice->setServerAddress(ui->serverEdit->text().toInt());
        if (!modbusDevice->connectDevice()) {
            statusBar()->showMessage(tr("Connect failed: ") + modbusDevice->errorString(), 5000);
        } else {
            ui->actionConnect->setEnabled(false);
            ui->actionDisconnect->setEnabled(true);
        }
    } else {
        modbusDevice->disconnectDevice();
        ui->actionConnect->setEnabled(true);
        ui->actionDisconnect->setEnabled(false);
    }
}

void MainWindowATOR::onStateChanged(int state)
{
    bool connected = (state != QModbusDevice::UnconnectedState);
    ui->actionConnect->setEnabled(!connected);
    ui->actionDisconnect->setEnabled(connected);

    if (state == QModbusDevice::UnconnectedState)
        ui->connectButton->setText(tr("Connect"));
    else if (state == QModbusDevice::ConnectedState)
        ui->connectButton->setText(tr("Disconnect"));
}

void MainWindowATOR::coilChanged(int id)
{
    //QAbstractButton *button = coilButtons.button(id);
    //bitChanged(id, QModbusDataUnit::Coils, button->isChecked());
}

void MainWindowATOR::discreteInputChanged(int id)
{
    //QAbstractButton *button = discreteButtons.button(id);
    //bitChanged(id, QModbusDataUnit::DiscreteInputs, button->isChecked());
}

void MainWindowATOR::bitChanged(int id, QModbusDataUnit::RegisterType table, bool value)
{
    if (!modbusDevice)
        return;

    if (!modbusDevice->setData(table, quint16(id), value))
        statusBar()->showMessage(tr("Could not set data: ") + modbusDevice->errorString(), 5000);
}

void MainWindowATOR::setRegister(const QString &value)
{
    if (!modbusDevice)
        return;

    const QString objectName = QObject::sender()->objectName();
    if (registers.contains(objectName)) {
        bool ok = true;
        const quint16 id = quint16(QObject::sender()->property("ID").toUInt());
        if (objectName.startsWith(QStringLiteral("inReg")))
            ok = modbusDevice->setData(QModbusDataUnit::InputRegisters, id, value.toUShort(&ok));
        else if (objectName.startsWith(QStringLiteral("holdReg")))
            ok = modbusDevice->setData(QModbusDataUnit::HoldingRegisters, id, value.toUShort(&ok));

        if (!ok)
            statusBar()->showMessage(tr("Could not set register: ") + modbusDevice->errorString(),
                                     5000);
    }
}

void MainWindowATOR::updateWidgets(QModbusDataUnit::RegisterType table, int address, int size)
{
    for (int i = 0; i < size; ++i) {
        quint16 value;
        QString text;
        switch (table) {
        case QModbusDataUnit::Coils:
            //modbusDevice->data(QModbusDataUnit::Coils, quint16(address + i), &value);
            //coilButtons.button(address + i)->setChecked(value);
            break;
        case QModbusDataUnit::HoldingRegisters:
            modbusDevice->data(QModbusDataUnit::HoldingRegisters, quint16(address + i), &value);
            registers.value(QStringLiteral("holdReg_%1").arg(address + i))->setText(text
                .setNum(value));
            break;
        default:
            break;
        }
    }
}
*/

void MainWindowATOR::setRegister(const QString &value)
{
    if (!modnet)
        return;

    QLineEdit * lineEdit = static_cast< QLineEdit * >( QObject::sender() );
    if ( !lineEdit )
    {
        return;
    }

    QHash<int, QHash<QString, QLineEdit *> >::iterator it;
    for ( it = devs.begin(); it != devs.end(); ++ it   )
    {
        if (it.value().values().contains( lineEdit )) {

            bool ok = true;
            quint16 id = lineEdit->property("ID").toUInt();
            Slave *slave = modnet->getSlaves()[ static_cast<quint8>( it.key() )];

            if (lineEdit->objectName().startsWith(QStringLiteral("inReg")))
            {
                slave->setInputRegister(id, value.toUShort(&ok) );
            } else if (lineEdit->objectName().startsWith(QStringLiteral("holdReg")))
            {
                slave->setHoldingRegister(id, value.toUShort(&ok) );
            } else {
                ok = false;
            }
            if (!ok)
            {
                statusBar()->showMessage( QString("Addr %1. Could not set register: %2 ").arg( it.key() ).arg( lineEdit->objectName() ) );
            }
            break;
        }
    }
}

// -- private

void MainWindowATOR::setupDeviceData()
{/*
    if (!modbusDevice)
        return;

    //for (quint16 i = 30000; i < coilButtons.buttons().count(); ++i)
    //    modbusDevice->setData(QModbusDataUnit::Coils, i, coilButtons.button(i)->isChecked());

    //for (quint16 i = 30000; i < discreteButtons.buttons().count(); ++i) {
    //    modbusDevice->setData(QModbusDataUnit::DiscreteInputs, i,
    //        discreteButtons.button(i)->isChecked());
    //}

    bool ok;
    for (QLineEdit *widget : qAsConst(registers))
    {
        if (widget->objectName().startsWith(QStringLiteral("inReg"))) {
            modbusDevice->setData(QModbusDataUnit::InputRegisters, quint16(widget->property("ID").toUInt()),
                widget->text().toUShort(&ok));
        } else if (widget->objectName().startsWith(QStringLiteral("holdReg"))) {
            modbusDevice->setData(QModbusDataUnit::HoldingRegisters, quint16(widget->property("ID").toUInt()),
                widget->text().toUShort(&ok));
        }
    }*/
}

void MainWindowATOR::setupWidgetContainers()
{
    devs.clear();
    QRegularExpression regexp;

    const QList<QGroupBox *> qgb = ui->centralWidget->findChildren<QGroupBox *>();
    for (QGroupBox *gb : qgb)
    {
        //Поиск адресов устройств
        const QList<QSpinBox *> qsp = gb->findChildren<QSpinBox *>();
        if ( qsp.isEmpty() ) {
            continue;
        }
        qsp.at(0)->value();

        //Поиск регистров
        QHash<QString, QLineEdit *> registers;
        regexp.setPattern(QLatin1String("(in|hold)Reg_\\d+_(?<ID>\\d+)"));
        const QList<QLineEdit *> qle = gb->findChildren<QLineEdit *>(regexp);

        for (QLineEdit *lineEdit : qle)
        {
            registers.insert(lineEdit->objectName(), lineEdit);
            lineEdit->setProperty("ID", regexp.match(lineEdit->objectName()).captured("ID").toInt());
    //        lineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression(QStringLiteral("[0-9a-f]{0,4}"),
    //            QRegularExpression::CaseInsensitiveOption), this));
            lineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression(QStringLiteral("[0-9]{0,5}"),
                QRegularExpression::CaseInsensitiveOption), this));
            connect(lineEdit, &QLineEdit::textChanged, this, &MainWindowATOR::setRegister);
        }

        devs.insert( qsp.at(0)->value(), registers);
    }

    setupNetwork();
}

void MainWindowATOR::setupNetwork()
{
    QHash<int, QHash<QString, QLineEdit *> >::iterator it;
    for ( it = devs.begin(); it != devs.end(); ++ it   )
    {
        Slave *slave = new Slave();
        slave->setID(static_cast<quint8>(it.key()));
        slave->setDescription("Slave #" + QString::number(slave->getID()));

        for(QLineEdit *lineEdit : it.value() )
        {
            QString sectionName;
            DataType type;
            if (lineEdit->objectName().startsWith(QStringLiteral("inReg")))
            {
               sectionName = "InputRegister";
               type = INPUT_REGISTER;
            } else if (lineEdit->objectName().startsWith(QStringLiteral("holdReg")))
            {
               sectionName = "HoldingRegister";
               type = HOLDING_REGISTER;
            } else {
               sectionName = "ErrorRegister";
               type = HOLDING_REGISTER;
            }

            data_unit_t<quint16> rv;
            rv.address = static_cast<quint16>( lineEdit->property("ID").toInt() );
            rv.value = static_cast<quint16>( lineEdit->text().toInt());
            rv.description = sectionName + " #" + QString::number(rv.address);

            slave->addRegisterValue(type, rv);
        }

        connect(slave, &Slave::updateHoldingRegisters,
                this, &MainWindowATOR::updateHoldingRegisters);

        modnet->addSlave(slave);
    }
}

void MainWindowATOR::updateHoldingRegisters(quint8 id)
{
    QHash<int, QHash<QString, QLineEdit *> >::iterator it = devs.find(id);
    if (it == devs.end())
    {
        return;
    }

    Slave *slave = modnet->getSlaves()[id];

    const QMap<quint16, data_unit_t<quint16> > holding = slave->getHoldingRegisters();

    for(QLineEdit *lineEdit : it.value() )
    {
        if ( lineEdit->objectName().startsWith(QStringLiteral("holdReg") ) )
        {
             quint16 regAddr = static_cast<quint16>( lineEdit->property("ID").toInt() );

             lineEdit->setText( QString::number( holding[regAddr].value ) );
        }
    }
}

void MainWindowATOR::logPring(QString msg)
{
    statusBar()->showMessage( msg, 5000 );
}
