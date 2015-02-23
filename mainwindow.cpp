#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->connect_btn, SIGNAL(clicked()), SLOT(on_connect_clicked()));
    this->current = -1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setShowQuestion(bool next)
{
    if (next) this->current++;
    else this->current--;

    if(this->current >= this->questions.count())
    {
        this->testFinish();
        return;
    }

    Question* currentQuest = this->questions.at(this->current);
    QList<int> answeIds = currentQuest->getIds();
    this->one_answer->setChecked(false);
    this->two_answer->setChecked(false);
    this->three_answer->setChecked(false);
    this->four_answer->setChecked(false);
    if(currentQuest->getAnswersCount() == 2)
    {
        this->three_answer->setVisible(false);
        this->four_answer->setVisible(false);
        this->one_answer->setText(currentQuest->getAnswerText(answeIds.at(0)));
        this->two_answer->setText(currentQuest->getAnswerText(answeIds.at(1)));
    }
    else if(currentQuest->getAnswersCount() == 3)
    {
        this->three_answer->setVisible(true);
        this->four_answer->setVisible(false);
        this->one_answer->setText(currentQuest->getAnswerText(answeIds.at(0)));
        this->two_answer->setText(currentQuest->getAnswerText(answeIds.at(1)));
        this->three_answer->setText(currentQuest->getAnswerText(answeIds.at(2)));
    }
    else if(currentQuest->getAnswersCount() == 4)
    {
        this->three_answer->setVisible(true);
        this->four_answer->setVisible(true);
        this->one_answer->setText(currentQuest->getAnswerText(answeIds.at(0)));
        this->two_answer->setText(currentQuest->getAnswerText(answeIds.at(1)));
        this->three_answer->setText(currentQuest->getAnswerText(answeIds.at(2)));
        this->four_answer->setText(currentQuest->getAnswerText(answeIds.at(3)));
    }
    this->question_text->setText(currentQuest->getText());
}

void MainWindow::initQuestionsUi()
{
    delete ui->centralWidget;
    this->setGeometry(this->x(),this->y(), 640, 300);

    QWidget* generalWidget = new QWidget();
    QHBoxLayout* horizontalL = new QHBoxLayout();
    QVBoxLayout* generalVertL = new QVBoxLayout();
    QVBoxLayout* verticalL = new QVBoxLayout();
    QPushButton* nextB = new QPushButton("Далее");
    QPushButton* backB = new QPushButton("Назад");
    this->one_answer = new QRadioButton();
    this->two_answer = new QRadioButton();
    this->three_answer = new QRadioButton();
    this->four_answer = new QRadioButton();
    this->question_text = new QLabel();

    this->setCentralWidget(generalWidget);
    generalWidget->setLayout(generalVertL);
    generalVertL->addSpacerItem(new QSpacerItem(0,0));
    generalVertL->setStretch(0, 2);
    generalVertL->addWidget(this->question_text);
    generalVertL->addLayout(verticalL);
    generalVertL->addLayout(horizontalL);

    horizontalL->addWidget(backB);
    horizontalL->addWidget(nextB);

    verticalL->addWidget(this->one_answer);
    verticalL->addWidget(this->two_answer);
    verticalL->addWidget(this->three_answer);
    verticalL->addWidget(this->four_answer);

    connect(nextB, SIGNAL(clicked()), SLOT(on_next_question()));
    connect(backB, SIGNAL(clicked()), SLOT(on_back_question()));

    this->setShowQuestion(true);
}

void MainWindow::saveRightAnswer()
{
    Question * currentQuest = this->questions.at(this->current);
    if(this->one_answer->isChecked())
    {
        currentQuest->setRightAnswer(currentQuest->getAnswers()->key(this->one_answer->text()));
    }
    else if(this->two_answer->isChecked())
    {
        currentQuest->setRightAnswer(currentQuest->getAnswers()->key(this->two_answer->text()));
    }
    else if(this->three_answer->isChecked())
    {
        currentQuest->setRightAnswer(currentQuest->getAnswers()->key(this->three_answer->text()));
    }
    else if(this->four_answer->isChecked())
    {
        currentQuest->setRightAnswer(currentQuest->getAnswers()->key(this->four_answer->text()));
    }
}

void MainWindow::testFinish()
{
    QMessageBox* isFinish = new QMessageBox(QMessageBox::Information, "Выполнение теста", "Завершить выполнение теста?", QMessageBox::Yes|QMessageBox::No);
    int result = isFinish->exec();
    delete isFinish;
    if(result == QMessageBox::Yes)
    {
        this->sendResult();
    }
}

void MainWindow::sendResult()
{
    QString rightAnswers = "";
    for(int i =0; i < this->questions.count();i++)
    {
        rightAnswers += QString::number(this->questions.at(i)->getRightAnswer())+";";
    }
    this->cli->sendResult(rightAnswers.remove(rightAnswers.length()-1, 1));
}

void MainWindow::on_connect_clicked()
{
    ui->name_string->setEnabled(false);
    ui->connect_btn->setText("Подключение...");
    ui->connect_btn->setEnabled(false);
    this->cli = new client();
    connect(this->cli, SIGNAL(xmlFileReceived()), SLOT(on_file_received()));
    connect(this->cli, SIGNAL(rightAnswers(int)), SLOT(on_right_answers(int)));
    this->cli->connectTo(ui->name_string->text());
}

void MainWindow::on_file_received()
{
    XMLReader* reader = new XMLReader();
    reader->start(this->cli->getXML());
    this->questions = reader->getResult();
    this->initQuestionsUi();
}

void MainWindow::on_next_question()
{
    this->saveRightAnswer();
    this->setShowQuestion(true);
}

void MainWindow::on_back_question()
{
    this->saveRightAnswer();
    if(this->current != 0)
        this->setShowQuestion(false);
}

void MainWindow::on_right_answers(int right)
{
    this->setVisible(false);
    QMessageBox::information(this, "Результаты теста", "Павильно: "+QString::number(right)+". Всего: "+QString::number(this->current));
    delete this;
}
