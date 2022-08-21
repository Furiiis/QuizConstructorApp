#include "tagsfilterdialog.h"
#include "ui_tagsfilterdialog.h"


TagsFilterDialog::TagsFilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TagsFilterDialog)
{
    ui->setupUi(this);
    defaultTags = new TagListModel(DatabaseManager::instance().getAllTags());
    selectedTags = new TagListModel();
    ui->defaultTagsListView->setModel(defaultTags);
    ui->selectedTagsListView->setModel(selectedTags);

//    SelectionCopier* models_copier = new SelectionCopier(ui->defaultTagsListView, ui->selectedTagsListView);
//    connect(ui->moveToSelectedPushButton, SIGNAL(clicked()), models_copier, SLOT(copySelection()));

connect(ui->moveToSelectedPushButton, SIGNAL(clicked()), this, SLOT(methods()));

//    connect(ui->moveToSelectedPushButton, SIGNAL(clicked()),
//            ui->defaultTagsListView, SLOT(onSelectedItemsChanged(QItemSelection, QItemSelection)));
//    connect(ui->moveToSelectedPushButton, SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
//            m_myModel, SLOT(onSelectedItemsChanged(QItemSelection, QItemSelection)));
//    connect(ui->defaultTagsListView, SIGNAL(sendTag(Tag item)),
//            ui->selectedTagsListView, SLOT(GetSelectedTag(Tag item)));
}

TagsFilterDialog::~TagsFilterDialog()
{
    delete ui;
}

std::vector<Tag> TagsFilterDialog::GetSelectedTags() const
{
    return selectedTags->getTags();
}

void TagsFilterDialog::methods()
{
    QItemSelectionModel * selectionModel = ui->defaultTagsListView->selectionModel();

            if(selectionModel->hasSelection())
            {
                foreach(const QModelIndex & modelIndex, selectionModel->selectedIndexes())
                {
//                    ui->selectedTagsListView->model()->insertRow(ui->selectedTagsListView->model()->rowCount(), modelIndex);
//                    ui->selectedTagsListView->currentIndex();

//                    ui->selectedTagsListView->model()->setData( QModelIndex(),
//                                                               defaultTags->getItemTag(modelIndex));
                    selectedTags->pushBackItemTag(defaultTags->takeItemTag(modelIndex));
                    ui->selectedTagsListView->doItemsLayout();
                }
            }
            defaultTags->takeItemTags(selectionModel->selectedIndexes());
}
