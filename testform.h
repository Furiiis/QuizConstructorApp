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
    void CheckQuestionState() const;

private:
    Ui::TestForm *ui;
    TestWindowForm* questionWidget;
    TestSessionData _sessionData;
    std::vector<Question>::iterator current_question = _sessionData.questions.begin();
};

#endif // TESTFORM_H
