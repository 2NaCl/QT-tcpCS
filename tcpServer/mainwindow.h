#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>

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

    void doProcessnewConnection();

    void doProcessAcceptError(QAbstractSocket::SocketError);

    void doProcessDisconnected();//设置客户端断连

    void doProcessReadyRead();//读取客户端的信息

private:
    Ui::MainWindow *ui;
    QTcpServer *myServer;
    void Init();
};

#endif // MAINWINDOW_H
