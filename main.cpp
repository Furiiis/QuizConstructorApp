#include "testwindowform.h"

#include <QApplication>
#include <QWidget>
#include <QFrame>
#include <QGridLayout>

#include "databasemanager.h"
#include "qt_stackwidget.h"

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);
//  DatabaseManager *databaseManager = &DatabaseManager::instance();

//  TestWindowForm form(nullptr, databaseManager->getQuestion(2));
//  form.show();

  Qt_StackWidget* qt_st = &Qt_StackWidget::instance();
  qt_st->show();
  return app.exec();
}
