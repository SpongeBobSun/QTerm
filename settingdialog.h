#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QLineEdit>
#include <QLabel>
#include <QFile>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

class SettingDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SettingDialog(QWidget *parent = 0);
signals:

public slots:

private:
    QString settingsFilename;
    QSettings* settings;
    QPushButton* buttonOK;
    QPushButton* buttonCancle;
    QLineEdit* textIP;
    QLineEdit* textPort;
    QGridLayout* layout;
    QHBoxLayout* buttonLayout;
    QLabel* labelIP;
    QLabel* labelPort;
    void readSettings();
    void initGUI();
    void initSignals();
private slots:
    void writeSettings();
};

#endif // SETTINGDIALOG_H
