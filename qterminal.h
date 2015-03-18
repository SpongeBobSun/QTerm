#ifndef QTERMINAL_H
#define QTERMINAL_H

#include <QPlainTextEdit>
#include <QPalette>
#include <QMessageBox>
#include <QAction>
#include <QTextCursor>

#include <QSslSocket>
#include <QSsl>
#include <QAbstractSocket>
#include <QSslCipher>

#include <QSettings>

#include "qtermhistory.h"
#include "telnetIAC.h"

class QTerminal : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit QTerminal(QWidget *parent = 0);

private:
    QSslSocket *socket;
    QString* content;
    QString echoContent;
    QString* socketStr;
    QString  serverIP;
    int port;
    int cmdLen;
    int cursorPos;
    QByteArray lineByte;
    bool readSettings();
    int serverPort;
    bool connected;
    QTextCursor backspaceCursor;
    QTextCursor endCursor;
    QTextCursor hMoveCursor;
    QTextCursor delCursor;
    QTextCursor comCursor;
    QTermHistory* completer;

    void telnetHandShake(QString* str);

signals:
    void socketStatus(int);
public slots:
    void initSocket();
    void disconnect();
private slots:
    void socketStateChanged(QAbstractSocket::SocketState state);
    void socketEncrypted();
    void socketReadyRead();
    void sslErrors(const QList<QSslError> &errors);
protected:
    virtual void keyReleaseEvent(QKeyEvent *e);
    virtual void keyPressEvent(QKeyEvent *e);
};

#endif // QTERMINAL_H

