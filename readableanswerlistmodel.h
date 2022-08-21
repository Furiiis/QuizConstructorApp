#ifndef READABLEANSWERLISTMODEL_H
#define READABLEANSWERLISTMODEL_H

#include <answerlistmodel.h>

class ReadableAnswerListModel : public AnswerListModel
{
    Q_OBJECT

public:
  ReadableAnswerListModel();
  ReadableAnswerListModel(const std::vector<Answer>& answers);

  QVariant data(const QModelIndex& index, int role) const override;
  Qt::ItemFlags flags(const QModelIndex& index) const override;
  bool setData(const QModelIndex & index, const QVariant & value, int role) override;

public:
  void changeState();
  bool IsChecked() const;

private:
    enum State {CHECKUP, CLOSED};
    State state = CLOSED;
};

#endif // READABLEANSWERLISTMODEL_H
