#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#pragma once

#include <QObject>
#include <QSqlDatabase>
#include <vector>
#include "question.h"
#include "tag.h"

class DatabaseManager : public QObject
{
    Q_OBJECT

public:
    static DatabaseManager& instance();
    ~DatabaseManager();

public:
    bool openDB();
    bool closeDB();
//    std::vector<Question> getRandomQuestions();
    std::vector<Question> getAllQuestions();
    std::vector<Question> getQuestions(const int limit);
    std::vector<Question> getQuestions(const int limit, const std::vector<Tag>& tags);
    Question getQuestion(const int id);
    std::vector<Answer> getAnswers(const int id);
    void addQuestion(const Question& question);
    void deleteQuestion(const int id);
    void updateQuestion(const Question& question);
    std::vector<Tag> getAllTags();

private:
    explicit DatabaseManager(QObject *parent = nullptr);
    Question hydrateQuestion(QSqlQuery& query);
    Answer hydrateAnswer(QSqlQuery& query);
    Tag hydrateTag(QSqlQuery &query);
    void addAnswers(const std::vector<Answer>& answers, const int question_index);
    void updateAnswers(const std::vector<Answer>& answers, const int question_index);

private:
    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_H
