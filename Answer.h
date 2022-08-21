#ifndef ANSWER_H
#define ANSWER_H
#pragma once
#include <QString>

struct Answer
{
  Answer() = default;
//  Answer(const QString v, const bool trueness)
//      : value(v), isRightAnswer(trueness) {}
  Answer(const int answer_id, const QString v, const bool trueness)
      : id(answer_id), value(v), isRightAnswer(trueness) {}

  int id = 0;
  QString value;
  bool isRightAnswer;
};

#endif // ANSWER_H
