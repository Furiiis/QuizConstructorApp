#include "editablequestiondialog.h"
#include <QtCore>
#include "ui_editablequestiondialog.h"

EditableQuestionDialog::EditableQuestionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditableQuestionDialog)
{
    ui->setupUi(this);
    answers_ = new EditableAnswerListModel();
    ui->listView->setModel(answers_);
}

EditableQuestionDialog::EditableQuestionDialog(QWidget *parent, const Question& question) :
    QDialog(parent),
    ui(new Ui::EditableQuestionDialog)
{
    ui->setupUi(this);
    answers_ = new EditableAnswerListModel(question.answers_);
    ui->listView->setModel(answers_);
    ui->questionNumberLabel->setText(QString::number(question.number_));
    ui->questionTextEdit->setText(question.question_);
    ui->descriptionTextEdit->setText(question.description_);
    ui->sourceTextEdit->setText(question.source_);
}

EditableQuestionDialog::~EditableQuestionDialog()
{
    delete answers_;
    delete ui;
}

void EditableQuestionDialog::removeAnswersListRows()
{
    QModelIndex index = ui->listView->selectionModel()->currentIndex();
    int count = ui->listView->selectionModel()->selectedIndexes().size();
    ui->listView->model()->removeRows(index.row(), count, index.parent());
}

void EditableQuestionDialog::addAnswersListRows()
{
    QModelIndex index = ui->listView->selectionModel()->currentIndex();
    if(ui->listView->selectionModel()->selectedIndexes().size() == 0)
//        ui->listView->model()->insertRow(ui->listView->model()->rowCount() - 1, index.parent());
        ui->listView->model()->insertRow(index.row()+1, index.parent());
    else
        ui->listView->model()->insertRow(index.row(), index.parent());
}

