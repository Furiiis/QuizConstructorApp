#include "addquestiondialog.h"
#include "ui_editablequestiondialog.h"


AddQuestionDialog::AddQuestionDialog(QWidget *parent) :
    EditableQuestionDialog(parent)
{
    connect(ui->buttonBox->buttons()[0], SIGNAL(clicked()), this, SLOT(addQuestionToDb()));
    //connect(questionWidget, SIGNAL(SignalFromCheckButton()), this, SLOT(CheckQuestionState()));
}

AddQuestionDialog::~AddQuestionDialog()
{

}

void AddQuestionDialog::addQuestionToDb() const
{
        DatabaseManager::instance().addQuestion(Question(NULL,
              ui->questionTextEdit->toPlainText(), answers_->getAnswers(),
                                                    ui->descriptionTextEdit->toPlainText(), ui->sourceTextEdit->toPlainText()));
}

//void AddQuestionDialog::removeAnswersListRows()
//{
//    QModelIndex index = ui->listView->selectionModel()->currentIndex();
//    int count = ui->listView->selectionModel()->selectedIndexes().size();
//    ui->listView->model()->removeRows(index.row(), count, index.parent());
//}

//void AddQuestionDialog::addAnswersListRows()
//{
//    QModelIndex index = ui->listView->selectionModel()->currentIndex();
//    if(ui->listView->selectionModel()->selectedIndexes().size() == 0)
////        ui->listView->model()->insertRow(ui->listView->model()->rowCount() - 1, index.parent());
//        ui->listView->model()->insertRow(index.row()+1, index.parent());
//    else
//        ui->listView->model()->insertRow(index.row(), index.parent());
//}
