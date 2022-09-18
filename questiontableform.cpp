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
    connect(ui->updatePushButton, SIGNAL(clicked()), this, SLOT(UpdateModel()));
    connect(ui->deletePushButton, SIGNAL(clicked()), this, SLOT(RemoveQuestion()));
    connect(ui->addPushButton, SIGNAL(clicked()), this, SLOT(AddQuestion()));
    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(ContexMenuRequested(QPoint)));
}

QuestionTableForm::~QuestionTableForm()
{
    delete ui;
}

void QuestionTableForm::Back() const
{
    Qt_StackWidget::instance().activatePerviousView();
}

void QuestionTableForm::UpdateModel()
{
    question_model = new QuestionTableModel(DatabaseManager::instance().getAllQuestions());
    ui->tableView->setModel(question_model);
}

void QuestionTableForm::EditQuestion()
{
    /* Также создаем диалог и подключаем его сигнал завершения работы
     * к слоту обновления вида модели представления данных, но передаём
     * в качестве параметров строку записи
     * */
    QModelIndex index = ui->tableView->selectionModel()->currentIndex();

    UpdateQuestionDialog *updateDialog = new UpdateQuestionDialog(
                question_model->GetQuestion(ui->tableView->selectionModel()->currentIndex()));

    connect(updateDialog, &UpdateQuestionDialog::QuestionDataChanged, [&](const Question& question)
    {
        question_model->setData(index, QVariant::fromValue<Question>(question), Qt::EditRole);
    });
    /* Выполняем запуск диалогового окна
     * */
    updateDialog->exec();
}

void QuestionTableForm::AddQuestion()
{
    AddQuestionDialog *addDialog = new AddQuestionDialog();

    connect(addDialog, &AddQuestionDialog::QuestionAdded, [&](const Question& question)
    {
//          ui->tableView->model()->insertRow(question_model->rowCount(QModelIndex())-1);
//          question_model->setData(question_model->index(ui->tableView->model()->rowCount() - 1, 1),
//                                        QVariant::fromValue<Question>(question), Qt::EditRole);
          question_model->addQuestion(question);
    });

    addDialog->exec();
}

void QuestionTableForm::RemoveQuestion()
{
    /* Выясняем, какая из строк была выбрана
         * */
    int selected_row = ui->tableView->selectionModel()->currentIndex().row();
    int selected_questions_count = ui->tableView->selectionModel()->selectedRows().size();
    /* Проверяем, что строка была действительно выбрана
     * */
    if(selected_row >= 0){
        /* Задаём вопрос, стоит ли действительно удалять запись.
         * При положительном ответе удаляем запись
         * */
        if (QMessageBox::warning(this,
                                 trUtf8("Удаление вопроса"),
                                 trUtf8("Вы уверены, что хотите удалить этот вопрос?"),
                                 QMessageBox::No | QMessageBox::Yes) == QMessageBox::No)
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
            question_model->removeRows(selected_row, selected_questions_count, QModelIndex());
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
