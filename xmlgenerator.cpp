#include "xmlgenerator.h"
#include <QDebug>

XMLGenerator::XMLGenerator(QObject *parent) : QObject(parent)
{

}

XMLGenerator::~XMLGenerator()
{

}

QString XMLGenerator::start(QList<Question *> questions, bool isRight)
{
    QDomDocument doc("questions");
    QDomElement  domElement = doc.createElement("questions");
    doc.appendChild(domElement);

    for(int i = 0; i < questions.count(); i++)
    {
        Question* quest = questions.at(i);
        QDomElement element = this->question(i,quest->getText(), quest->getRightAnswer(), quest->getAnswers(), doc, isRight);
        domElement.appendChild(element);
    }
    return doc.toString(0);
}

QDomElement XMLGenerator::question(int id, QString text, int rightAnswer,
                                   QMap<int, QString> *answers, QDomDocument domDoc, bool isRight)
{
    QDomElement question = domDoc.createElement("question");
    QDomElement idElm = domDoc.createElement("id");
    QDomElement textElm = domDoc.createElement("text");
    QDomElement right = domDoc.createElement("rightAnswer");
    QDomElement answersElm = domDoc.createElement("answers");

    QDomText idText = domDoc.createTextNode(QString::number(id));
    idElm.appendChild(idText);
    QDomText textElmText = domDoc.createTextNode(text);
    textElm.appendChild(textElmText);
    QDomText rightText;
    if(isRight)
        rightText = domDoc.createTextNode(QString::number(rightAnswer));
    else
        rightText = domDoc.createTextNode("0");
    right.appendChild(rightText);

    QMap<int, QString> map = *answers;

    QMapIterator<int, QString>* answer = new QMapIterator<int, QString>(map);


    while (answer->hasNext())
    {
        answer->next();
        QDomElement answerElm = this->answer(answer->value(), answer->key(), domDoc);
        answersElm.appendChild(answerElm);
    }
    question.appendChild(idElm);
    question.appendChild(textElm);
    question.appendChild(right);
    question.appendChild(answersElm);
    return question;
}

QDomElement XMLGenerator::answer(QString text, int id, QDomDocument domDoc)
{
    QDomElement answerElm = domDoc.createElement("answer");
    answerElm.setAttribute("id", id);
    answerElm.setAttribute("text", text);
    return answerElm;
}

