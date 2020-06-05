#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    QLabel* nameLable;
    QLabel* serverLable;
    QLabel* portLable;
    QTextEdit* recievedText;
    QTextEdit* inputText;
    QPushButton* giveText;
    QLabel* status;

public slots:
    void connected();
    void readStuff();
    void statusChanged();
    void sendText();

private:
    Ui::MainWindow *ui;
    QTcpServer* server;
    QTcpSocket* socket;
};
#endif // MAINWINDOW_H
