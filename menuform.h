#ifndef MENUFORM_H
#define MENUFORM_H

#include <QWidget>
#include "qt_stackwidget.h"
#include "testwindowform.h"
#include "questiontableform.h"
#include "addquestiondialog.h"
#include "testfilterdialog.h"

namespace Ui {
class MenuForm;
}

class MenuForm : public QWidget
{
    Q_OBJECT

public:
    explicit MenuForm(QWidget *parent = nullptr);
    ~MenuForm();

public slots:
    void quit() const;
    void about() const;
    void startTesting() const;
    void questionTable() const;
    void addQuestionButton();

private:
    Ui::MenuForm *ui;
};

#endif // MENUFORM_H
