#include "taglistmodel.h"

TagListModel::TagListModel() : QAbstractListModel()
{

}

TagListModel::TagListModel(const std::vector<Tag> &tags) : QAbstractListModel()
{
    for(const auto& tag : tags)
    {
//        tags_.push_back({tag, Qt::Unchecked});
        tags_.push_back(tag);
    }
}

TagListModel::TagListModel(const TagListModel & tag)
{
     tags_ = tag.tags_;
}

int TagListModel::rowCount(const QModelIndex& parent) const
{
    return tags_.size();
}

//std::vector<Tag> TagListModel::getAnswers() const
//{
//    std::vector<Answer> answers;
//    for(const auto& answer : answers_)
//    {
//        answers.push_back(answer.first);
//    }
//    return answers;
//}

QVariant TagListModel::data(const QModelIndex& index, int role) const
{
  if(!checkIndex(index, CheckIndexOption::IndexIsValid))
      return QVariant::Invalid;
  if(role == Qt::DisplayRole)
    {
    return tags_[index.row()].name_;
    }
//  if (role == Qt::CheckStateRole)
//    {
//    return tags_[index.row()].state;
//    }

  return QVariant::Invalid;
}

Qt::ItemFlags TagListModel::flags(const QModelIndex& index) const
{
  Qt::ItemFlags returnFlags = QAbstractListModel::flags(index);
//    returnFlags |= Qt::ItemIsUserCheckable;

  return returnFlags;
}

bool TagListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
//    if (index.isValid() && role == Qt::EditRole) {
            QVariant qv = value;
            Tag tag = qv.value<Tag>();
            tags_.push_back(tag);
            emit dataChanged(index, index);
            return true;
//        }

            //        return false;
}

Tag TagListModel::takeItemTag(const QModelIndex &index) const
{
   if(!index.isValid())
   {
       assert(false);
   }

   return tags_[index.row()];
}

std::vector<Tag> TagListModel::takeItemTags(const QModelIndexList &indexlist)
{
    std::vector<Tag> takenTags;
    std::vector<int> takenRows;
    foreach(const QModelIndex & modelIndex, indexlist)
                    {
    //                    ui->selectedTagsListView->model()->insertRow(ui->selectedTagsListView->model()->rowCount(), modelIndex);
    //                    ui->selectedTagsListView->currentIndex();

    //                    ui->selectedTagsListView->model()->setData( QModelIndex(),
    //                                                               defaultTags->getItemTag(modelIndex));
                        takenRows.push_back(modelIndex.row());
                        takenTags.push_back(tags_[modelIndex.row()]);
                    }

    tags_.erase(std::remove_if(tags_.begin(),
                             tags_.end(),
                             [&takenTags](Tag tag){
        bool isIn = false;

        for(auto & x : takenTags)
        {
            if(x.name_ == tag.name_)
            {
                isIn = true;
                break;
            }
        }

        return isIn;
    }), tags_.end());

    return takenTags;
}

void TagListModel::pushBackItemTag(const Tag &tag)
{
    tags_.push_back(tag);
    //    emit Data
}

std::vector<Tag> TagListModel::getTags() const
{
    return tags_;
}
