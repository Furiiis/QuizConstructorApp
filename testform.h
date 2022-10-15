#ifndef TESTFORM_H
#define TESTFORM_H

#include <QWidget>
#include "testwindowform.h"
#include "testsessiondata.h"

namespace Ui {
class TestForm;
}

class TestForm : public QWidget
{
    Q_OBJECT

public:
    explicit TestForm(const TestSessionData& sessionData, QWidget *parent = nullptr);
    ~TestForm();

public slots:
    void BackToMenu() const;
    void NextQuestion();

private slots:
    void EnableNextButton() const;

private:
    bool IsNextQuestionLast() const; //RENAME

private:
    Ui::TestForm *ui;
    TestWindowForm* questionWidget;
    TestSessionData _sessionData;
    //std::vector<Question>::iterator current_question = _sessionData.questions.begin();
    int current_question_index = 0;
};

#endif // TESTFORM_H
