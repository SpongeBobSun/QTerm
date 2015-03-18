#include "mainwindow.h"

//#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initGUI();
    connect(settingButton,SIGNAL(clicked()),settingDialog,SLOT(show()));
    connect(connectButton,SIGNAL(clicked()),term,SLOT(initSocket()));
    connect(term,SIGNAL(socketStatus(int)),this,SLOT(buttonStatus(int)));
    connect(disconnectButton,SIGNAL(clicked()),term,SLOT(disconnect()));
}

void MainWindow::initGUI(){
    term = new QTerminal(this);
    term->setCursorWidth(6);
    this->setCentralWidget(term);
    this->resize(QSize(800,600));

    settingDialog = new SettingDialog(this);
    settingDock = new QToolBar();
    settingButton = new QPushButton(settingDock);
//    settingButton->setText("Settings");
    settingButton->setIcon(QIcon(":/Image/settings.png"));
    settingButton->setWhatsThis("Configuration");
    connectButton = new QPushButton(settingDock);
    connectButton->setWhatsThis("Connect");
//    connectButton->setText("Connect");
    connectButton->setIcon(QIcon(":/Image/connect.png"));
    disconnectButton = new QPushButton(settingDock);
    disconnectButton->setWhatsThis("Disconnect");
//    disconnectButton->setText("Disconnect");
    disconnectButton->setIcon(QIcon(":/Image/disconnect.png"));
    disconnectButton->setEnabled(false);
    settingDock->addWidget(connectButton);
    settingDock->addWidget(disconnectButton);
    settingDock->addWidget(settingButton);
    this->addToolBar(settingDock);
}

void MainWindow::buttonStatus(int status){
    if(status>0){
        connectButton->setEnabled(false);
        disconnectButton->setEnabled(true);
//        qDebug()<<"Connected"<<endl;
    }else{
        connectButton->setEnabled(true);
        disconnectButton->setEnabled(false);
//        qDebug()<<"Disconnected"<<endl;
    }
}

MainWindow::~MainWindow()
{

}
