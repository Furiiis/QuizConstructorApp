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
    explicit TagsFilterDialog(QWidget *parent = nullptr);
    ~TagsFilterDialog();

    std::vector<Tag> GetSelectedTags() const;

public slots:
    void methods();

private:
    TagListModel* defaultTags;
    TagListModel* selectedTags;
    Ui::TagsFilterDialog *ui;
};

#endif // TAGSFILTERDIALOG_H
