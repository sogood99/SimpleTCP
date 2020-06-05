#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new QTcpServer(this);
    server->listen(QHostAddress("127.0.0.1"), quint16(91234));
    socket = new QTcpSocket(this);
    nameLable = new QLabel(ui->centralwidget);
    nameLable->setGeometry(100,0,100,20);
    nameLable->setText("Server");
    serverLable = new QLabel(ui->centralwidget);
    serverLable->setGeometry(100,100,100,20);
    serverLable->setText(server->serverAddress().toString());
    portLable = new QLabel(ui->centralwidget);
    portLable->setGeometry(100,120,100,100);
    portLable->setText(QString::number(server->serverPort()));
    inputText = new QTextEdit(ui->centralwidget);
    inputText->setGeometry(100,200,400,100);
    giveText = new QPushButton(ui->centralwidget);
    giveText->setGeometry(100,350,60,30);
    giveText->setText("Send");
    status = new QLabel(ui->centralwidget);
    status->setGeometry(300,100,60,60);
    status->setStyleSheet("background-color:red");
    inputText->hide();
    giveText->hide();
    recievedText = new QTextEdit(ui->centralwidget);
    recievedText->setReadOnly(true);
    recievedText->setGeometry(500,200,100,100);
    recievedText->setText("Recieved");
    recievedText->hide();
    connect(server, &QTcpServer::newConnection, this, &MainWindow::connected);
    connect(giveText, &QPushButton::clicked, this, &MainWindow::sendText);
    qDebug()<<"Server running";
}

MainWindow::~MainWindow(){
    if (socket->state() == QTcpSocket::ConnectedState){
        socket->disconnectFromHost();
    }
    socket->close();
    server->close();
    delete ui;
}

void MainWindow::connected(){
    socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::stateChanged, this, &MainWindow::statusChanged);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readStuff);
    connect(socket, &QTcpSocket::stateChanged, this, &MainWindow::statusChanged);
    statusChanged();
    qDebug()<<"Server: Connected";
}

void MainWindow::statusChanged(){
    if (socket->state() == QTcpSocket::ConnectedState){
        status->setStyleSheet("background-color:green");
        inputText->show();
        giveText->show();
        recievedText->show();
    }else if (socket->state() == QTcpSocket::ConnectingState){
        status->setStyleSheet("background-color:blue");
        inputText->hide();
        giveText->hide();
        recievedText->hide();
    }else{
        status->setStyleSheet("background-color:red");
        inputText->hide();
        giveText->hide();
        recievedText->hide();
    }
}

void MainWindow::sendText(){
    QString str = inputText->toPlainText();
    socket->write(QByteArray(str.toUtf8()));
}

void MainWindow::readStuff(){
    qDebug()<<"Server: Recieved";
    QByteArray data = socket->readAll();
    recievedText->setText(data);
}
