#ifndef QLISTMODEL_H
#define QLISTMODEL_H

#pragma once
#include <QAbstractListModel>
#include <vector>
#include "answer.h"

class AnswerListModel : public QAbstractListModel
{
    Q_OBJECT

public:
  AnswerListModel();
  AnswerListModel(const std::vector<Answer>& answers);

  virtual int rowCount(const QModelIndex& parent) const;
//  virtual QVariant data(const QModelIndex& index, int role) const = 0;
//  virtual Qt::ItemFlags flags(const QModelIndex& index) const = 0;
//  virtual bool setData(const QModelIndex & index, const QVariant & value, int role);

  std::vector<Answer> getAnswers() const;

protected:
  std::vector<std::pair<Answer, Qt::CheckState>> answers_;
};

//Q_DECLARE_METATYPE(AnswerListModel)

#endif
