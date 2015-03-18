#include "settingdialog.h"

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent)
{
    settingsFilename = QString("config/term.ini");

    settings = new QSettings(settingsFilename,QSettings::IniFormat);
    initGUI();
    initSignals();
    readSettings();
}

void SettingDialog::initGUI(){
    this->resize(400,300);
    layout = new QGridLayout(this);
    buttonLayout = new QHBoxLayout(this);
    labelIP = new QLabel("Server Address",this);
    labelPort = new QLabel("Port",this);
    textPort = new QLineEdit(this);
    textIP = new QLineEdit(this);
    buttonOK = new QPushButton(this);
    buttonOK->setText("Okay");
    buttonCancle = new QPushButton(this);
    buttonCancle->setText("Nah");
    buttonLayout->addStretch();
    buttonLayout->addWidget(buttonOK);
    buttonLayout->addWidget(buttonCancle);
    textIP->setMaxLength(15);
    layout->addWidget(labelIP,0,0);
    layout->addWidget(textIP,0,1);
    layout->addWidget(labelPort,1,0);
    layout->addWidget(textPort,1,1);
    layout->addLayout(buttonLayout,2,1);
    this->setLayout(layout);
}

void SettingDialog::readSettings(){
    textIP->setText(settings->value("IPAddr").toString());
    textPort->setText(settings->value("Port").toString());
}
void SettingDialog::writeSettings(){
    settings->setValue("IPAddr",textIP->text());
    settings->setValue("Port",textPort->text().toInt());
    this->hide();
}

void SettingDialog::initSignals(){
    connect(buttonOK,SIGNAL(clicked()),this,SLOT(writeSettings()));
    connect(buttonCancle,SIGNAL(clicked()),this,SLOT(close()));
}

