#include "qtermhistory.h"

QTermHistory::QTermHistory(QWidget *parent) :
    QObject((QObject*)parent)
{
    history = new QVector<QString>();
}

QString QTermHistory::getNext(){
    if((!history->isEmpty()
        && (history->length()-1 > currentPos)
         && currentPos>=0)){
        return history->at(currentPos++);
    }
    return "";
}
QString QTermHistory::getPrev(){
    if((!history->isEmpty()
            && currentPos >=0)){
        return history->at(currentPos--);
    }
    return "";
}

void QTermHistory::putCmd(QString cmd){
    if(cmd.isEmpty()){
        return;
    }
    history->append(cmd);
    currentPos = history->length()-1;
//    qDebug()<<"Put cmd: " + cmd<<endl;
    return;
}
