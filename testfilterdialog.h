#ifndef TESTFILTER_H
#define TESTFILTER_H

#include <QDialog>
#include "qt_stackwidget.h"
#include "testwindowform.h"
#include "tagsfilterdialog.h"

namespace Ui {
class TestFilterDialog;
}

class TestFilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TestFilterDialog(QWidget *parent = nullptr);
    ~TestFilterDialog();

public slots:
    void startTestSession();
private:
    Ui::TestFilterDialog *ui;
    TagsFilterDialog* tagsDialog;

private slots:
    void OpenTagsFilterDialog() const;
};

#endif // TESTFILTER_H
