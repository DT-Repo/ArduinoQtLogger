#ifndef PLOTWIN_H
#define PLOTWIN_H

#include <QDialog>
#include <QSerialPort>
#include <QByteArray>
#include <QElapsedTimer>
#include <QCloseEvent>
#include <QFile>
#include <QTextStream>


namespace Ui {
class PlotWin;
}

class PlotWin : public QDialog
{
    Q_OBJECT

public:
    explicit PlotWin(QWidget *parent = 0);
    ~PlotWin();
    QSerialPort *arduino;

protected:
    void closeEvent(QCloseEvent *event);

signals:
    void closing();

public slots:
    void connection_created(QString);

private slots:
    void on_plotButton_clicked();
    void on_stopButton_clicked();
    void on_exitButton_clicked();
    void readSerial();
    void updateChart(QString, QString);
    void on_gridCheckBox_stateChanged(int arg1);
    void on_recordCheckBox_stateChanged(int arg1);

private:
    Ui::PlotWin *ui;
    QByteArray serialData;
    QString serialBuffer;
    QString parsed_data_temp;
    QString parsed_data_hum;
    double temperature_value;
    double humidity_value;
    QVector<double> qv_x, qv_y;
    QElapsedTimer timer;
    double yMax;
    double yMin;
    bool status = false;
    bool timerStarted = false;
    QFile file;
    bool record_on = false;
    QString filename = "../ArduinoPlotterInterface/Recorded_data/record.csv";
    QTextStream stream;
};

#endif // PLOTWIN_H
