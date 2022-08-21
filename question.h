#ifndef QUESTION_H
#define QUESTION_H

#pragma once
#include <QString>
#include <vector>

#include "answer.h"

struct Question
{
    Question() = default;
    Question(const int number, const QString& question, const std::vector<Answer>& answers,
             const QString& description, const QString& source)
        : number_(number), question_(question), answers_(answers), description_(description), source_(source) {}
    int number_;
    QString question_;
    std::vector<Answer> answers_;
    QString description_;
    QString source_;
};

#endif // QUESTION_H
