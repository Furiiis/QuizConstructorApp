#include "updatequestiondialog.h"
#include "databasemanager.h"
#include "ui_editablequestiondialog.h"
#include "question.h"


UpdateQuestionDialog::UpdateQuestionDialog(const Question &question, QWidget *parent) :
     EditableQuestionDialog(parent, question)
{
    connect(ui->buttonBox->buttons()[0], SIGNAL(clicked()), this, SLOT(UpdateQuestionToDb()));
}

UpdateQuestionDialog::~UpdateQuestionDialog()
{

}

void UpdateQuestionDialog::UpdateQuestionToDb() const {
    DatabaseManager::instance().updateQuestion(Question(ui->questionNumberLabel->text().toInt(), ui->questionTextEdit->toPlainText(),
                                      answers_->getAnswers(),ui->descriptionTextEdit->toPlainText(),
                                                        ui->sourceTextEdit->toPlainText()));
}
