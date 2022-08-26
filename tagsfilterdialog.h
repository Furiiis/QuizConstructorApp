#ifndef TAGSFILTERDIALOG_H
#define TAGSFILTERDIALOG_H

#include <QDialog>
#include "taglistmodel.h"
#include "databasemanager.h"
#include <QStandardItemModel>

namespace Ui {
class TagsFilterDialog;
}

class TagsFilterDialog : public QDialog
{
    Q_OBJECT

public:
//    explicit TagsFilterDialog(QWidget *parent = nullptr);
//    explicit TagsFilterDialog(QWidget *parent, const std::vector<Tag>& default_tags);
    explicit TagsFilterDialog(QWidget *parent = nullptr, const std::vector<Tag>& default_tags = {},
                              const std::vector<Tag>& selected_tags = {});
    ~TagsFilterDialog();

    std::vector<Tag> GetSelectedTags() const;

public slots:
//    void methods();
    void MoveTagsFromDefaultToSelected();
    void MoveTagsFromSelectedToDefault();
    void MoveAllTagsToSelected();
    void MoveAllTagsToDefault();

private:
    void UpdateViews() const;

private:
    TagListModel* defaultTags;
    TagListModel* selectedTags;
    Ui::TagsFilterDialog *ui;
};

#endif // TAGSFILTERDIALOG_H
