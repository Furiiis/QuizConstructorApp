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
    void deleteQuestion(const int question_id);
    void deleteQuestions(const std::vector<int>& question_id);
    void updateQuestion(const Question& question);
    std::vector<Tag> getAllTags();
    std::vector<Tag> getQuestionTags(const int question_id);
    std::vector<Tag> getAllTagsExceptQuestions(const int question_id);

private:
    explicit DatabaseManager(QObject *parent = nullptr);
    Question hydrateQuestion(QSqlQuery& query);
    Answer hydrateAnswer(QSqlQuery& query);
    Tag hydrateTag(QSqlQuery &query);
    void addAnswers(const std::vector<Answer>& answers, const int question_index);
    void updateAnswers(const std::vector<Answer>& answers, const int question_index);
    void deleteAnswers(const std::vector<int>& id_answers);
    void updateTags(const std::vector<Tag>& tags_to_update, const int question_id);
    void deleteQuestionsTags(const std::vector<Tag>& tags_to_delete, const int question_id);
    void insertQuestionsTags(const std::vector<Tag>& tags_to_insert, const int question_id);

private:
    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_H
