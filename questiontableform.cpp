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

    this->UpdateModel();
}

void QuestionTableForm::RemoveQuestion()
{
    /* Выясняем, какая из строк была выбрана
         * */
    QModelIndexList selected_indexes = ui->tableView->selectionModel()->selectedIndexes();
    qSort(selected_indexes);
    std::vector<int> question_indexes;
    QModelIndexList selected_rows;
    for(const auto & index : selected_indexes)
    {
        if(selected_rows.empty() || (selected_rows.back().row() != index.row()))
        {
            selected_rows.push_back(index);
            question_indexes.push_back(question_model->GetQuestion(index).number_);
        }
    }

//    int selected_row = ui->tableView->selectionModel()->currentIndex().row();
    if (QMessageBox::warning(this,
                             trUtf8("Удаление вопроса"),
                             trUtf8("Вы уверены, что хотите удалить этот вопрос?"),
                             QMessageBox::No | QMessageBox::Yes) == QMessageBox::No)
    {
        return;
    } else {
        DatabaseManager::instance().deleteQuestions(question_indexes);
        question_model->removeMultipleRows(selected_rows, QModelIndex());
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
