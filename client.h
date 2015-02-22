#ifndef CLIENT_H
#define CLIENT_H
//ghbdtn
#include <QObject>
#include <QtNetwork>
#include <QtDebug>

class client : public QObject
{
    Q_OBJECT
public:
    explicit client(QObject *parent = 0);
    ~client();
    void connectTo(QString name);
    QString getXML();
    void sendResult(QString result);
private:
    void sendData(QString str);
    void parseCmd(QString cmd);

    QString queryConstruct(QString type, QString data);

    QTcpSocket* socket;
    QString name;
    QString xmlQuestions;

    int id;
    qint64 xmlFileLength;
    qint16 msgSize;

signals:
    void xmlFileReceived();
    void rightAnswers(int);

public slots:
    void on_readyRead();
};

#endif // CLIENT_H
