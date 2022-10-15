#include "testform.h"
#include "ui_testform.h"

TestForm::TestForm(const TestSessionData &sessionData, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestForm),
    _sessionData(sessionData)
{
    ui->setupUi(this);
    questionWidget = new TestWindowForm(this, _sessionData.questions[current_question_index]);
    //questionWidget = new TestWindowForm(this, *current_question);
    ui->verticalLayout->addWidget(questionWidget);
    ui->questionsSizeLabel->setText(QString::number(_sessionData.questions.size()));
    ui->currentNumberLabel->setText(QString::number(current_question_index + 1));

    connect(questionWidget, SIGNAL(SignalFromCheckButton()), this, SLOT(EnableNextButton()));
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

    //TestWindowForm* temp_question_widget = new TestWindowForm(this, *std::next(current_question));
    TestWindowForm* temp_question_widget = new TestWindowForm(this,
                                           _sessionData.questions[current_question_index + 1]);

//    ui->verticalLayout->removeWidget(questionWidget);
////    questionWidget = temp_question_widget;
//    ui->verticalLayout->replaceWidget(questionWidget, temp_question_widget);
    std::swap(questionWidget, temp_question_widget);
    delete temp_question_widget;
    ui->verticalLayout->addWidget(questionWidget);
    connect(questionWidget, SIGNAL(SignalFromCheckButton()), this, SLOT(EnableNextButton()));

    ++current_question_index;
    ui->currentNumberLabel->setText(QString::number(current_question_index+1));
////    questionWidget = temp_question_widget;
////    questionWidget->show();
////    questionWidget = temp_question_widget;
////    ui->verticalLayout->update();
//    ui->verticalLayout->addWidget(questionWidget);
//    questionWidget->
//    delete temp_question_widget;

     IsNextQuestionLast();
}

void TestForm::EnableNextButton() const //RENAME
{
    //if(questionWidget->IsChecked())
    ui->nextPushButton->setEnabled(true);
}

bool TestForm::IsNextQuestionLast() const
{
    if(current_question_index + 1 == _sessionData.questions.size())
    {
        ui->nextPushButton->setVisible(false);
        return true;
    }
    else return false;
}
