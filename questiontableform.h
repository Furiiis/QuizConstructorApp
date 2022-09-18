#ifndef QUESTIONTABLEFORM_H
#define QUESTIONTABLEFORM_H

#include <QWidget>
#include <QMenu>
#include "questiontablemodel.h"
#include "addquestiondialog.h"
#include "databasemanager.h"

namespace Ui {
class QuestionTableForm;
}

class QuestionTableForm : public QWidget
{
    Q_OBJECT

public:
    explicit QuestionTableForm(QWidget *parent = nullptr);
    ~QuestionTableForm();

public slots:
    void Back() const;
    void UpdateModel();
    void EditQuestion();
    void RemoveQuestion();
    void AddQuestion();
    void ContexMenuRequested(QPoint pos);

private:
    Ui::QuestionTableForm *ui;
    QuestionTableModel *question_model;

};

#endif // QUESTIONTABLEFORM_H
