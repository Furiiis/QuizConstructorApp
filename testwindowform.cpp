#include "testwindowform.h"
#include "ui_testwindowform.h"
#include <iostream>

TestWindowForm::TestWindowForm(QWidget *parent) : QWidget(parent),
    ui(new Ui::TestWindowForm)
{
    ui->setupUi(this);
    _test_window = new TestPageModel();
    tags_model = new TagListModel();
    ui->answerListView->setModel(_test_window->answers_list_);
    ui->questionLabel->setText(_test_window->question_);
    ui->descriptionLabel->setText(_test_window->description_);
    ui->sourceLabel->setText(_test_window->source_);

    ui->descriptionLabel->setVisible(false);
    ui->sourceLabel->setVisible(false);

    connect(ui->tagsPushButton, SIGNAL(clicked()), this, SLOT(RunTagsDialog()));
}

TestWindowForm::TestWindowForm(QWidget *parent, const Question &question)
    : QWidget(parent), ui(new Ui::TestWindowForm)
{
    ui->setupUi(this);
    answers_model = new ReadableAnswerListModel(question.answers_);
    tags_model = new TagListModel(question.tags_);
    ui->questionNumberLabel->setText(QString::number(question.number_));
    ui->answerListView->setModel(answers_model);
    ui->questionLabel->setText(question.question_);
    ui->descriptionLabel->setText(question.description_);
    ui->sourceLabel->setText(question.source_);

    ui->descriptionLabel->setVisible(false);
    ui->sourceLabel->setVisible(false);

    connect(ui->tagsPushButton, SIGNAL(clicked()), this, SLOT(RunTagsDialog()));
}

TestWindowForm::~TestWindowForm()
{
    delete ui;
}

void TestWindowForm::CheckAnswers()
{
    answers_model->changeState();
//    ui->answerListView->selectionModel()->clearSelection();
/*    ui->answerListView->selectionModel()->selectedIndexes().clear();
    ui->answerListView->selectionModel()->deleteLater();
    ui->answerListView->selectAll();
    ui->answerListView->clearSelection();*/

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

void TestWindowForm::RunTagsDialog()
{
    QDialog* tags_dialog = new QDialog(this, Qt::WindowStaysOnTopHint);
    tags_dialog->setModal(true);
    QVBoxLayout *tags_layout = new QVBoxLayout{tags_dialog};
    tags_layout->addWidget(new QLabel{tr("Tags"), this});
    QListView* tags_listview = new QListView{this};
    tags_listview->setModel(tags_model);
    tags_layout->addWidget(tags_listview);

    tags_dialog->show();
}
