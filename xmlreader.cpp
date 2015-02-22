#include "xmlreader.h"
#include <QDebug>

XMLReader::XMLReader(QObject *parent) : QObject(parent)
{
}

XMLReader::~XMLReader()
{

}

void XMLReader::start(QString text)
{
    QDomDocument doc;
    doc.setContent(text);
    QDomElement domElm = doc.documentElement();
    if(domElm.tagName() == "questions")
        this->traverseNode(domElm);
}

void XMLReader::traverseNode(const QDomNode &node)
{
    if(!node.isNull())
    {
        if(node.isElement())
        {
            QDomElement domElm = node.firstChildElement();
            while(!domElm.isNull())
            {
                if(domElm.tagName() == "question")
                {
                    this->question(domElm);
                }
                domElm = domElm.nextSiblingElement();
            }
        }
    }
}

void XMLReader::question(const QDomNode &node)
{
    this->questions.append(new Question());
    QDomElement domElm = node.firstChildElement();
    while(!domElm.isNull())
    {
        if(domElm.tagName() == "answers")
            answers(domElm);
        else if (domElm.tagName() == "id")
            this->questions.last()->setId(domElm.text().toInt());
        else if (domElm.tagName() == "text")
            this->questions.last()->setText(domElm.text());
        else if (domElm.tagName() == "rightAnswer")
            this->questions.last()->setRightAnswer(domElm.text().toInt());
        domElm = domElm.nextSiblingElement();
    }
}

void XMLReader::answers(const QDomNode &node)
{
    QDomElement domElm = node.firstChildElement();
    while(!domElm.isNull())
    {
        if(domElm.tagName() == "answer")
        {
            this->questions.last()->addAnswer(domElm.attribute("text"), domElm.attribute("id").toInt());
        }
        domElm = domElm.nextSiblingElement();
    }
}

QList<Question *> XMLReader::getResult()
{
    return this->questions;
}

