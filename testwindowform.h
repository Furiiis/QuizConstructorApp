#ifndef TESTWINDOWFORM_H
#define TESTWINDOWFORM_H

#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include "readableanswerlistmodel.h"
#include "testpagemodel.h"
#include "question.h"
#include "qt_stackwidget.h"

namespace Ui {
class TestWindowForm;
}

class TestWindowForm : public QWidget
{
    Q_OBJECT

public:
    explicit TestWindowForm(QWidget *parent = nullptr);
    explicit TestWindowForm(QWidget *parent, const Question& question);
    ~TestWindowForm();

public slots:
    void CheckAnswers();
    void Back() const;
    bool IsChecked() const;

signals:
    void SignalFromCheckButton();

protected:
   TestPageModel* _test_window;
   ReadableAnswerListModel* answers_model;

public:
    Ui::TestWindowForm *ui;
//    QPushButton* next_btn_ = new QPushButton("Next");
//    QPushButton* check_btn_ = new QPushButton("Check");
};

#endif // TESTWINDOWFORM_H
