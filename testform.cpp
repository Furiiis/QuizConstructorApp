#include "testform.h"
#include "ui_testform.h"

TestForm::TestForm(const TestSessionData &sessionData, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestForm),
    _sessionData(sessionData)
{
    ui->setupUi(this);
    questionWidget = new TestWindowForm(this, *current_question);
    ui->verticalLayout->addWidget(questionWidget);

    connect(questionWidget, SIGNAL(SignalFromCheckButton()), this, SLOT(CheckQuestionState()));
    IsNextQuestionLast();
}

TestForm::~TestForm()
{
    delete ui;
}

void TestForm::BackToMenu() const
{
    Qt_StackWidget::instance().activatePerviousView();
}

void TestForm::NextQuestion()
{

    TestWindowForm* temp_question_widget = new TestWindowForm(this, *std::next(current_question));

//    ui->verticalLayout->removeWidget(questionWidget);
////    questionWidget = temp_question_widget;
//    ui->verticalLayout->replaceWidget(questionWidget, temp_question_widget);
    std::swap(questionWidget, temp_question_widget);
    delete temp_question_widget;
    ui->verticalLayout->addWidget(questionWidget);
    connect(questionWidget, SIGNAL(SignalFromCheckButton()), this, SLOT(CheckQuestionState()));

    current_question++;
////    questionWidget = temp_question_widget;
////    questionWidget->show();
////    questionWidget = temp_question_widget;
////    ui->verticalLayout->update();
//    ui->verticalLayout->addWidget(questionWidget);
//    questionWidget->
//    delete temp_question_widget;

     IsNextQuestionLast();
}

void TestForm::CheckQuestionState() const
{
    if(IsNextQuestionLast()) return;
    if(questionWidget->IsChecked()) ui->nextPushButton->setEnabled(true);
}

bool TestForm::IsNextQuestionLast() const
{
    if(std::next(current_question) == _sessionData.questions.end())
    {
        ui->nextPushButton->setVisible(false);
        return true;
    }
    else return false;
}
