/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_config;
    QAction *actionQuit;
    QWidget *centralWidget;
    QGroupBox *gbConnection;
    QComboBox *cbPortName;
    QComboBox *cbBaubrate;
    QComboBox *cbDataBits;
    QComboBox *cbStopBits;
    QComboBox *cbParity;
    QPushButton *pbConnect;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QGroupBox *groupBox;
    QPushButton *pbCleanLog;
    QPlainTextEdit *ptSystemLog;
    QListWidget *lwSlavesList;
    QGroupBox *groupBox_2;
    QTableWidget *twDiscreteInputs;
    QTableWidget *twCoils;
    QTableWidget *twInputRegisters;
    QTableWidget *twHoldingRedisters;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1020, 691);
        actionOpen_config = new QAction(MainWindow);
        actionOpen_config->setObjectName(QString::fromUtf8("actionOpen_config"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gbConnection = new QGroupBox(centralWidget);
        gbConnection->setObjectName(QString::fromUtf8("gbConnection"));
        gbConnection->setGeometry(QRect(10, 0, 1001, 91));
        cbPortName = new QComboBox(gbConnection);
        cbPortName->setObjectName(QString::fromUtf8("cbPortName"));
        cbPortName->setGeometry(QRect(20, 50, 131, 25));
        cbBaubrate = new QComboBox(gbConnection);
        cbBaubrate->addItem(QString());
        cbBaubrate->addItem(QString());
        cbBaubrate->addItem(QString());
        cbBaubrate->addItem(QString());
        cbBaubrate->addItem(QString());
        cbBaubrate->addItem(QString());
        cbBaubrate->addItem(QString());
        cbBaubrate->addItem(QString());
        cbBaubrate->addItem(QString());
        cbBaubrate->addItem(QString());
        cbBaubrate->addItem(QString());
        cbBaubrate->addItem(QString());
        cbBaubrate->addItem(QString());
        cbBaubrate->setObjectName(QString::fromUtf8("cbBaubrate"));
        cbBaubrate->setGeometry(QRect(160, 50, 101, 25));
        cbDataBits = new QComboBox(gbConnection);
        cbDataBits->addItem(QString());
        cbDataBits->addItem(QString());
        cbDataBits->addItem(QString());
        cbDataBits->addItem(QString());
        cbDataBits->addItem(QString());
        cbDataBits->setObjectName(QString::fromUtf8("cbDataBits"));
        cbDataBits->setGeometry(QRect(270, 50, 71, 25));
        cbStopBits = new QComboBox(gbConnection);
        cbStopBits->addItem(QString());
        cbStopBits->addItem(QString());
        cbStopBits->setObjectName(QString::fromUtf8("cbStopBits"));
        cbStopBits->setGeometry(QRect(350, 50, 71, 25));
        cbParity = new QComboBox(gbConnection);
        cbParity->addItem(QString());
        cbParity->addItem(QString());
        cbParity->addItem(QString());
        cbParity->setObjectName(QString::fromUtf8("cbParity"));
        cbParity->setGeometry(QRect(430, 50, 71, 25));
        pbConnect = new QPushButton(gbConnection);
        pbConnect->setObjectName(QString::fromUtf8("pbConnect"));
        pbConnect->setGeometry(QRect(520, 50, 101, 25));
        label = new QLabel(gbConnection);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 30, 81, 17));
        label_2 = new QLabel(gbConnection);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(160, 30, 81, 17));
        label_3 = new QLabel(gbConnection);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(270, 30, 71, 17));
        label_4 = new QLabel(gbConnection);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(350, 30, 71, 17));
        label_5 = new QLabel(gbConnection);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(440, 30, 51, 17));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(240, 520, 771, 131));
        pbCleanLog = new QPushButton(groupBox);
        pbCleanLog->setObjectName(QString::fromUtf8("pbCleanLog"));
        pbCleanLog->setGeometry(QRect(670, 30, 81, 25));
        ptSystemLog = new QPlainTextEdit(groupBox);
        ptSystemLog->setObjectName(QString::fromUtf8("ptSystemLog"));
        ptSystemLog->setGeometry(QRect(10, 60, 751, 61));
        lwSlavesList = new QListWidget(centralWidget);
        lwSlavesList->setObjectName(QString::fromUtf8("lwSlavesList"));
        lwSlavesList->setGeometry(QRect(10, 100, 221, 551));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(240, 100, 771, 421));
        twDiscreteInputs = new QTableWidget(groupBox_2);
        twDiscreteInputs->setObjectName(QString::fromUtf8("twDiscreteInputs"));
        twDiscreteInputs->setGeometry(QRect(10, 40, 371, 171));
        twCoils = new QTableWidget(groupBox_2);
        twCoils->setObjectName(QString::fromUtf8("twCoils"));
        twCoils->setGeometry(QRect(390, 40, 371, 171));
        twInputRegisters = new QTableWidget(groupBox_2);
        twInputRegisters->setObjectName(QString::fromUtf8("twInputRegisters"));
        twInputRegisters->setGeometry(QRect(10, 241, 371, 171));
        twHoldingRedisters = new QTableWidget(groupBox_2);
        twHoldingRedisters->setObjectName(QString::fromUtf8("twHoldingRedisters"));
        twHoldingRedisters->setGeometry(QRect(390, 240, 371, 171));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 20, 81, 17));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(400, 20, 81, 17));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 220, 81, 17));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(400, 220, 101, 17));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1020, 18));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen_config);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);

        retranslateUi(MainWindow);

        cbDataBits->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "QSlave Modbus network emulator", nullptr));
        actionOpen_config->setText(QCoreApplication::translate("MainWindow", "Open config", nullptr));
        actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        gbConnection->setTitle(QCoreApplication::translate("MainWindow", "Connection", nullptr));
        cbBaubrate->setItemText(0, QCoreApplication::translate("MainWindow", "9600", nullptr));
        cbBaubrate->setItemText(1, QCoreApplication::translate("MainWindow", "19200", nullptr));
        cbBaubrate->setItemText(2, QCoreApplication::translate("MainWindow", "38400", nullptr));
        cbBaubrate->setItemText(3, QCoreApplication::translate("MainWindow", "57600", nullptr));
        cbBaubrate->setItemText(4, QCoreApplication::translate("MainWindow", "115200", nullptr));
        cbBaubrate->setItemText(5, QCoreApplication::translate("MainWindow", "125000", nullptr));
        cbBaubrate->setItemText(6, QCoreApplication::translate("MainWindow", "230400", nullptr));
        cbBaubrate->setItemText(7, QCoreApplication::translate("MainWindow", "250000", nullptr));
        cbBaubrate->setItemText(8, QCoreApplication::translate("MainWindow", "460800", nullptr));
        cbBaubrate->setItemText(9, QCoreApplication::translate("MainWindow", "500000", nullptr));
        cbBaubrate->setItemText(10, QCoreApplication::translate("MainWindow", "921600", nullptr));
        cbBaubrate->setItemText(11, QCoreApplication::translate("MainWindow", "1000000", nullptr));
        cbBaubrate->setItemText(12, QCoreApplication::translate("MainWindow", "2000000", nullptr));

        cbDataBits->setItemText(0, QCoreApplication::translate("MainWindow", "5", nullptr));
        cbDataBits->setItemText(1, QCoreApplication::translate("MainWindow", "6", nullptr));
        cbDataBits->setItemText(2, QCoreApplication::translate("MainWindow", "7", nullptr));
        cbDataBits->setItemText(3, QCoreApplication::translate("MainWindow", "8", nullptr));
        cbDataBits->setItemText(4, QCoreApplication::translate("MainWindow", "9", nullptr));

        cbStopBits->setItemText(0, QCoreApplication::translate("MainWindow", "1", nullptr));
        cbStopBits->setItemText(1, QCoreApplication::translate("MainWindow", "2", nullptr));

        cbParity->setItemText(0, QCoreApplication::translate("MainWindow", "None", nullptr));
        cbParity->setItemText(1, QCoreApplication::translate("MainWindow", "Odd", nullptr));
        cbParity->setItemText(2, QCoreApplication::translate("MainWindow", "Even", nullptr));

        pbConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Serial port", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Baubrate", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Data bits", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Stop bits", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Parity", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "System log", nullptr));
        pbCleanLog->setText(QCoreApplication::translate("MainWindow", "Clean", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Device memory map", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Discrete Inputs", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Coils", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Input Registers", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Holding Registers", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "&File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
