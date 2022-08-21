#include "qt_stackwidget.h"
#include "testwindowform.h"
#include "databasemanager.h"
#include "ui_qt_stackwidget.h"
#include "menuform.h"

Qt_StackWidget &Qt_StackWidget::instance()
{
    static Qt_StackWidget *instance = new Qt_StackWidget();
    return *instance;
}

Qt_StackWidget::Qt_StackWidget(QWidget *parent) : QMainWindow(parent)
{
    ui = new Ui::MainWindow;
    ui->setupUi(this);
    DatabaseManager *databaseManager = &DatabaseManager::instance();

    //TestWindowForm form(nullptr, databaseManager->getQuestion(2));
    stack = new QStackedWidget();
    addCurrentWidget(new MenuForm());
    ui->stackedWidget = stack;

//       back = NULL;
//       stack = new QStackedWidget();
//       QObject::connect(stack, SIGNAL(currentChanged(int)),this, SLOT(activeWidgetChanged(int)));
//       stack->addWidget(new Homewidget(stack));
    setCentralWidget(stack);
}

void Qt_StackWidget::addCurrentWidget(QWidget *widget)
{
    stack->addWidget(widget);
    stack->setCurrentWidget(widget);
}

Qt_StackWidget::~Qt_StackWidget()
{

}

void Qt_StackWidget::activatePerviousView()
{
    if(stack->count() <= 1) assert(false);

    QWidget* widget = stack->currentWidget();

    stack->removeWidget(widget);
    delete widget;
}
