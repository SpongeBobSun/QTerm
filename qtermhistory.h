#ifndef QTERMHISTORY_H
#define QTERMHISTORY_H

#include <QObject>
#include <QVector>
#include <QVectorIterator>

//#include <QDebug>

class QTermHistory : public QObject
{
    Q_OBJECT
public:
    explicit QTermHistory(QWidget *parent = 0);
    void putCmd(QString cmd);
    QString getNext();
    QString getPrev();
    int currentPos;
signals:

public slots:

private:
    QVector<QString>* history;
    QVectorIterator<QString>* content;

};

#endif // QTERMHISTORY_H
