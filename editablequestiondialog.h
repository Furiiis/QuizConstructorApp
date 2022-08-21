#ifndef EDITABLEQUESTIONDIALOG_H
#define EDITABLEQUESTIONDIALOG_H

#include <QDialog>
#include <databasemanager.h>
#include "editableanswerlistmodel.h"
#include "question.h"

namespace Ui {
class EditableQuestionDialog; // RENAME
}

class EditableQuestionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditableQuestionDialog(QWidget *parent = nullptr);
    explicit EditableQuestionDialog(QWidget *parent,
            const Question& question);
    virtual ~EditableQuestionDialog();

public slots:
    void removeAnswersListRows();
    void addAnswersListRows();

protected:
    EditableAnswerListModel* answers_;
    Ui::EditableQuestionDialog *ui;
};

#endif // EDITABLEQUESTIONDIALOG_H
