#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include <QColor>
#include <QKeyEvent>
#include <QToolBar>
#include <QPushButton>
#include <QIcon>
#include "qterminal.h"
#include "settingdialog.h"


//#include <openssl/ssl.h>
//#include <openssl/err.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initGUI();
    QTerminal* term;
    SettingDialog* settingDialog;
    QToolBar* settingDock;
    QPushButton* settingButton;
    QPushButton* connectButton;
    QPushButton* disconnectButton;

private slots:
    void buttonStatus(int status);
protected:
};

#endif // MAINWINDOW_H
