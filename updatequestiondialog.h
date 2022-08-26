#ifndef UPDATEQUESTIONDIALOG_H
#define UPDATEQUESTIONDIALOG_H

#include <QDialog>
#include <editableanswerlistmodel.h>
#include <databasemanager.h>
#include "question.h"
#include "editablequestiondialog.h"

class UpdateQuestionDialog : public EditableQuestionDialog
{
    Q_OBJECT

public:
    explicit UpdateQuestionDialog(const Question& question, QWidget *parent = nullptr);
    ~UpdateQuestionDialog();

public slots:
    void UpdateQuestionToDb() const;
};

#endif // UPDATEQUESTIONDIALOG_H
