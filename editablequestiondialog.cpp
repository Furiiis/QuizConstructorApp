#include "editablequestiondialog.h"
#include <QtCore>
#include "ui_editablequestiondialog.h"
#include <iostream>

EditableQuestionDialog::EditableQuestionDialog(QWidget *parent, const Question& question) :
    QDialog(parent),
    ui(new Ui::EditableQuestionDialog)
{
    ui->setupUi(this);
    answers_ = new EditableAnswerListModel(question.answers_);
    tagsDialog = new TagsFilterDialog(this, DatabaseManager::instance().getAllTagsExceptQuestions(question.number_),
                                      question.tags_
        );
    ui->listView->setModel(answers_);
    ui->questionNumberLabel->setText(QString::number(question.number_));
    ui->questionTextEdit->setText(question.question_);
    ui->descriptionTextEdit->setText(question.description_);
    ui->sourceTextEdit->setText(question.source_);

    connect(ui->tagsPushButton, SIGNAL(clicked()),
            this, SLOT(CreateTagsDialog()));
}

EditableQuestionDialog::~EditableQuestionDialog()
{
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

void EditableQuestionDialog::CreateTagsDialog()
{
    tagsDialog->exec();
}
