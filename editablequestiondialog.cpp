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
    QModelIndex selected_index = ui->listView->selectionModel()->currentIndex();
    int rows_count = ui->listView->model()->rowCount();

    if(rows_count == 0)
    {
        ui->listView->model()->insertRow(0);
    }
    else if(selected_index.row() == -1)
    {
        ui->listView->model()->insertRow(rows_count - 1);
    }
    else
        ui->listView->model()->insertRow(selected_index.row());
}

void EditableQuestionDialog::CreateTagsDialog()
{
    tagsDialog->exec();
}
