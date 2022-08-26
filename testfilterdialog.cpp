#include "testfilterdialog.h"
#include "ui_testfilterdialog.h"
#include "databasemanager.h"
#include "testsessiondata.h"
#include "testform.h"
#include "taglistmodel.h"

TestFilterDialog::TestFilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestFilterDialog)
{
    ui->setupUi(this);
    tagsDialog = new TagsFilterDialog(parent, DatabaseManager::instance().getAllTags());
//    ui->tagsComboBox->setModel( new TagListModel(DatabaseManager::instance().getAllTags()) );
    connect(ui->tagsPushButton, SIGNAL(clicked()), this, SLOT(OpenTagsFilterDialog()));
}

TestFilterDialog::~TestFilterDialog()
{
    delete ui;
}

void TestFilterDialog::startTestSession()
{
    int questions_limit = ui->amountSpinBox->value();
    TestSessionData sessionData;
    if(questions_limit > 0)
    {
        sessionData.tags = tagsDialog->GetSelectedTags();
//        sessionData.questions = DatabaseManager::instance().getQuestions(questions_limit);
        sessionData.questions = DatabaseManager::instance().getQuestions(questions_limit, sessionData.tags);
        Qt_StackWidget::instance().addCurrentWidget(new TestForm(sessionData));
    }
//    this->~TestFilterDialog();
    this->close();
}

void TestFilterDialog::OpenTagsFilterDialog() const
{
    tagsDialog->exec();
}
