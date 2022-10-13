#ifndef ARDUPLOT_H
#define ARDUPLOT_H

#include <QMainWindow>
#include <QSerialPort>
#include <QByteArray>
#include "plotwin.h"

namespace Ui {
class ArduPlot;
}

class ArduPlot : public QMainWindow
{
    Q_OBJECT

public:
    explicit ArduPlot(QWidget *parent = 0);
    ~ArduPlot();

signals:
    void create_connection(QString port);

private slots:
    void on_connectButton_clicked();
    void on_boardComboBox_currentTextChanged(const QString &arg1);

private:
    Ui::ArduPlot *ui;
    quint16 arduino_vendor_id;
    quint16 arduino_product_id;
    QByteArray serialData;
    bool arduino_is_available = false;
    PlotWin * win;
    bool port_ok = false;
};

#endif // ARDUPLOT_H
