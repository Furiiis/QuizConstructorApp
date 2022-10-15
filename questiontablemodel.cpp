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
    return 5;
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
//          else if (index.column() == 4) {
//            return
//        }

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
            } else if (section == 4) {
                return QString("Tags");
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
    beginInsertRows(parent, row+1, row + count);
    if(_questions.empty())
        _questions.push_back(Question());
    else
        _questions.insert(_questions.begin() + row + 1, Question());

    endInsertRows();
    return true;
}

bool QuestionTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    _questions.erase(_questions.begin() + row, _questions.begin() + row + count);
    endRemoveRows();
    return true;
}

bool QuestionTableModel::removeMultipleRows(const QModelIndexList &rows_indexes,  const QModelIndex &parent)
{
    int indexes_to_delete = 0;

    for(int i = rows_indexes.size() - 1; i >= 0; --i)
    {
        if(i == 0 || rows_indexes.at(i) != rows_indexes.at(i - 1))
        {
            if( !removeRows(rows_indexes.at(i).row(), indexes_to_delete + 1, parent))
            {
                return false;
            }
        }
        else
        {
            indexes_to_delete++;
        }
    }

    return true;
}

void QuestionTableModel::addQuestion(const Question &question)
{
    beginInsertRows(QModelIndex(), rowCount(QModelIndex()), rowCount(QModelIndex()));
    _questions.push_back(question);
    endInsertRows();
}
