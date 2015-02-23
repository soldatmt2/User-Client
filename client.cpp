#include "client.h"

client::client(QObject *parent) : QObject(parent)
{
    this->msgSize = 0;
    this->name = "";
    this->xmlQuestions = "";
    this->id = 0;
    this->xmlFileLength = 0;
    socket = new QTcpSocket();
}

client::~client()
{

}

void client::connectTo(QString name)
{
    this->name = name;
    socket->connectToHost(QHostAddress::LocalHost, 12215);
    connect(socket, SIGNAL(readyRead()), SLOT(on_readyRead()));
}

QString client::getXML()
{
    return this->xmlQuestions;
}

void client::sendResult(QString result)
{
    this->sendData(this->queryConstruct("result", result));
}

void client::sendData(QString str)
{
    QByteArray block;
    QDataStream sendStream(&block, QIODevice::WriteOnly);
    sendStream.setVersion(QDataStream::Qt_5_0);

    sendStream << quint16(0) << str;
    sendStream.device()->seek(0);
    sendStream << (quint16)(block.size() - sizeof(quint16));
    socket->write(block);
}

void client::parseCmd(QString cmd)
{
    QStringList data = cmd.split('/');
    if(data.count() < 2)
        return;
    if(data.at(0) != "Tester")
        socket->disconnectFromHost();
    if(data.at(1) == "setid")
    {
        this->id = data.at(2).toInt();
        if(!this->id)
            qDebug() <<"id = 0";
        this->sendData(this->queryConstruct("name", this->name));
    }
    else if(data.at(1) == "filelength")
    {
        this->xmlFileLength = data.at(2).toInt();
        this->sendData(this->queryConstruct("file", "0"));
    }
    else if(data.at(1) == "file")
    {
        this->xmlQuestions += cmd.remove(0, 12);
        if(this->xmlFileLength > this->xmlQuestions.length())
            this->sendData(this->queryConstruct("file", QString::number(this->xmlQuestions.length())));
        else
            emit xmlFileReceived();
    }
    else if(data.at(1) == "right")
    {
        emit rightAnswers(data.at(2).toInt());
    }
}

QString client::queryConstruct(QString type, QString data)
{
    return "Tester/"+QString::number(this->id)+"/"+type+"/"+data;
}

void client::on_readyRead()
{
    QString buff;
    QDataStream stream(socket);
    stream.setVersion(QDataStream::Qt_5_0);

    while(true) {
        if (!msgSize) {
            if (socket->bytesAvailable() < sizeof(qint16))
                break;
            stream >> msgSize;
        }
        if (socket->bytesAvailable() < msgSize)
            break;
        stream >> buff;
        msgSize = 0;
    }
    this->parseCmd(buff);
}

