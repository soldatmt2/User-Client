#ifndef XMLREADER_H
#define XMLREADER_H

#include <QObject>
#include <QtXml>
#include <question.h>

class XMLReader : public QObject
{
    Q_OBJECT
public:
    explicit XMLReader(QObject *parent = 0);
    ~XMLReader();
    void start(QString text);
    void traverseNode(const QDomNode& node);
    void question(const QDomNode& node);
    void answers(const QDomNode& node);
    QList<Question *> getResult();
private:
    QList <Question*> questions;
signals:

public slots:
};

#endif // XMLREADER_H
