#ifndef QUESTION_H
#define QUESTION_H

#include <QString>
#include <vector>

#include "answer.h"
#include "tag.h"

struct Question
{
//private:
//    Question() = default;
//    Question(const int number, const QString& question, const std::vector<Answer>& answers,
//             const QString& description, const QString& source, std::vector<Tag> tags)
//        : number_(number), question_(question), answers_(answers),
//          description_(description), source_(source), tags_(tags) {}
    int number_;
    QString question_;
    std::vector<Answer> answers_;
    QString description_;
    QString source_;
    std::vector<Tag> tags_;
};

#endif // QUESTION_H
