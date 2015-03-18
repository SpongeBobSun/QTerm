#include "qterminal.h"
//#include <QDebug>

QTerminal::QTerminal(QWidget *parent) :
    QPlainTextEdit(parent)
{
    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    setPalette(p);
    content = new QString();
    cmdLen = 0;
    cursorPos = 0;
    connected = false;

    endCursor = this->textCursor();
    endCursor.movePosition(QTextCursor::End);

    completer = new QTermHistory(this);

}


void QTerminal::keyReleaseEvent(QKeyEvent *e){
    if(!connected){
        QMessageBox::information(NULL,"Warning","Not connected to server!",
                      QMessageBox::Yes,QMessageBox::Yes);
        return;
    }

    switch (e->key()) {
    case Qt::Key_Up:
//        content->clear();
//        content->append(completer->getPrev());
//        if(content->isEmpty()){
//            content->append(echoContent);
//            return;
//        }
//        echoContent.clear();
//        echoContent.append(*content);
//        cmdLen = content->length();
//        cursorPos =  cmdLen-1;
//        comCursor = this->textCursor();
//        comCursor.movePosition(QTextCursor::NoMove,QTextCursor::KeepAnchor,cmdLen);
//        comCursor.select(QTextCursor::LineUnderCursor);
//        comCursor.removeSelectedText();
//        this->setTextCursor(comCursor);
//        this->insertPlainText(echoContent);
        return;
    case Qt::Key_Down:
//        content->clear();
//        content->append(completer->getNext());
//        if(content->isEmpty()){
//            content->append(echoContent);
//            return;
//        }
//        echoContent.clear();
//        echoContent.append(*content);
//        cmdLen = content->length();
//        cursorPos =  cmdLen-1;
//        comCursor = this->textCursor();
//        comCursor.movePosition(QTextCursor::NoMove,QTextCursor::KeepAnchor,cmdLen);
//        comCursor.select(QTextCursor::LineUnderCursor);
//        comCursor.removeSelectedText();
//        this->setTextCursor(comCursor);
//        this->insertPlainText(echoContent);
        return;
    case Qt::Key_Return:
        this->setTextCursor(endCursor);
        this->insertPlainText("\r\n");
        completer->putCmd(*content);
        lineByte = content->append("\r\n").toLocal8Bit();
        socket->write(lineByte.data(),cmdLen+2);
        echoContent = *content;
        content->clear();
        lineByte.clear();
        cmdLen = 0;
        cursorPos = 0;
        return;
     case Qt::Key_Backspace:
        if(cmdLen){
            cmdLen--;
            cursorPos--;
            content->remove(cursorPos,1);
//            QPlainTextEdit::keyReleaseEvent(e);
            backspaceCursor = this->textCursor();
            backspaceCursor.deletePreviousChar();
            this->setTextCursor(backspaceCursor);
        }
        return;
    case Qt::Key_Left:
      return;
    case Qt::Key_Right:
      return;
    case Qt::Key_Shift:
        QPlainTextEdit::keyReleaseEvent(e);
        return;
    case Qt::Key_Delete:
        if(cmdLen){
            delCursor = this->textCursor();
            delCursor.deleteChar();
            this->setTextCursor(delCursor);
            content->remove(cursorPos,1);
            cmdLen--;
        }
      return;
    }

    cmdLen++;
    cursorPos++;
    *content+=e->text();
    this->insertPlainText(e->text());
    return;

}

void QTerminal::initSocket(){

    if(!readSettings()){
//        qDebug()<<"IP and Port error"<<endl;
        QMessageBox::information(NULL,"Warning","Invalid configuration!",
                      QMessageBox::Yes,QMessageBox::Yes);
        return;
    }

    socket = new QSslSocket(this);

    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(encrypted()),
            this, SLOT(socketEncrypted()));
    connect(socket, SIGNAL(sslErrors(QList<QSslError>)),
            this, SLOT(sslErrors(QList<QSslError>)));
    connect(socket, SIGNAL(readyRead()),
            this, SLOT(socketReadyRead()));

    socket->connectToHostEncrypted(serverIP,serverPort);

}

void QTerminal::socketEncrypted(){
    if(!socket){
        return;
    }
//    QSslCipher ciph = socket->sessionCipher();
//    QString cipher = QString("%1, %2 (%3/%4)").arg(ciph.authenticationMethod())
//                     .arg(ciph.name()).arg(ciph.usedBits()).arg(ciph.supportedBits());
//    qDebug()<<"cipher infomation:"<<endl;
//    qDebug()<<cipher<<endl;
}


void QTerminal::socketStateChanged(QAbstractSocket::SocketState state){
       if (state == QAbstractSocket::UnconnectedState) {
           connected = false;
           emit socketStatus(-1);
           socket->deleteLater();
           socket = 0;
       }
       if(state == QAbstractSocket::ConnectedState){
           connected = true;
            emit socketStatus(1);
       }
}
void QTerminal::socketReadyRead(){
    if(socketStr){
        delete(socketStr);
    }
    socketStr = new QString(socket->readAll());
    if(socketStr->compare(echoContent) == 0){
        echoContent.clear();
        socketStr->clear();
        return;
    }
    if(socketStr->at(0).unicode() == IAC_IAC){
        telnetHandShake(socketStr);
        return;
    }
    this->insertPlainText(*socketStr);
    this->setTextCursor(endCursor);
    socketStr->clear();

}
void QTerminal::sslErrors(const QList<QSslError> &errors){
    socket->ignoreSslErrors();
}

bool QTerminal::readSettings(){
    QSettings* set = new QSettings("config/term.ini",QSettings::IniFormat);
    serverIP = set->value("IPAddr").toString();
    serverPort = set->value("Port").toInt();
    set->deleteLater();
    if(serverIP.length()==0 || serverPort < 0){
        return false;
    }
    return true;
}

void QTerminal::disconnect(){
    socket->disconnectFromHost();
    socket->deleteLater();
}
void QTerminal::keyPressEvent(QKeyEvent *e){
    if(!connected){
        QMessageBox::information(NULL,"Warning","Not connected to server!",
                      QMessageBox::Yes,QMessageBox::Yes);
    }
    if(e->modifiers() == Qt::ControlModifier){
        if(e->key() == Qt::Key_Y){
            lineByte = content->append("\r\n").toLocal8Bit();
            //TO-DO
            //write len maybe incorrect
            socket->write(lineByte.data(),4);
            content->clear();
            lineByte.clear();
            cmdLen = 0;
            cursorPos = 0;
            return;
        }
        QPlainTextEdit::keyPressEvent(e);
        return;
    }
    switch (e->key()) {
    case Qt::Key_Left:
          if(cmdLen != 0){
              cursorPos--;
          }
          QPlainTextEdit::keyPressEvent(e);
      return;
    case Qt::Key_Right:
        if(cmdLen != cursorPos){
            cursorPos++;
        }
          QPlainTextEdit::keyPressEvent(e);
      return;

    }
}

void QTerminal::telnetHandShake(QString* str){
    qDebug()<<"enter hand shake"<<endl;
    QByteArray response;
    response.clear();
    if(str->at(1) == IAC_WILL){
        if(str->at(2) == IAC_TERM){
            response.append((char)IAC_IAC);
            response.append((char)IAC_DO);
            response.append((char)IAC_TERM);
            socket->write(response,3);
            qDebug()<<"hand shake - term"<<endl;
        }
    }
    if(str->at(1) == IAC_SB){

    }
}
