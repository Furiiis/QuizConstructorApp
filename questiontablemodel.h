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
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool insertRows(int row, int count, const QModelIndex &parent) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;
    bool removeMultipleRows(const QModelIndexList& rows_indexes,  const QModelIndex &parent);
    void addQuestion(const Question& question);
    Question GetQuestion(const QModelIndex &index) const;

private:
    std::vector<Question> _questions;
};

#endif // QUESTIONTABLEMODEL_H
