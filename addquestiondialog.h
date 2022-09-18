#ifndef ADDQUESTIONDIALOG_H
#define ADDQUESTIONDIALOG_H

#include <editableanswerlistmodel.h>
#include <databasemanager.h>
#include "question.h"
#include "editablequestiondialog.h"

class AddQuestionDialog : public EditableQuestionDialog
{
    Q_OBJECT

public:
    explicit AddQuestionDialog(QWidget *parent = nullptr);

public slots:
    void addQuestionToDb();
signals:
    void QuestionAdded(const Question& question);
};

#endif // ADDQUESTIONDIALOG_H
