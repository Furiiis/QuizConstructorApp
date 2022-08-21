#ifndef EDITABLEANSWERLISTMODEL_H
#define EDITABLEANSWERLISTMODEL_H

#include <answerlistmodel.h>

class EditableAnswerListModel : public AnswerListModel
{
    Q_OBJECT

public:
  EditableAnswerListModel();
  EditableAnswerListModel(const std::vector<Answer>& answers);

  virtual QVariant data(const QModelIndex& index, int role) const override;
  virtual Qt::ItemFlags flags(const QModelIndex& index) const override;
  virtual bool setData(const QModelIndex & index, const QVariant & value, int role) override;
  bool removeRows(int row, int count, const QModelIndex &parent) override;
  bool insertRows(int row, int count, const QModelIndex &parent) override;
};

#endif // EDITABLEANSWERLISTMODEL_H
