#include "arduplot.h"
#include "ui_arduplot.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include "plotwin.h"

//struct arduino_data{
//    QString board;
//    quint16 arduino_product_id;
//    quint16 arduino_vendor_id;
//};

//arduino_data struct1, struct2, struct3;
//struct1.board = "coa";
//std::vector<arduino_data> arduino_id;

//struct1.board = "UNO";
//struct1.arduino_vendor_id = 4444;
//struct1.arduino_product_id = 44444;

//struct2.board = "Nano";
//struct2.arduino_vendor_id = 5555;
//struct2.arduino_product_id = 55555;
//struct3.board = "MEGA 2056";
//struct3.arduino_vendor_id = 6790;
//struct3.arduino_product_id = 29987;
//arduino_id.push_back(struct1);
//arduino_id.push_back(struct2);
//arduino_id.push_back(struct3);


QString arduino_mega_port_name;

ArduPlot::ArduPlot(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ArduPlot)
{
    ui->setupUi(this);

    QObject::connect(ui->connectButton, &QPushButton::released, this, &ArduPlot::on_connectButton_clicked);
    ui->boardComboBox->addItem("Uno");
    ui->boardComboBox->addItem("Nano");
    ui->boardComboBox->addItem("MEGA 2056");
    QObject::connect(ui->boardComboBox, &QComboBox::currentTextChanged, this, &ArduPlot::on_boardComboBox_currentTextChanged);

    win = new PlotWin();
    QObject::connect(win, SIGNAL(closing()), this, SLOT(show()));
    QObject::connect(this, &ArduPlot::create_connection, win, &PlotWin::connection_created);

}


ArduPlot::~ArduPlot()
{
    delete ui;
}

void ArduPlot::on_connectButton_clicked()
{
    if(arduino_is_available){
        emit create_connection(arduino_mega_port_name);
        hide();
        win->show();
    }
}

void ArduPlot::on_boardComboBox_currentTextChanged(const QString &arg1)
{
    if(port_ok == true){
        ui->serialComboBox->removeItem(0);
        port_ok = false;
    }
    //    for (auto it = begin (arduino_id); it != end (arduino_id); ++it) {
    //        if (!QString::compare(ui->boardComboBox->currentText(),it.board)){
    //            arduino_vendor_id = it.vendor_id;
    //            arduino_product_id = it.product_id;
    //            foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
    //                //  check if the serialport has both a product identifier and a vendor identifier
    //                if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier()){
    //                    //  check if the product ID and the vendor ID match those of the arduino uno
    //                    if((serialPortInfo.productIdentifier() == arduino_product_id)
    //                            && (serialPortInfo.vendorIdentifier() == arduino_vendor_id)){
    //                        arduino_is_available = true; //    arduino uno is available on this port
    //                        arduino_mega_port_name = serialPortInfo.portName();
    //                        ui->serialComboBox->addItem(arduino_mega_port_name);
    //                        port_ok = true;
    //                    }
    //                }
    //            }
    //        }
    //    }


    if (!QString::compare(ui->boardComboBox->currentText(),"MEGA 2056")){
        arduino_vendor_id = 6790;
        arduino_product_id = 29987;
        foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
            //  check if the serialport has both a product identifier and a vendor identifier
            if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier()){
                //  check if the product ID and the vendor ID match those of the arduino uno
                if((serialPortInfo.productIdentifier() == arduino_product_id)
                        && (serialPortInfo.vendorIdentifier() == arduino_vendor_id)){
                    arduino_is_available = true; //    arduino uno is available on this port
                    arduino_mega_port_name = serialPortInfo.portName();
                    ui->serialComboBox->addItem(arduino_mega_port_name);
                    port_ok = true;
                }
            }
        }

    }
    if (!QString::compare(ui->boardComboBox->currentText(),"Nano")){
        arduino_vendor_id = 6793;
        arduino_product_id = 22987;
        foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
            //  check if the serialport has both a product identifier and a vendor identifier
            if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier()){
                //  check if the product ID and the vendor ID match those of the arduino uno
                if((serialPortInfo.productIdentifier() == arduino_product_id)
                        && (serialPortInfo.vendorIdentifier() == arduino_vendor_id)){
                    arduino_is_available = true; //    arduino uno is available on this port
                    arduino_mega_port_name = serialPortInfo.portName();
                    ui->serialComboBox->addItem(arduino_mega_port_name);
                    port_ok = true;
                }
            }
        }
    }

    if (!QString::compare(ui->boardComboBox->currentText(),"Uno")){
        arduino_vendor_id = 9825;
        arduino_product_id = 67;
        foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
            //  check if the serialport has both a product identifier and a vendor identifier
            if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier()){
                //  check if the product ID and the vendor ID match those of the arduino uno
                if((serialPortInfo.productIdentifier() == arduino_product_id)
                        && (serialPortInfo.vendorIdentifier() == arduino_vendor_id)){
                    arduino_is_available = true; //    arduino uno is available on this port
                    arduino_mega_port_name = serialPortInfo.portName();
                    ui->serialComboBox->addItem(arduino_mega_port_name);
                    port_ok = true;
                }
            }
        }

    }

}



