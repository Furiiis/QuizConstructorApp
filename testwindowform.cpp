#include "testwindowform.h"
#include "ui_testwindowform.h"

TestWindowForm::TestWindowForm(QWidget *parent) : QWidget(parent),
    ui(new Ui::TestWindowForm)
{
    ui->setupUi(this);
    _test_window = new TestPageModel();
    ui->answerListView->setModel(_test_window->answers_list_);
    ui->questionLabel->setText(_test_window->question_);
    ui->descriptionLabel->setText(_test_window->description_);
    ui->sourceLabel->setText(_test_window->source_);

    ui->descriptionLabel->setVisible(false);
    ui->sourceLabel->setVisible(false);
//    ui->buttonsHorizontalLayout->addWidget(next_btn_);
    //    ui->buttonsHorizontalLayout->addWidget(check_btn_);
}

TestWindowForm::TestWindowForm(QWidget *parent, const Question &question)
    : QWidget(parent), ui(new Ui::TestWindowForm)
{
    ui->setupUi(this);
    answers_model = new ReadableAnswerListModel(question.answers_);
    ui->questionNumberLabel->setText(QString::number(question.number_));
    ui->answerListView->setModel(answers_model);
    ui->questionLabel->setText(question.question_);
    ui->descriptionLabel->setText(question.description_);
    ui->sourceLabel->setText(question.source_);
}

TestWindowForm::~TestWindowForm()
{
//    delete _test_window;
//    delete ui;
}

void TestWindowForm::CheckAnswers()
{
    answers_model->changeState();
    SignalFromCheckButton();
}

void TestWindowForm::Back() const
{
    Qt_StackWidget::instance().activatePerviousView();
}

bool TestWindowForm::IsChecked() const
{
    return answers_model->IsChecked();
}
