#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QList<QSerialPortInfo> serial_list = QSerialPortInfo::availablePorts();
    QStringList name_list;
    for (auto port : serial_list){
        qDebug() << port.portName();
        name_list.push_back(port.portName());
    }

    port_ = new QSerialPort();
    port_->setBaudRate(QSerialPort::Baud57600);
    port_->setDataBits(QSerialPort::Data8);
    port_->setParity(QSerialPort::NoParity);
    port_->setStopBits(QSerialPort::OneStop);
    port_->setFlowControl(QSerialPort::NoFlowControl);

    ui->serial_combo->addItems(name_list);

    balance_timer_ = new QTimer(this);
    gait_timer_ = new QTimer(this);
    standup_timer_ = new QTimer(this);

    QObject::connect(balance_timer_, SIGNAL(timeout()), this, SLOT(balance_publish()));
    QObject::connect(gait_timer_, SIGNAL(timeout()), this, SLOT(gait_pubish()));
    QObject::connect(standup_timer_, SIGNAL(timeout()), this, SLOT(standup_publish()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radio_btn_balance_clicked(bool checked)
{
    is_balance_ = checked;
}

void MainWindow::on_radio_btn_gait_clicked(bool checked)
{
    is_gait_ = checked;
}

void MainWindow::on_radio_btn_stand_clicked(bool checked)
{
    is_standup_ = checked;
}

void MainWindow::on_balancce_slider_valueChanged(int value)
{
    balance_val_ = value;
    ui->balance_lcd->display(value);
}

void MainWindow::on_gait_slider_valueChanged(int value)
{
    gait_val_ = value;
    ui->gait_lcd->display(value);
}

void MainWindow::on_stand_slider_valueChanged(int value)
{
    standup_val_ = value;
    ui->stand_lcd->display(value);
}

void MainWindow::on_serial_combo_currentIndexChanged(const QString &arg1)
{
    serial_name_ = arg1;
}

void MainWindow::on_serial_button_clicked()
{
    if (port_->isOpen())
        port_->close();

    port_->setPortName(serial_name_);

    if(port_->open(QIODevice::ReadWrite)) {
        ui->statusBar->showMessage(QString("Open Success!!"));
//        qDebug() << "Serial Port Open Error ";
    }
    else {
        ui->statusBar->showMessage(QString("Open Error!!"));
    }
}

void MainWindow::balance_publish()
{
    QByteArray write_data;

    write_data.append('B');
    QString number = QString("%1").arg(balance_val_, 6, 10, QChar('0'));

    write_data.append(number); write_data.append(',');
    write_data.append(number); write_data.append(',');
    write_data.append(number); write_data.append(',');
    write_data.append(number);

    write_data.append('\n');
    port_->write(write_data);
    port_->waitForBytesWritten(1);

    QString text = "Balance: " + number;
    ui->statusBar->showMessage(text);

}

void MainWindow::gait_pubish()
{
    QByteArray write_data;

    write_data.append('d');
    QString number = QString("%1").arg(gait_val_, 6, 10, QChar('0'));

    write_data.append(number);

    write_data.append('\n');
    port_->write(write_data);
    port_->waitForBytesWritten(1);

    QString text = "Gait: " + number;
    ui->statusBar->showMessage(text);
}

void MainWindow::standup_publish()
{
    QByteArray write_data;

    write_data.append('S');
    QString number = QString("%1").arg(standup_val_, 6, 10, QChar('0'));

    write_data.append(number);
    write_data.append('\n');
    port_->write(write_data);
    port_->waitForBytesWritten(1);

    QString text = "Standup: " + number;
    ui->statusBar->showMessage(text);
}

void MainWindow::on_start_button_clicked()
{
    if (is_balance_) balance_timer_->start(20);
    if (is_gait_) gait_timer_->start(20);
    if (is_standup_) standup_timer_->start(20);
}

void MainWindow::on_stop_button_clicked()
{
    balance_timer_->stop();
    gait_timer_->stop();
    standup_timer_->stop();
}

void MainWindow::on_radio_btn_balance_toggled(bool checked)
{
    is_balance_ = checked;
}

void MainWindow::on_radio_btn_gait_toggled(bool checked)
{
    is_gait_ = checked;
}

void MainWindow::on_radio_btn_stand_toggled(bool checked)
{
    is_standup_ = checked;
}

