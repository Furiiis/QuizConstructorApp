#include "tagsfilterdialog.h"
#include "ui_tagsfilterdialog.h"

namespace  {
    void moveSelectedTagItems(TagListModel* from_list,
                          TagListModel* to_list, QItemSelectionModel* selectionModel)
{
            if(selectionModel->hasSelection())
            {
                foreach(const QModelIndex & modelIndex, selectionModel->selectedIndexes())
                {
                    to_list->pushBackItemTag(from_list->takeItemTag(modelIndex));
                }
            }
            from_list->takeItemTags(selectionModel->selectedIndexes());
}

     void moveAllTagItems(TagListModel* from_list,  TagListModel* to_list)
     {
         foreach(const Tag& tag, from_list->getTags())
         {
             to_list->pushBackItemTag(tag);
         }

         from_list->clear();
     }
}

//TagsFilterDialog::TagsFilterDialog(QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::TagsFilterDialog)
//{
//    ui->setupUi(this);
//    defaultTags = new TagListModel(DatabaseManager::instance().getAllTags());
//    selectedTags = new TagListModel();
//    ui->defaultTagsListView->setModel(defaultTags);
//    ui->selectedTagsListView->setModel(selectedTags);

//connect(ui->moveToSelectedPushButton, SIGNAL(clicked()), this,
//        SLOT(MoveTagsFromDefaultToSelected()));
//connect(ui->moveToDefaultPushButton, SIGNAL(clicked()), this,
//        SLOT(MoveTagsFromSelectedToDefault()));
//connect(ui->moveAllToSelectedPushButton, SIGNAL(clicked()), this,
//        SLOT(MoveAllTagsToSelected()));
//connect(ui->moveAllToDefaultPushButton, SIGNAL(clicked()), this,
//        SLOT(MoveAllTagsToDefault()));
//}

//TagsFilterDialog::TagsFilterDialog(QWidget *parent, const std::vector<Tag> &default_tags) :
//    QDialog(parent),
//    ui(new Ui::TagsFilterDialog)
//{
//    ui->setupUi(this);
//    defaultTags = new TagListModel(default_tags);
//    selectedTags = new TagListModel();
//    ui->defaultTagsListView->setModel(defaultTags);
//    ui->selectedTagsListView->setModel(selectedTags);

//connect(ui->moveToSelectedPushButton, SIGNAL(clicked()), this,
//        SLOT(MoveTagsFromDefaultToSelected()));
//connect(ui->moveToDefaultPushButton, SIGNAL(clicked()), this,
//        SLOT(MoveTagsFromSelectedToDefault()));
//connect(ui->moveAllToSelectedPushButton, SIGNAL(clicked()), this,
//        SLOT(MoveAllTagsToSelected()));
//connect(ui->moveAllToDefaultPushButton, SIGNAL(clicked()), this,
//        SLOT(MoveAllTagsToDefault()));
//}

//TagsFilterDialog::TagsFilterDialog(QWidget *parent, const std::vector<Tag> &default_tags,
//                                   const std::vector<Tag> &selected_tags)
//{
//    ui->setupUi(this);
//    defaultTags = new TagListModel(default_tags);
//    selectedTags = new TagListModel();
//    ui->defaultTagsListView->setModel(defaultTags);
//    ui->selectedTagsListView->setModel(selectedTags);

//connect(ui->moveToSelectedPushButton, SIGNAL(clicked()), this,
//        SLOT(MoveTagsFromDefaultToSelected()));
//connect(ui->moveToDefaultPushButton, SIGNAL(clicked()), this,
//        SLOT(MoveTagsFromSelectedToDefault()));
//connect(ui->moveAllToSelectedPushButton, SIGNAL(clicked()), this,
//        SLOT(MoveAllTagsToSelected()));
//connect(ui->moveAllToDefaultPushButton, SIGNAL(clicked()), this,
//        SLOT(MoveAllTagsToDefault()));
//}

TagsFilterDialog::TagsFilterDialog(QWidget *parent, const std::vector<Tag>& default_tags,
                          const std::vector<Tag>& selected_tags) :
        QDialog(parent),
        ui(new Ui::TagsFilterDialog)
{
    ui->setupUi(this);
    defaultTags = new TagListModel(default_tags);
    selectedTags = new TagListModel(selected_tags);
    ui->defaultTagsListView->setModel(defaultTags);
    ui->selectedTagsListView->setModel(selectedTags);

connect(ui->moveToSelectedPushButton, SIGNAL(clicked()), this,
        SLOT(MoveTagsFromDefaultToSelected()));
connect(ui->moveToDefaultPushButton, SIGNAL(clicked()), this,
        SLOT(MoveTagsFromSelectedToDefault()));
connect(ui->moveAllToSelectedPushButton, SIGNAL(clicked()), this,
        SLOT(MoveAllTagsToSelected()));
connect(ui->moveAllToDefaultPushButton, SIGNAL(clicked()), this,
        SLOT(MoveAllTagsToDefault()));
}

TagsFilterDialog::~TagsFilterDialog()
{
    delete ui;
}

std::vector<Tag> TagsFilterDialog::GetSelectedTags() const
{
    return selectedTags->getTags();
}

void TagsFilterDialog::MoveTagsFromDefaultToSelected()
{
    moveSelectedTagItems(defaultTags, selectedTags,
                         ui->defaultTagsListView->selectionModel());
    UpdateViews();
}

void TagsFilterDialog::MoveTagsFromSelectedToDefault()
{
    moveSelectedTagItems(selectedTags, defaultTags,
                         ui->selectedTagsListView->selectionModel());
    UpdateViews();
}

void TagsFilterDialog::MoveAllTagsToSelected()
{
    moveAllTagItems(defaultTags, selectedTags);
    UpdateViews();
}

void TagsFilterDialog::MoveAllTagsToDefault()
{
    moveAllTagItems(selectedTags, defaultTags);
    UpdateViews();
}

void TagsFilterDialog::UpdateViews() const
{
    ui->selectedTagsListView->doItemsLayout();
    ui->defaultTagsListView->doItemsLayout();
}
