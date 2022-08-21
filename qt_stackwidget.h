#ifndef QT_STACKWIDGET_H
#define QT_STACKWIDGET_H

#include <QMainWindow>
#include "ui_qt_stackwidget.h"
#include <QStackedWidget>

namespace Ui {
class MainWindow;
}

class Qt_StackWidget : public QMainWindow
{
   Q_OBJECT

public:
    static Qt_StackWidget& instance();
    void addCurrentWidget(QWidget* widget);

    ~Qt_StackWidget();
//    void createBaseMenu();
//    void changeCBA(QBaseWidget* current);
//    void createOptionsBackCBA(QBaseWidget* current);
//    void createOptionsExitCBA(QWidget* current);
//    QAction* back;

    public slots:
    void activatePerviousView();

private:
    explicit Qt_StackWidget(QWidget *parent = 0);

private:
    Ui::MainWindow* ui;
    QStackedWidget *stack;

//private slots:
//    void activeWidgetChanged(int index);
};

#endif // QT_STACKWIDGET_H
