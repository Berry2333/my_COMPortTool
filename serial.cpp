#include "serial.h"
#include "ui_serial.h"

Serial::Serial(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Serial)
{
    ui->setupUi(this);
    //user
    system_init();
}

Serial::~Serial()
{
    delete ui;
}

/*--------------------------------
 *            function
 *-------------------------------*/
void Serial::system_init(){
    //port config
    global_port.setParity(QSerialPort::NoParity);
    global_port.setDataBits(QSerialPort::Data8);
    global_port.setStopBits(QSerialPort::OneStop);

    //connect
    connect(ui->btn_open, &QPushButton::clicked, this, &Serial::btn_open_port);
    connect(ui->btn_send, &QPushButton::clicked, this, &Serial::btn_send_data);
    connect(&global_port, &QSerialPort::readyRead,this,&Serial::receive_data);
    connect(ui->btn_close, &QPushButton::clicked, this, &Serial::btn_close_port);
}

/*--------------------------------
 *            slots
 *-------------------------------*/
void Serial::btn_open_port(bool){
    //获取端口号
    qDebug()<<ui->cmb_port_name->currentIndex();


/*-----------------port_name----------------*/
    switch (ui->cmb_port_name->currentIndex()) {
    case 0:
        global_port.setPortName("COM1");
        break;
    case 1:
        global_port.setPortName("COM2");
        break;
    case 2:
        global_port.setPortName("COM3");
        break;
    case 3:
        global_port.setPortName("COM4");
        break;
    case 4:
        global_port.setPortName("COM5");
        break;
    case 5:
        global_port.setPortName("COM5");
        break;
    case 6:
        global_port.setPortName("COM7");
        break;
    default:
        global_port.setPortName("COM8");
        break;
    }


/*-----------------band_rate----------------*/

    switch (ui->cmb_baud_rate->currentIndex()) {
    case 0:
        global_port.setBaudRate(QSerialPort::Baud115200);
        break;
    case 1:
        global_port.setBaudRate(QSerialPort::Baud57600);
        break;
    case 2:
        global_port.setBaudRate(QSerialPort::Baud38400);
        break;
    case 3:
        global_port.setBaudRate(QSerialPort::Baud19200);
        break;
    case 4:
        global_port.setBaudRate(QSerialPort::Baud9600);
        break;
    case 5:
        global_port.setBaudRate(QSerialPort::Baud4800);
        break;
    case 6:
        global_port.setBaudRate(QSerialPort::Baud2400);
        break;
    default:
        global_port.setBaudRate(QSerialPort::Baud1200);
        break;
    }

    //open
    global_port.open(QIODevice::ReadWrite);

    ui->Lab_status->setText("Connected");
    //global_port.write("1");
}
/*-----------------close com-------------------*/
void Serial::btn_close_port(bool){
    global_port.close();
    ui->Lab_status->setText("Disconnected");
}

/*-----------------sending_data----------------*/
void Serial::btn_send_data(bool){

    qDebug()<<ui->lint_send_data->text();
    QString data = ui->lint_send_data->text();
    QByteArray array = data.toLatin1();

    global_port.write(array);
}

/*-----------------receive_data----------------*/
void Serial::receive_data(){
    QByteArray array = global_port.readAll();
    qDebug()<<array;

    if(ui->checkBox->checkState()==Qt::Checked){
        ui->play_Text->insertPlainText(QString(array.toHex(' ').toUpper().append(' ')));
    }else{
        ui->play_Text->insertPlainText(QString(array));
    }
}
