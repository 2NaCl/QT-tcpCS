#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>

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
    void on_btn_bind_clicked();

    void on_btn_send_clicked();

    void doProcessConnected();//判断连接状态

    void doProcessReadyRead();//读取服务器的数据

    void doProcessDisconnect();//断开连接

    void doProcessError(QAbstractSocket::SocketError);//连接失败

private:
    Ui::MainWindow *ui;
    QTcpSocket *myClient;

    void Init();
};

#endif // MAINWINDOW_H
