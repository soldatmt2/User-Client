#ifndef QUESTION_H
#define QUESTION_H

#include <QObject>
#include <QMap>

class Question : public QObject
{
    Q_OBJECT
public:
    explicit Question(QObject *parent = 0);
    int addAnswer(QString text);
    void addAnswer(QString text, int id);
    QString getAnswerText(int id);
    void setAnswerText(int id, QString text);
    void setRightAnswer(int id);
    int getRightAnswer();
    int getAnswersCount();
    QMap<int, QString> *getAnswers();
    QList<int> getIds();
    void setText(QString text);
    QString getText();
    void deleteAnswer(int id);
    void setId(int id);

private:
    QMap<int, QString>* answerList;
    QString text;
    int rightAnswer;
    int id;

signals:

public slots:

};

#endif // QUESTION_H
