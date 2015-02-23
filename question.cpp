#include "question.h"

Question::Question(QObject *parent) :
    QObject(parent)
{
    this->answerList = new QMap<int, QString>();
}

int Question::addAnswer(QString text)
{
    int id = rand() % 10001;
    while(true)
    {
        if(this->answerList->contains(id))
            id = rand() % 10001;
        else
            break;
    }
    this->answerList->insert(id, text);
    return id;
}

void Question::addAnswer(QString text, int id)
{
    this->answerList->insert(id, text);
}

QString Question::getAnswerText(int id)
{
    if(this->answerList->contains(id))
        return this->answerList->value(id);
    else
        return "";
}

void Question::setAnswerText(int id, QString text)
{
    this->answerList->insert(id, text);
}

void Question::setRightAnswer(int id)
{
    if(this->answerList->contains(id))
        this->rightAnswer = id;
}

int Question::getRightAnswer()
{
    return this->rightAnswer;
}

int Question::getAnswersCount()
{
    return this->answerList->count();
}

QMap<int, QString> *Question::getAnswers()
{
    return this->answerList;
}

QList<int> Question::getIds()
{
    return this->answerList->keys();
}

void Question::setText(QString text)
{
    this->text = text;
}

QString Question::getText()
{
    return this->text;
}

void Question::deleteAnswer(int id)
{
    if(this->answerList->contains(id))
        this->answerList->remove(id);
}

void Question::setId(int id)
{
    this->id = id;
}
