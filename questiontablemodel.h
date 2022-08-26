#ifndef QUESTIONTABLEMODEL_H
#define QUESTIONTABLEMODEL_H

#include <QAbstractTableModel>
#include <vector>

#include "question.h"


class QuestionTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    QuestionTableModel();
    QuestionTableModel(const std::vector<Question>& questions);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Question GetQuestion(const QModelIndex &index) const;

private:
    std::vector<Question> _questions;



    // QAbstractItemModel interface
public:
    bool setData(const QModelIndex &index, const QVariant &value, int role);
};

#endif // QUESTIONTABLEMODEL_H
