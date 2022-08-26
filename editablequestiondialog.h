#ifndef EDITABLEQUESTIONDIALOG_H
#define EDITABLEQUESTIONDIALOG_H

#include <QDialog>
#include <databasemanager.h>
#include "editableanswerlistmodel.h"
#include "question.h"
#include "tagsfilterdialog.h"

namespace Ui {
class EditableQuestionDialog; // RENAME
}

class EditableQuestionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditableQuestionDialog(QWidget *parent = nullptr,
                                    const Question& question = {});
    virtual ~EditableQuestionDialog();

public slots:
    void removeAnswersListRows();
    void addAnswersListRows();
    void CreateTagsDialog();

protected:
    EditableAnswerListModel* answers_;
    TagsFilterDialog* tagsDialog;
    Ui::EditableQuestionDialog *ui;
};

#endif // EDITABLEQUESTIONDIALOG_H
