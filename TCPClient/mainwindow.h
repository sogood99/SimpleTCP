#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QNetworkInterface>

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
    QTextEdit* recieved;
    QPushButton* connectButton;
    QTextEdit* inputText;
    QPushButton* giveText;
    QLabel* status;

public slots:
    void readStuff();
    void stateisChanged();
    void connectTry();
    void sendText();

private:
    Ui::MainWindow *ui;
    QTcpSocket* socket;
};
#endif // MAINWINDOW_H
