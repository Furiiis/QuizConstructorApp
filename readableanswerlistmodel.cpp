#include "readableanswerlistmodel.h"
#include <QBrush>

ReadableAnswerListModel::ReadableAnswerListModel()
{

}

ReadableAnswerListModel::ReadableAnswerListModel(const std::vector<Answer> &answers)
    : AnswerListModel(answers)
{

}

QVariant ReadableAnswerListModel::data(const QModelIndex &index, int role) const
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
    if (role == Qt::BackgroundColorRole)
    {
        if(state == CHECKUP){
          if(this->answers_[index.row()].second == Qt::CheckState::Checked)
               {
                   if(this->answers_[index.row()].first.isRightAnswer)
                       return QBrush(Qt::darkGreen);
                   else return QBrush(Qt::red);
               }
          else
          {
              if(this->answers_[index.row()].first.isRightAnswer)
                  return QBrush(Qt::red);
              else return QBrush(Qt::green);
          }
        }
    }

    return QVariant::Invalid;
}

Qt::ItemFlags ReadableAnswerListModel::flags(const QModelIndex& index) const
{
  Qt::ItemFlags returnFlags = QAbstractListModel::flags(index);
    returnFlags |= Qt::ItemIsUserCheckable;

  return returnFlags;
}

bool ReadableAnswerListModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (role == Qt::CheckStateRole)
        {
        this->answers_[index.row()].second = static_cast<Qt::CheckState>(value.toUInt());
        }

      emit dataChanged(index, index);
    return true;
}

void ReadableAnswerListModel::changeState()
{
    state = CHECKUP;
}

bool ReadableAnswerListModel::IsChecked() const
{
    if(state == State::CHECKUP) return true;
    else return false;
}
