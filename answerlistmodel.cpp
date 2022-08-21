#include <QBrush>
#include "answerlistmodel.h"

#include <sstream>

AnswerListModel::AnswerListModel() : QAbstractListModel()
{
//  std::vector<Answer> column1;
//  Answer item("в зависимости от возвращаемого значения foo", false);
//  answers_.push_back({item, Qt::Unchecked});
//  item.value = "в зависимости от пространства имен, где находится foo\nasdfadfadf/madsfadfasdf/masdfadfasdfasdfad\nadfadsf"; item.isRightAnswer = true;
//  answers_.push_back({item, Qt::Unchecked});
//  item.value = "fooo"; item.isRightAnswer = true;
//  answers_.push_back({item, Qt::Unchecked});
//  item.value = "govno1"; item.isRightAnswer = false;
//  answers_.push_back({item, Qt::Unchecked});
//  item.value = "govno2"; item.isRightAnswer = false;
//  answers_.push_back({item, Qt::Unchecked});
//  item.value = "govno3"; item.isRightAnswer = false;
//  answers_.push_back({item, Qt::Unchecked});
//  item.value = "govno4"; item.isRightAnswer = false;
//  answers_.push_back({item, Qt::Unchecked});
}

AnswerListModel::AnswerListModel(const std::vector<Answer> &answers) : QAbstractListModel()
{
    for(const auto& answer : answers)
    {
        if(answer.isRightAnswer)
            answers_.push_back({answer, Qt::Checked});
        else
            answers_.push_back({answer, Qt::Unchecked});
    }
}

int AnswerListModel::rowCount(const QModelIndex& parent) const
{
    return answers_.size();
}

std::vector<Answer> AnswerListModel::getAnswers() const
{
    std::vector<Answer> answers;
    for(const auto& answer : answers_)
    {
        answers.push_back(answer.first);
    }
    return answers;
}

//QVariant AnswerListModel::data(const QModelIndex& index, int role) const
//{
//  if(!checkIndex(index, CheckIndexOption::IndexIsValid))
//      return QVariant::Invalid;
//  if(role == Qt::DisplayRole)
//    {
//    return answers_[index.row()].first.value;
//    }
//  if (role == Qt::CheckStateRole)
//    {
//    return this->answers_[index.row()].second;
//    }
//  if (role == Qt::BackgroundColorRole)
//  {
//      if(state == CHECKUP){
//        if(this->answers_[index.row()].second == Qt::CheckState::Checked)
//             {
//                 if(this->answers_[index.row()].first.isRightAnswer)
//                     return QBrush(Qt::darkGreen);
//                 else return QBrush(Qt::red);
//             }
//        else
//        {
//            if(this->answers_[index.row()].first.isRightAnswer)
//                return QBrush(Qt::red);
//            else return QBrush(Qt::green);
//        }
//      }
//  }

//  return QVariant::Invalid;
//}

//Qt::ItemFlags AnswerListModel::flags(const QModelIndex& index) const
//{
//  Qt::ItemFlags returnFlags = QAbstractListModel::flags(index);
//    returnFlags |= Qt::ItemIsUserCheckable;

//  return returnFlags;
//}

//bool AnswerListModel::setData(const QModelIndex & index, const QVariant & value, int role)
//{
//    if (role == Qt::CheckStateRole)
//        {
//        this->answers_[index.row()].second = static_cast<Qt::CheckState>(value.toUInt());
//        }

//      emit dataChanged(index, index);
//    return true;
//}

//QHash<int, QByteArray> AnswerListModel::roleNames() const
//{
//    QHash<int, QByteArray> names;
//    names[IsRightAnswer] = "rightAnswer";
//    return names;
//}

//void AnswerListModel::changeState()
//{
//    state = CHECKUP;
//}
