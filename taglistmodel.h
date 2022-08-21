#ifndef TAGLISTMODEL_H
#define TAGLISTMODEL_H

#pragma once
#include <QAbstractListModel>
#include <vector>
#include <QItemSelection>
#include "tag.h"

class TagListModel : public QAbstractListModel
{
    Q_OBJECT

//    struct TagCheckBox
//    {
//        Tag tag;
//        Qt::CheckState state;
//    };

public:
  TagListModel();
  TagListModel(const std::vector<Tag>& tags);
  TagListModel(const TagListModel& tag);

  virtual int rowCount(const QModelIndex& parent) const;
  virtual QVariant data(const QModelIndex& index, int role) const;
  virtual Qt::ItemFlags flags(const QModelIndex& index) const;
//  virtual bool setData(const QModelIndex & index, const QVariant & value, int role);

//  std::vector<Tag> getTags() const;

//public slots:
//    void onSelectedItemsChanged(QItemSelection selected, QItemSelection deselected)
//    {
//        // Here is where your model receives the notification on what items are currently
//        // selected and deselected
//        if (!selected.empty())
//        {
//            int index = selected.first().indexes().first().row();
//            emit sendTag(tags_[index]);
//            emit moveSelectedTags(tags_[index]);
//        }


//    }
//    void GetSelectedTag(Tag item)
//    {
//        tags_.push_back(item);
//    }

//signals:
//    void moveSelectedTags(Tag item);
//    void sendTag(Tag item);

private:
  std::vector<Tag> tags_;

public:
  bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  Tag takeItemTag(const QModelIndex &index) const;
  std::vector<Tag> takeItemTags(const QModelIndexList& indexlist);
  void pushBackItemTag(const Tag& tag);
  std::vector<Tag> getTags() const;
};

Q_DECLARE_METATYPE(TagListModel)

#endif
