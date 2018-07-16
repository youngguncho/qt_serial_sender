#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QIODevice>
#include <QTimer>
#include <QtSerialBus/QtSerialBus>
#include <QString>
#include <QDebug>
#include <QList>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_radio_btn_balance_clicked(bool checked);

    void on_radio_btn_gait_clicked(bool checked);

    void on_radio_btn_stand_clicked(bool checked);

    void on_balancce_slider_valueChanged(int value);

    void on_gait_slider_valueChanged(int value);

    void on_stand_slider_valueChanged(int value);

    void on_serial_combo_currentIndexChanged(const QString &arg1);

    void on_serial_button_clicked();

    void balance_publish();

    void gait_pubish();

    void standup_publish();

    void on_start_button_clicked();

    void on_radio_btn_balance_toggled(bool checked);

    void on_radio_btn_gait_toggled(bool checked);

    void on_radio_btn_stand_toggled(bool checked);

    void on_stop_button_clicked();

private:
    Ui::MainWindow *ui;

    bool is_balance_ = false;
    bool is_gait_ = false;
    bool is_standup_ = false;

    int balance_val_ = 0;
    int gait_val_ = 0;
    int standup_val_ = 0;

    QString serial_name_;
    QSerialPort *port_;

    QTimer *balance_timer_;
    QTimer *gait_timer_;
    QTimer *standup_timer_;



};

#endif // MAINWINDOW_H
