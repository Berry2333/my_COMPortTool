#ifndef SERIAL_H
#define SERIAL_H

#include <QMainWindow>

/*-----user-----------*/
#include <QSerialPort>
//debug
#include <QtDebug>
/*--------------------*/
QT_BEGIN_NAMESPACE
namespace Ui { class Serial; }
QT_END_NAMESPACE

class Serial : public QMainWindow
{
    Q_OBJECT

public:
    Serial(QWidget *parent = nullptr);
    ~Serial();
private:
    // button
    void btn_open_port(bool);
    void btn_send_data(bool);

    void btn_close_port(bool);
    //receive data
    void receive_data();

private:
    Ui::Serial *ui;
    /*------------function-------------------*/
    void system_init();
    /*------------variable-------------------*/
    QSerialPort global_port;
};
#endif // SERIAL_H
