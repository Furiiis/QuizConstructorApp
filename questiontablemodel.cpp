#include "questiontablemodel.h"

QuestionTableModel::QuestionTableModel()
{

}

QuestionTableModel::QuestionTableModel(const std::vector<Question> &questions) :
    _questions(questions)
{

}

int QuestionTableModel::rowCount(const QModelIndex &parent) const
{
    return _questions.size();
}

int QuestionTableModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant QuestionTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
            return QVariant();
        }
        if (index.column() == 0) {
            return _questions[index.row()].number_;
        } else if (index.column() == 1) {
            return _questions[index.row()].question_;
        } else if (index.column() == 2) {
            return _questions[index.row()].description_;
        }  else if (index.column() == 3) {
            return _questions[index.row()].source_;
        }
        return QVariant();
}

QVariant QuestionTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            if (section == 0) {
                return QString("Id");
            } else if (section == 1) {
                return QString("Question");
            } else if (section == 2) {
                return QString("Description");
            } else if (section == 3) {
                return QString("Source");
            }
        }
    return QVariant();
}

Question QuestionTableModel::GetQuestion(const QModelIndex &index) const
{
    return _questions[index.row()];
}

bool QuestionTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole)
    {
        _questions[index.row()] = value.value<Question>();
        emit dataChanged(index, index);
        return true;
    }
    return false;
}


bool QuestionTableModel::insertRows(int row, int count, const QModelIndex &parent)
{

}

bool QuestionTableModel::removeRows(int row, int count, const QModelIndex &parent)
{

}
