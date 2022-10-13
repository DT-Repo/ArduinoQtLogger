#include "plotwin.h"
#include "ui_plotwin.h"
#include "arduplot.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include <string>
#include <QElapsedTimer>
#include <QFile>
#include <QTextStream>

PlotWin::PlotWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlotWin)
{
    ui->setupUi(this);

    QObject::connect(ui->plotButton, &QPushButton::released, this, &PlotWin::on_plotButton_clicked);
    QObject::connect(ui->stopButton, &QPushButton::released, this, &PlotWin::on_stopButton_clicked);
    QObject::connect(ui->exitButton, &QPushButton::released, this, &PlotWin::on_exitButton_clicked);
    arduino = new QSerialPort(this);
    file.setFileName(filename);
    ui->plot->addGraph();
    // give the axes some labels:
    ui->plot->xAxis->setLabel("time[s]");
    ui->plot->yAxis->setLabel("Value");
    // set axes ranges, so we see all data:
    ui->plot->xAxis->setRange(0, 1);
    ui->plot->yAxis->setRange(0, 1);
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->plot->graph(0)->setPen(QPen(Qt::blue));
    qv_x.append(0.00);
    qv_y.append(0.00);
    ui->plot->graph(0)->setData(qv_x, qv_y);

}

PlotWin::~PlotWin()
{
    delete ui;
}

void PlotWin::on_plotButton_clicked()
{
    if(timerStarted == false){
        timer.start();
        timerStarted = true;
    }
    status = true;
}

void PlotWin::on_stopButton_clicked()
{
    status = false;
}

void PlotWin::on_exitButton_clicked()
{
    timerStarted = false;
    //arduino->close();
    this->close();

}


void PlotWin::readSerial()
{

    QStringList buffer_split = serialBuffer.split(","); //  split the serialBuffer string, parsing with ',' as the separator

    if(status == true){
        if(buffer_split.length() < 3){
            serialData = arduino->readAll();
            serialBuffer = serialBuffer + QString::fromStdString(serialData.toStdString());
            serialData.clear();
            //qDebug() << serialBuffer;
        } else {
            serialBuffer = "";
            parsed_data_temp = buffer_split[0];
            parsed_data_hum = buffer_split[1];
            temperature_value = parsed_data_temp.toDouble();
            humidity_value = parsed_data_hum.toDouble();
            parsed_data_temp = QString::number(temperature_value, 'g', 4); // format precision of temperature_value to 4 digits or fewer
            parsed_data_hum = QString::number(humidity_value, 'g', 4); // format precision of temperature_value to 4 digits or fewer

            PlotWin::updateChart(parsed_data_temp, parsed_data_hum);
        }

    }

}

void PlotWin::updateChart(const QString temp_reading, const QString hum_reading){
    double temp_value = temp_reading.toDouble();
    //double hum_value = hum_reading.toDouble();
    double time = timer.elapsed() / 1000.00;

    qv_x.append(time);
    ui->plot->xAxis->setRange(0, time + 1.00);
    qv_y.append(temp_value);
    yMin = *std::min_element(qv_y.begin(), qv_y.end());
    yMax = *std::max_element(qv_y.begin(), qv_y.end());

    ui->plot->yAxis->setRange(yMin-yMin/5, yMax+yMax/5);
    ui->plot->graph(0)->setData(qv_x, qv_y);
    ui->valueLcdNumber->display(temp_reading);
    ui->plot->replot();
    ui->plot->update();

    if(record_on){
        QTextStream stream(&file);
        stream << time << ", " << temp_value << "\n";
        stream.flush();
    }

}


void PlotWin::closeEvent(QCloseEvent *event)
{
    emit closing();
    event->accept();
}



void PlotWin::connection_created(QString port)
{
    arduino->setPortName(port);
    arduino->setBaudRate(QSerialPort::Baud9600);
    arduino->setDataBits(QSerialPort::Data8);
    arduino->setFlowControl(QSerialPort::NoFlowControl);
    arduino->setParity(QSerialPort::NoParity);
    arduino->setStopBits(QSerialPort::OneStop);
    if(!arduino->open(QSerialPort::ReadOnly)){
        //qDebug() << arduino->error();
        return;}

    QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));

}

void PlotWin::on_gridCheckBox_stateChanged(int arg1)
{
    if(arg1){
        ui->plot->xAxis->grid()->setVisible(false);
        ui->plot->yAxis->grid()->setVisible(false);
    } else {
        ui->plot->xAxis->grid()->setVisible(true);
        ui->plot->yAxis->grid()->setVisible(true);
    }
}

void PlotWin::on_recordCheckBox_stateChanged(int arg1)
{
    if(arg1){
        record_on = true;
        if(!file.open(QIODevice::WriteOnly)){
            qDebug() << "Failed open the file";
        }

    } else {
        file.close();
        record_on = false;
    }

}
