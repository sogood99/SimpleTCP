#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nameLable = new QLabel(ui->centralwidget);
    nameLable->setGeometry(100,0,100,50);
    nameLable->setText("Client");
    nameLable->show();
    recieved = new QTextEdit(ui->centralwidget);
    recieved->setGeometry(500,200,100,100);
    recieved->setReadOnly(true);
    recieved->setText("Recieved text");
    connectButton = new QPushButton(ui->centralwidget);
    connectButton->setGeometry(100,100,100,50);
    connectButton->setText("Connect");
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
    recieved->hide();
    socket = new QTcpSocket(this);
    QObject::connect(connectButton, &QPushButton::clicked, this, &MainWindow::connectTry);
    QObject::connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readStuff);
    QObject::connect(socket, &QTcpSocket::stateChanged, this, &MainWindow::stateisChanged);
    QObject::connect(giveText, &QPushButton::clicked, this, &MainWindow::sendText);
}

MainWindow::~MainWindow()
{
    if (socket->state() == QTcpSocket::ConnectedState){
        socket->disconnectFromHost();
    }
    socket->close();
    delete ui;
}

void MainWindow::connectTry(){
    if (socket->state() == QTcpSocket::ConnectedState){
        socket->disconnectFromHost();
    }else if (socket->state() == QTcpSocket::UnconnectedState){
        socket->connectToHost("127.0.0.1", quint16(91234));
    }else{
        socket->abort();
    }
}

void MainWindow::sendText(){
    QString str = inputText->toPlainText();
    socket->write(QByteArray(str.toUtf8()));
}

void MainWindow::readStuff(){
    qDebug()<<"Client: Recieved";
    QByteArray datas = socket->readAll();
    recieved->setText(datas);
}

void MainWindow::stateisChanged(){
    qDebug()<<"State is changed";
    if (socket->state() == QTcpSocket::ConnectedState){
        status->setStyleSheet("background-color:green");
        inputText->show();
        giveText->show();
        recieved->show();
    }else if (socket->state() == QTcpSocket::ConnectingState){
        status->setStyleSheet("background-color:blue");
        inputText->hide();
        giveText->hide();
        recieved->hide();
    }else{
        status->setStyleSheet("background-color:red");
        inputText->hide();
        giveText->hide();
        recieved->hide();
    }
}
