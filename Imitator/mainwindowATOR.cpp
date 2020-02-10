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
#include "settingsdialog.h"
#include "ui_mainwindowATOR.h"

#include <QModbusRtuSerialSlave>
#include <QModbusTcpServer>
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
    ui->portEdit->setText("\\\\.\\COM5");
#else
    ui->portEdit->setText("/dev/ttyUSB1");
#endif

    setupWidgetContainers();

//#if QT_CONFIG(modbus_serialport)
    ui->connectType->setCurrentIndex(0);
    onCurrentConnectTypeChanged(0);
//#else
//    // lock out the serial port option
//    ui->connectType->setCurrentIndex(1);
//    onCurrentConnectTypeChanged(1);
//    ui->connectType->setEnabled(false);
//#endif

    m_settingsDialog = new SettingsDialog(this);
    initActions();
    initVVODigIn();
    initVVODigOut();
}

MainWindowATOR::~MainWindowATOR()
{
    if (modbusDevice)
        modbusDevice->disconnectDevice();
    delete modbusDevice;

    delete ui;
}

void MainWindowATOR::initActions()
{
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionExit->setEnabled(true);
    ui->actionOptions->setEnabled(true);

    connect(ui->connectButton, &QPushButton::clicked,
            this, &MainWindowATOR::onConnectButtonClicked);
    connect(ui->actionConnect, &QAction::triggered,
            this, &MainWindowATOR::onConnectButtonClicked);
    connect(ui->actionDisconnect, &QAction::triggered,
            this, &MainWindowATOR::onConnectButtonClicked);
    connect(ui->connectType, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindowATOR::onCurrentConnectTypeChanged);

    connect(ui->actionExit, &QAction::triggered, this, &QMainWindow::close);
    connect(ui->actionOptions, &QAction::triggered, m_settingsDialog, &QDialog::show);
}

void MainWindowATOR::initVVODigIn()
{
    connect(ui->inReg_0, &QLineEdit::textChanged,
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

    ui->inReg_0->setText(QString("%1").arg( u ));
}

void MainWindowATOR::initVVODigOut()
{
    connect(ui->holdReg_0, &QLineEdit::textChanged,
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
}

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

// -- private

void MainWindowATOR::setupDeviceData()
{
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
    }
}

void MainWindowATOR::setupWidgetContainers()
{
    QRegularExpression regexp;
/*
    coilButtons.setExclusive(false);
    discreteButtons.setExclusive(false);

    regexp.setPattern(QStringLiteral("coils_(?<ID>\\d+)"));
    const QList<QCheckBox *> coils = findChildren<QCheckBox *>(regexp);
    for (QCheckBox *cbx : coils)
        coilButtons.addButton(cbx, regexp.match(cbx->objectName()).captured("ID").toInt());
    connect(&coilButtons, SIGNAL(buttonClicked(int)), this, SLOT(coilChanged(int)));

    regexp.setPattern(QStringLiteral("disc_(?<ID>\\d+)"));
    const QList<QCheckBox *> discs = findChildren<QCheckBox *>(regexp);
    for (QCheckBox *cbx : discs)
        discreteButtons.addButton(cbx, regexp.match(cbx->objectName()).captured("ID").toInt());
    connect(&discreteButtons, SIGNAL(buttonClicked(int)), this, SLOT(discreteInputChanged(int)));
*/
    regexp.setPattern(QLatin1String("(in|hold)Reg_(?<ID>\\d+)"));

    const QList<QLineEdit *> qle = ui->groupBox->findChildren<QLineEdit *>(regexp);

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
}
