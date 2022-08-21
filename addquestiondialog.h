#ifndef ADDQUESTIONDIALOG_H
#define ADDQUESTIONDIALOG_H

#include <QDialog>
#include <editableanswerlistmodel.h>
#include <databasemanager.h>
#include "question.h"
#include "editablequestiondialog.h"


//namespace Ui {
//class AddQuestionDialog;
//}

class AddQuestionDialog : public EditableQuestionDialog
{
    Q_OBJECT

public:
    explicit AddQuestionDialog(QWidget *parent = nullptr);
    ~AddQuestionDialog();

public slots:
    void addQuestionToDb() const;
//    void removeAnswersListRows();
//    void addAnswersListRows();

//private:
//    EditableAnswerListModel* answers;
//    Ui::AddQuestionDialog *ui;
};

#endif // ADDQUESTIONDIALOG_H
