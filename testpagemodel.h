#ifndef TESTWINDOW_H
#define TESTWINDOW_H
//DEPRICATED FILE
#pragma once

#include <QLabel>
#include <QPushButton>
#include <QAbstractListModel>
#include <QVector>
#include <QVariant>
#include "readableanswerlistmodel.h"


struct TestPageModel
{
    TestPageModel();
    QString question_;
    ReadableAnswerListModel* answers_list_;
    QString answer_;
    QString description_;
    QString source_;

//    QVariant At(const size_t index) const
//    {
//        switch(index)
//        {
//        case 0: return question_;
//        case 1: return QVariant::fromValue<AnswerListModel*>(answers_list_);
//        case 2: return answer_;
//        case 3: return description_;
//        case 4: return source_;
//        }

//        return QVariant::Invalid;
//    }
};

//class TestPageModel : public QAbstractListModel
//{
//    Q_OBJECT
//public:
//    explicit TestPageModel();

//    int rowCount(const QModelIndex& parent) const;
//    QVariant data(const QModelIndex& index, int role) const;
//    Qt::ItemFlags flags(const QModelIndex& index) const;
////    QLabel* GetQuestion() const;
////    QLabel* GetAnswer() const;
////    QLabel* GetDescription() const;
////    QLabel* GetSourceLink() const;
////    AnswerListModel* GetAnswers() const;
////    QPushButton* GetNextBtn() const;
////    QPushButton* GetCheckBtn() const;

//private:
//    TestPageItems items;
////    QLabel* question_;
////    QLabel* answer_;
////    QLabel* description_;
////    QLabel* source_link_;
////    AnswerListModel* answers_list_;
//////    QPushButton* next_btn_;
////    QPushButton* check_btn_;
//};

#endif // TESTWINDOW_H
