#include "editableanswerlistmodel.h"

EditableAnswerListModel::EditableAnswerListModel()
{

}

EditableAnswerListModel::EditableAnswerListModel(const std::vector<Answer> &answers)
    : AnswerListModel(answers, true)
{

}

QVariant EditableAnswerListModel::data(const QModelIndex &index, int role) const
{
    if(!checkIndex(index, CheckIndexOption::IndexIsValid))
        return QVariant::Invalid;
    if(role == Qt::DisplayRole)
      {
      return answers_[index.row()].first.value;
      }
    if (role == Qt::CheckStateRole)
      {
      return this->answers_[index.row()].second;
      }
//    if (role == Qt::BackgroundColorRole)
//    {
//        if(state == CHECKUP){
//          if(this->answers_[index.row()].second == Qt::CheckState::Checked)
//               {
//                   if(this->answers_[index.row()].first.isRightAnswer)
//                       return QBrush(Qt::darkGreen);
//                   else return QBrush(Qt::red);
//               }
//          else
//          {
//              if(this->answers_[index.row()].first.isRightAnswer)
//                  return QBrush(Qt::red);
//              else return QBrush(Qt::green);
//          }
//        }
//    }

    return QVariant::Invalid;
}

Qt::ItemFlags EditableAnswerListModel::flags(const QModelIndex& index) const
{
  Qt::ItemFlags returnFlags = QAbstractListModel::flags(index);
    returnFlags |= Qt::ItemIsUserCheckable | Qt::ItemIsSelectable
                | Qt::ItemIsEditable;

  return returnFlags;
}

bool EditableAnswerListModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (role == Qt::CheckStateRole)
    {
        this->answers_[index.row()].second = static_cast<Qt::CheckState>(value.toUInt());
        this->answers_[index.row()].first.isRightAnswer = value.toUInt();
    }
    if(role == Qt::EditRole)
    {
        answers_[index.row()].first.value = value.toString();
    }

      emit dataChanged(index, index);
    return true;
}

bool EditableAnswerListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(answers_.empty()) return false;
    if(answers_.erase(answers_.begin() + row) == answers_.end())
        return false;
    return true;
}

bool EditableAnswerListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    answers_.insert(answers_.begin() + row + 1, {Answer(), Qt::Unchecked});
}
