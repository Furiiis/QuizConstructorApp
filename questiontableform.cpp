#include "questiontableform.h"
#include "updatequestiondialog.h"
#include "ui_questiontableform.h"
#include "qt_stackwidget.h"
#include <QMessageBox>

QuestionTableForm::QuestionTableForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuestionTableForm)
{
    ui->setupUi(this);
    question_model = new QuestionTableModel(DatabaseManager::instance().getAllQuestions());
    ui->tableView->setModel(question_model);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(EditQuestion()));
    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(ContexMenuRequested(QPoint)));
}

QuestionTableForm::~QuestionTableForm()
{
    delete ui;
    delete question_model;
}

void QuestionTableForm::Back() const
{
    Qt_StackWidget::instance().activatePerviousView();
}

void QuestionTableForm::UpdateModel()
{

}

void QuestionTableForm::EditQuestion()
{
    /* Также создаем диалог и подключаем его сигнал завершения работы
     * к слоту обновления вида модели представления данных, но передаём
     * в качестве параметров строку записи
     * */
    UpdateQuestionDialog *updateDialog = new UpdateQuestionDialog(
                question_model->GetQuestion(ui->tableView->selectionModel()->currentIndex()));
    connect(updateDialog, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));

    /* Выполняем запуск диалогового окна
     * */
    updateDialog->exec();
}

void QuestionTableForm::RemoveQuestion()
{
    /* Выясняем, какая из строк была выбрана
         * */
    int row = ui->tableView->selectionModel()->currentIndex().row();
    /* Проверяем, что строка была действительно выбрана
     * */
    if(row >= 0){
        /* Задаём вопрос, стоит ли действительно удалять запись.
         * При положительном ответе удаляем запись
         * */
        if (QMessageBox::warning(this,
                                 trUtf8("Удаление вопроса"),
                                 trUtf8("Вы уверены, что хотите удалить этот вопрос?"),
                                 QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
        {
            /* При отрицательном ответе делаем откат действий
             * и закрываем диалог без удаления записи
             * */
           // QSqlDatabase::database().rollback();
            return;
        } else {
            /* В противном случае производим удаление записи.
             * При успешном удалении обновляем таблицу.
             * */
//            if(!modelDevice->removeRow(row)){
//                QMessageBox::warning(this,trUtf8("Уведомление"),
//                                     trUtf8("Не удалось удалить запись\n"
//                                            "Возможно она используется другими таблицами\n"
//                                            "Проверьте все зависимости и повторите попытку"));
//            }
//            modelDevice->select();
//            ui->deviceTableView->setCurrentIndex(modelDevice->index(-1, -1));
            DatabaseManager::instance().deleteQuestion(question_model->GetQuestion(ui->tableView->selectionModel()->currentIndex()).number_);
            question_model->removeRow(row);

//            question_model->select();
            ui->tableView->setCurrentIndex(question_model->index(-1, -1));
        }
}
}

void QuestionTableForm::ContexMenuRequested(QPoint pos)
{
    QMenu * menu = new QMenu(this);
    /* Создаём действия для контекстного меню */
    QAction * editDevice = new QAction(trUtf8("Редактировать"), this);
    QAction * deleteDevice = new QAction(trUtf8("Удалить"), this);
    /* Подключаем СЛОТы обработчики для действий контекстного меню */
    connect(editDevice, SIGNAL(triggered()), this, SLOT(EditQuestion()));     // Обработчик вызова диалога редактирования
    connect(deleteDevice, SIGNAL(triggered()), this, SLOT(RemoveQuestion())); // Обработчик удаления записи
    /* Устанавливаем действия в меню */
    menu->addAction(editDevice);
    menu->addAction(deleteDevice);
    /* Вызываем контекстное меню */
    menu->popup(ui->tableView->viewport()->mapToGlobal(pos));
}
