#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#define MAXNUM 100

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
    myServer = new QTcpServer(this);
}

//绑定绑定按钮_slots
void MainWindow::on_btn_bind_clicked()
{
    QString myAddr;
    //方法1：通过程序遍历网卡ip
//    QList<QHostAddress> addrs = QNetworkInterface::allAddresses();
//    for(int i = 0 ; i<addrs.length() ; i++){
//        QHostAddress addr = addrs.at(i);
//        QDebug()<<addr.toString();
//        if(addr.toString().contains("127.")){
//            myAddr = addr.toString();
//            break;
//        }

//    }


    //方法2：手动设置ip
    myAddr = ui->ledit_server_addr->text();
    QString myPort = ui->ledit_server_port->text();

    QString msg;
    bool ret = myServer->listen(QHostAddress(myAddr),myPort.toUInt());

    if(!ret){
        msg = "绑定失败";
    }else{
        msg="绑定成功";
    }
    //绑定状态
     ui->textEdit->append(msg);
     //绑定之后，设置最大监听数量
     myServer->setMaxPendingConnections(MAXNUM);
     //接下来使用信号，因为我们不确定客户端连接的情况，当连接上的时候，需要发送一个信号
     connect(myServer,SIGNAL(newConnection()),this,SLOT(doProcessnewConnection()));
     //若果出现了连接失败，就弹出错误
     connect(myServer,SIGNAL(acceptError(QAbstractSocket::SocketError)),this,SLOT(doProcessAcceptError(QAbstractSocket::SocketError)));
}

void MainWindow::doProcessnewConnection(){
    //检测客户端的连接
    QTcpSocket *client = myServer->nextPendingConnection();
    //客户端退出
    connect(client,SIGNAL(disconnected()),this,SLOT(doProcessDisconnected()));
    //读取客户端数据
    connect(client,SIGNAL(readyRead()),this,SLOT(doProcessReadyRead()));
}

void MainWindow::doProcessAcceptError(QAbstractSocket::SocketError){
    QString msg = QString("连接失败");
    ui->textEdit->append(msg);
}

void MainWindow::doProcessDisconnected(){
    QTcpSocket *client =(QTcpSocket *) this->sender();
    QString msg = QString("客户端[%1:%2] 退出！").arg(client->peerAddress().toString()).arg(client->peerPort());
    ui->textEdit->append(msg);
}
void MainWindow::doProcessReadyRead(){
    QTcpSocket *client =(QTcpSocket *) this->sender();
    QString str1 = QString("客户端[%1:%2] 说：").arg(client->peerAddress().toString()).arg(client->peerPort());
    QString msg;
    QString str2;
    while(!client->atEnd()){
        msg.append(QString(client->readAll()));

    }
    str2 =QString("%1%2").arg(str1).arg(msg);
    ui->textEdit->append(str2);
}
//end slots
