#ifndef XMLGENERATOR_H
#define XMLGENERATOR_H

#include <question.h>
#include <QObject>
#include <QtXml>

class XMLGenerator : public QObject
{
    Q_OBJECT
public:
    explicit XMLGenerator(QObject *parent = 0);
    ~XMLGenerator();
    QString start(QList<Question*> questions, bool isRight);
    QDomElement question(int id, QString text, int rightAnswer, QMap<int, QString>* answers, QDomDocument domDoc, bool isRight);
    QDomElement answer(QString text, int id, QDomDocument domDoc);

signals:

public slots:
};

#endif // XMLGENERATOR_H
