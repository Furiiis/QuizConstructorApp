#include "testpagemodel.h"
//DEPRICATED FILE
TestPageModel::TestPageModel()
{

    answers_list_ = new ReadableAnswerListModel();
    QString lyrics = "Who doesn't long for someone to hold\n\
    Who knows how to love you without being told\n\
    Somebody tell me why I'm on my own\n\
    If there's a soulmate for everyone\n\
    \n\
    Here we are again, circles never end\n\
    How do I find the perfect fit\n\
    There's enough for everyone\n\
    But I'm still waiting in line\n\
    \n\
    Who doesn't long for someone to hold\n\
    Who knows how to love you without being told\n\
    Somebody tell me why I'm on my own\n\
    If there's a soulmate for everyone"
            "Who doesn't long for someone to hold\n\
            Who knows how to love you without being told\n\
            Somebody tell me why I'm on my own\n\
            If there's a soulmate for everyone\n\
            \n\
            Here we are again, circles never end\n\
            How do I find the perfect fit\n\
            There's enough for everyone\n\
            But I'm still waiting in line\n\
            \n\
            Who doesn't long for someone to hold\n\
            Who knows how to love you without being told\n\
            Somebody tell me why I'm on my own\n\
            If there's a soulmate for everyone"
            "Who doesn't long for someone to hold\n\
            Who knows how to love you without being told\n\
            Somebody tell me why I'm on my own\n\
            If there's a soulmate for everyone\n\
            \n\
            Here we are again, circles never end\n\
            How do I find the perfect fit\n\
            There's enough for everyone\n\
            But I'm still waiting in line\n\
            \n\
            Who doesn't long for someone to hold\n\
            Who knows how to love you without being told\n\
            Somebody tell me why I'm on my own\n\
            If there's a soulmate for everyone";
    QString answer_str = "F::foo()\nD:fpp()";
    QString description_str = "Тк аd const вызывается копирующий конструктор";
    QString source_link_str = "Базовый курс C++ (MIPT, ILab). Lecture 5. RAII и перемещение\nhttps://www.youtube.com/watch?v=_mLDaU4wSOo";

    question_ = lyrics;
    answer_ = answer_str;
    description_ = description_str;
    source_ = source_link_str;
//    check_btn_ = new QPushButton("Check");
//    next_btn_ = new QPushButton("Next");
//    next_btn_->setEnabled(false);
}



//int TestPageModel::rowCount(const QModelIndex& parent) const //magic_number - change
//{
//  return 5;
//}

//QVariant TestPageModel::data(const QModelIndex& index, int role) const
//{
//  if(!checkIndex(index, CheckIndexOption::IndexIsValid))
//      return QVariant::Invalid;
//  if(role == Qt::DisplayRole)
//    {
//      return items.At(index.row());
//    }
//  return QVariant::Invalid;
//}

//Qt::ItemFlags TestPageModel::flags(const QModelIndex& index) const
//{
//  Qt::ItemFlags returnFlags = QAbstractListModel::flags(index);
//    returnFlags |= Qt::ItemIsEnabled;

//  return returnFlags;
//}



////QLabel* TestPageModel::GetQuestion() const
////{
////    return question_;
////}

////AnswerListModel* TestPageModel::GetAnswers() const
////{
////    return answers_list_;
////}

////QPushButton* TestPageModel::GetNextBtn() const
////{
////    return next_btn_;
////}

////QPushButton* TestPageModel::GetCheckBtn() const
////{
////    return check_btn_;
////}


////TestPageModel::~TestPageModel()
////{
////    delete question_;
////    delete answers_list_;
////}
