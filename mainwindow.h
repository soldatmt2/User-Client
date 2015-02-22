#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include <client.h>
#include <question.h>
#include <xmlreader.h>
#include <QMessageBox>
#include <xmlgenerator.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    client* cli;
    int current;

    void setShowQuestion(bool next);
    void initQuestionsUi();
    void saveRightAnswer();
    void testFinish();
    void sendResult();

    QRadioButton* one_answer;
    QRadioButton* two_answer;
    QRadioButton* three_answer;
    QRadioButton* four_answer;

    QLabel* question_text;

    QList<Question *> questions;
public slots:
    void on_connect_clicked();
    void on_file_received();
    void on_next_question();
    void on_back_question();
    void on_right_answers(int right);
};

#endif // MAINWINDOW_H
