#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}
//function
void MainWindow::Init(){
    myClient = new QTcpSocket(this);
}
//转到槽，连接服务器
void MainWindow::on_btn_bind_clicked()
{
    QString servIp = ui->ledit_server_addr->text();
    QString servPort = ui->ledit_server_port->text();
    myClient->connectToHost(QHostAddress(servIp),servPort.toUInt());
    connect(myClient,SIGNAL(connected()),this,SLOT(doProcessConnected()));//判断是否连接上
    connect(myClient,SIGNAL(readyRead()),this,SLOT(doProcessReadyRead()));//读取服务器的数据
    connect(myClient,SIGNAL(disconnected()),this,SLOT(doProcessDisconnect()));//断开连接
    connect(myClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(doProcessError(QAbstractSocket::SocketError)));//出错的事件绑定
}

//判断是否连接上
void MainWindow::doProcessConnected(){
    QString msg = QString("xxx");
    ui->textEdit->append(msg);
}
//读取服务器的数据
void MainWindow::doProcessReadyRead(){
    QString msg,str1,str2;
    str1 = QString("服务器[%1:%2] 说：")
            .arg(myClient->peerAddress().toString())
            .arg(myClient->peerPort());
    while(!myClient->atEnd()){
        str2.append((QString)myClient->readAll());
    }
    msg = QString("%1%2").arg(str1).arg(str2);
    ui->textEdit->append(msg);
}
//断开连接
void MainWindow::doProcessDisconnect(){
    QString msg = "服务器退出";
    ui->textEdit->append(msg);
}
//出错的事件绑定
void MainWindow::doProcessError(QAbstractSocket::SocketError err){
    qDebug()<<err;
}

//发送
void MainWindow::on_btn_send_clicked()
{
    QString msg = ui->textEdit_2->toPlainText();
    int ret = myClient->write(msg.toLatin1());
    if(ret<=0) return;
    ui->textEdit_2->clear();
}
