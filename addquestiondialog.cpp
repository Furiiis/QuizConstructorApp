#include "addquestiondialog.h"
#include "ui_editablequestiondialog.h"

AddQuestionDialog::AddQuestionDialog(QWidget *parent) :
    EditableQuestionDialog(parent)
{
    connect(ui->buttonBox->buttons()[0], SIGNAL(clicked()),
            this, SLOT(addQuestionToDb()));
}

void AddQuestionDialog::addQuestionToDb() const
{
        DatabaseManager::instance().addQuestion(Question{NULL,
              ui->questionTextEdit->toPlainText(), answers_->getAnswers(),
              ui->descriptionTextEdit->toPlainText(), ui->sourceTextEdit->toPlainText(),
              tagsDialog->GetSelectedTags()});
}
