#include "menuform.h"
#include "ui_menuform.h"

MenuForm::MenuForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuForm)
{
    ui->setupUi(this);
}

MenuForm::~MenuForm()
{
    delete ui;
}

void MenuForm::quit() const
{
    quit();
}

void MenuForm::about() const
{

}

void MenuForm::startTesting() const
{
    TestFilterDialog testFilter;
    testFilter.exec();
}

void MenuForm::questionTable() const
{
    Qt_StackWidget::instance().addCurrentWidget(new QuestionTableForm());
}

void MenuForm::addQuestionButton()
{
    AddQuestionDialog dialog;
    dialog.exec();
}
