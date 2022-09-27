#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QApplication>
#include <QDebug>
#include <iostream>

DatabaseManager &DatabaseManager::instance()
{
    static DatabaseManager *instance = new DatabaseManager();
    return *instance;
}

bool DatabaseManager::openDB()
{
    std::cout << "[DatabaseManager] openDB" << std::endl;
    if (QSqlDatabase::contains("AppTestDbConnection"))
    {
        m_db = QSqlDatabase::database("AppTestDbConnection");
    }
    else
    {
       m_db = QSqlDatabase::addDatabase("QSQLITE", "AppTestDbConnection");
    }

    QString l_dbPath = qApp->property("filesPath").toString() + "database.db";
        m_db.setDatabaseName(l_dbPath);

        if (!m_db.open()) {
            std::cerr << "Cannot m_db.open()" << std::endl;
            return false;
        }

        QSqlQuery l_query(m_db);
        l_query.prepare("PRAGMA foreign_keys = ON");

        if (!l_query.exec()) {
            std::cerr << "In openDB:" << std::endl;

//            std::cerr << l_query.lastError().text() << std::endl;
            return false;
        }

        return true;
}

bool DatabaseManager::closeDB()
{
    std::cout << "[DatabaseManager] Close database" << std::endl;
    m_db.close();
    return true;
}

std::vector<Question> DatabaseManager::getAllQuestions()
{
    QSqlQuery l_query(m_db);
    l_query.prepare("SELECT * "
                    "FROM questions");

    if (!l_query.exec())
    {
       QString err_str = l_query.lastError().text();
       std::cerr << "Error in DatabaseManager::getAllQuestions()"<< std::endl;
//        Macaw::DEBUG(l_query.lastError().text());
    }

    std::vector<Question> questions;

    while(l_query.next())
    {
        questions.push_back(hydrateQuestion(l_query));
        questions.back().tags_ = getQuestionTags(questions.back().number_);
    }

    return questions;
}

std::vector<Question> DatabaseManager::getQuestions(const int limit)
{
    QSqlQuery l_query(m_db);
    l_query.prepare("SELECT * "
                    "FROM questions "
                    "ORDER BY RANDOM()  "
                    "LIMIT :limit");
    l_query.bindValue(":limit", limit);

    if (!l_query.exec())
    {
       QString err_str = l_query.lastError().text();
       std::cerr << "Error in DatabaseManager::getQuestions(const int limit)" << std::endl;
    }

    std::vector<Question> questions;

    while(l_query.next())
    {
        questions.push_back(hydrateQuestion(l_query));
        questions.back().tags_ = getQuestionTags(questions.back().number_);
    }

    return questions;
}

std::vector<Question> DatabaseManager::getQuestions(const int limit, const std::vector<Tag> &tags)
{
    QSqlQuery l_query(m_db);

    QStringList idstrings;
    foreach(Tag tag, tags) {
        idstrings << QString::number(tag.id);
    }
//    QString idlist = idstrings.join(" , ");

    l_query.prepare(QString("SELECT * FROM questions "
                    "where questionNumber in "
                    "( select DISTINCT question_id from questions_tags_mapper  "
                    "where tag_id in (%1) ) "
                    "limit :limit;").arg(idstrings.join(" , ")));

    l_query.bindValue(":limit", limit);

    if (!l_query.exec())
    {
       QString err_str = l_query.lastError().text();
       std::cerr << "Error in DatabaseManager::getQuestions(const int limit, const std::vector<Tag> &tags)" << std::endl;
    }

    std::vector<Question> questions;

    while(l_query.next())
    {
        questions.push_back(hydrateQuestion(l_query));
        questions.back().tags_ = getQuestionTags(questions.back().number_);
    }

    return questions;
}

Question DatabaseManager::getQuestion(const int id)
{
    QSqlQuery l_query(m_db);
    l_query.prepare("SELECT * "
                    "FROM questions "
                    "WHERE questionNumber = :id");

    l_query.bindValue(":id", id);

    if (!l_query.exec())
    {
       QString err_str = l_query.lastError().text();
       std::cerr << "Error in DatabaseManager::getQuestion(const int id)"<< std::endl;
//        Macaw::DEBUG(l_query.lastError().text());
    }
    if(!l_query.first()) return Question();
    Question question = hydrateQuestion(l_query);
    question.tags_ = getQuestionTags(question.number_);
    return question;
}

std::vector<Answer> DatabaseManager::getAnswers(const int id)
{
    std::vector<Answer> l_answersvec;
    QSqlQuery l_query(m_db);
    l_query.prepare("SELECT * "
                    "FROM answers "
                    "WHERE questionNumber = :id "
                    "ORDER BY RANDOM()");

    l_query.bindValue(":id", id);

    if (!l_query.exec())
    {
       std::cerr << "Error in DatabaseManager::getAnswers(const int id)" << std::endl;
//        Macaw::DEBUG(l_query.lastError().text());
    }


        while(l_query.next())
        {
            l_answersvec.push_back(hydrateAnswer(l_query));
        }

        return l_answersvec;
}

void DatabaseManager::addQuestion(const Question &question)
{
    QSqlQuery l_query(m_db);
    l_query.prepare("INSERT INTO questions (questionText, description, source) "
                    "VALUES (:questionText, :description, :source)");
    l_query.bindValue(":questionText", question.question_);
    l_query.bindValue(":description", question.description_);
    l_query.bindValue(":source", question.source_);

    if (!l_query.exec())
    {
        std::cerr << "Error in DatabaseManager::addQuestion(const Question &question)" << std::endl;
        return;
//        Macaw::DEBUG(l_query.lastError().text());
    }

    l_query.clear();
    l_query.prepare("select last_insert_rowid();");
    if (!l_query.exec())
    {
        std::cerr << "Error in DatabaseManager::addQuestion(const Question &question)" << std::endl;
        return;
//        Macaw::DEBUG(l_query.lastError().text());
    }

    if(!l_query.first()) {
        std::cerr << "Error in DatabaseManager::addQuestion(const Question &question)" << std::endl;
        return;
    }

    int question_id = l_query.value(0).toInt();
    addAnswers(question.answers_, question_id);
    insertQuestionsTags(question.tags_, question_id);
}

void DatabaseManager::deleteQuestion(const int id)
{
    QSqlQuery l_query(m_db);

    l_query.prepare("Delete from questions "
                    "where questionNumber = :question_id");
    l_query.bindValue(":question_id", id);

    if(!l_query.exec())
    {
       std::cerr << "DatabaseManager::deleteQuestion(const int id)" << std::endl;
       return;
    }
}

void DatabaseManager::deleteQuestions(const std::vector<int>& question_id)
{
    QSqlQuery l_query(m_db);

    QStringList idstrings;
    foreach(int id, question_id) {
        idstrings << QString::number(id);
    }

    l_query.prepare(QString("DELETE FROM questions "
                    "WHERE questionNumber IN (%1) ").arg(idstrings.join(" , ")));

    if(!l_query.exec())
    {
       std::cerr << "DatabaseManager::deleteQuestions(const std::vector<int>& question_id)" << std::endl;
       return;
    }
}

void DatabaseManager::updateQuestion(const Question &question)
{
    QSqlQuery l_query(m_db);

    l_query.prepare("UPDATE questions "
                    "SET questionText = :question, "
                    "description = :description, "
                    "source = :source "
                    "where questionNumber = :question_id");
    l_query.bindValue(":question_id", question.number_);
    l_query.bindValue(":question", question.question_);
    l_query.bindValue(":description", question.description_);
    l_query.bindValue(":source", question.source_);

    if(!l_query.exec())
    {
       std::cerr << "DatabaseManager::updateQuestion(const Question &question)" << std::endl;
       return;
    }

    updateAnswers(question.answers_, question.number_);
    updateTags(question.tags_, question.number_);
}

std::vector<Tag> DatabaseManager::getAllTags()
{
    QSqlQuery l_query(m_db);

    l_query.prepare("SELECT * "
                    "FROM tags");

    if (!l_query.exec())
    {
       QString err_str = l_query.lastError().text();
       std::cerr << "Error in DatabaseManager::getAllTags()"<< std::endl;
//        Macaw::DEBUG(l_query.lastError().text());
    }

    std::vector<Tag> tags;

    while(l_query.next())
    {
        tags.push_back(hydrateTag(l_query));
    }

    return tags;
}

std::vector<Tag> DatabaseManager::getQuestionTags(const int question_id)
{
    QSqlQuery l_query(m_db);

    l_query.prepare("SELECT t.tag_id, t.name "
                    "FROM questions_tags_mapper as qtm "
                    "INNER JOIN tags AS t "
                    "ON t.tag_id = qtm.tag_id "
                    "WHERE qtm.question_id = :question_id;");

    l_query.bindValue(":question_id", question_id);

    if (!l_query.exec())
    {
       QString err_str = l_query.lastError().text();
       std::cerr << "Error in DatabaseManager::getQuestionTags(const int question_id)"<< std::endl;
//        Macaw::DEBUG(l_query.lastError().text());
    }

    std::vector<Tag> tags;

    while(l_query.next())
    {
        tags.push_back(hydrateTag(l_query));
    }

    return tags;
}

std::vector<Tag> DatabaseManager::getAllTagsExceptQuestions(const int question_id)
{
    QSqlQuery l_query(m_db);

    l_query.prepare("SELECT t.tag_id, t.name "
                    "FROM tags t "
                    "WHERE t.tag_id NOT IN "
                    "( SELECT qtm.tag_id FROM questions_tags_mapper qtm "
                    "WHERE qtm.question_id = :question_id ); ");

    l_query.bindValue(":question_id", question_id);

    if (!l_query.exec())
    {
       QString err_str = l_query.lastError().text();
       std::cerr << "Error in DatabaseManager::getAllTagsExceptQuestions(const int question_id)"<< std::endl;
//        Macaw::DEBUG(l_query.lastError().text());
    }

    std::vector<Tag> tags;

    while(l_query.next())
    {
        tags.push_back(hydrateTag(l_query));
    }

    return tags;
}

void DatabaseManager::addAnswers(const std::vector<Answer> &answers, const int question_index)
{
     QSqlQuery l_query(m_db);
     for(const auto& answer : answers)
     {
         l_query.clear();
         l_query.prepare("insert into answers (answerText, isRight, questionNumber)"
                         "VALUES (:answerText, :isRight, :questionNumber)");
         l_query.bindValue(":answerText", answer.value);
         l_query.bindValue(":isRight", answer.isRightAnswer);
         l_query.bindValue(":questionNumber", question_index);

         if(!l_query.exec())
         {
            std::cerr << "DatabaseManager::addAnswers(const std::vector<Answer> &answers, const int question_index)" << std::endl;
            return;
         }
     }
}

void DatabaseManager::updateAnswers(const std::vector<Answer>& answers, const int question_index)
{
    std::vector<int> answers_ids_to_delete;
    foreach( const Answer& answer, getAnswers(question_index))
    {
        if(answer.id == 0) continue;
        bool k = false;
        foreach(const Answer& new_answer, answers)
        {
            if(new_answer.id == answer.id)
            {
                k = true;
                break;
            }
        }
        if(k == false) answers_ids_to_delete.push_back(answer.id);
    }
    deleteAnswers(answers_ids_to_delete);

    QSqlQuery l_query(m_db);
    std::vector<Answer> answers_to_select;
    for(const auto& answer : answers)
    {
        if(answer.id != 0)
        {
            l_query.clear();
            l_query.prepare("UPDATE answers "
                            "SET answerText = :answer, "
                            "isRight = :isRight, "
                            "questionNumber = :question_id "
                            "where id = :answer_id;");
            l_query.bindValue(":answer_id", answer.id);
            l_query.bindValue(":answer", answer.value);
            l_query.bindValue(":isRight", answer.isRightAnswer);
            l_query.bindValue(":question_id", question_index);

            if(!l_query.exec())
            {
               std::cerr << "DatabaseManager::updateAnswers(const std::vector<Answer>& answers, const int question_index)" << std::endl;
               return;
            }
        }
        else
            answers_to_select.push_back(std::move(answer));
    }

    addAnswers(answers_to_select, question_index);
}

void DatabaseManager::deleteAnswers(const std::vector<int> &id_answers)
{
    QSqlQuery l_query(m_db);

    QStringList idstrings;
    foreach(int id, id_answers) {
        idstrings << QString::number(id);
    }

    l_query.prepare(QString("DELETE FROM answers "
                    "WHERE id IN (%1) ").arg(idstrings.join(" , ")));

    if (!l_query.exec())
    {
       QString err_str = l_query.lastError().text();
       std::cerr << "Error in DatabaseManager::deleteAnswers(const std::vector<int> &id_answers)" << std::endl;
    }
}

void DatabaseManager::updateTags(const std::vector<Tag> &tags_to_update, const int question_id)
{
   std::vector<Tag> to_delete;
   std::vector<Tag> to_insert;
   foreach(const Tag& new_tag, tags_to_update)
   {
       bool is_in_old_tags = false;
       foreach(const Tag& old_tag, getQuestionTags(question_id))
       {
           if(old_tag.id == new_tag.id)
           {
               is_in_old_tags = true;
               break;
           }
       }
       if(is_in_old_tags == false)
       {
           to_insert.push_back(new_tag);
       }
   }

   foreach(const Tag& old_tag, getQuestionTags(question_id))
   {
       bool is_in_new_tags = false;
       foreach(const Tag& new_tag, tags_to_update)
       {
           if(old_tag.id == new_tag.id)
           {
               is_in_new_tags = true;
               break;
           }
       }
       if(is_in_new_tags == false)
       {
           to_delete.push_back(old_tag);
       }
   }

   deleteQuestionsTags(to_delete, question_id);
   insertQuestionsTags(to_insert, question_id);
}

void DatabaseManager::deleteQuestionsTags(const std::vector<Tag>& tags_to_delete, const int question_id)
{
    QSqlQuery l_query(m_db);

    QStringList idstrings;
    foreach(const Tag& tag, tags_to_delete) {
        idstrings << QString::number(tag.id);
    }

    l_query.prepare(QString("DELETE FROM questions_tags_mapper "
                    "WHERE tag_id IN (%1) AND question_id = :question_id")
                    .arg(idstrings.join(" , ")));
    l_query.bindValue(":question_id", question_id);

    if (!l_query.exec())
    {
       QString err_str = l_query.lastError().text();
       std::cerr << "Error in DatabaseManager::deleteQuestionsTags(const std::vector<Tag>& tags_to_delete, const int question_id)" << std::endl;
    }
}

void DatabaseManager::insertQuestionsTags(const std::vector<Tag> &tags_to_insert, const int question_id)
{
    QSqlQuery l_query(m_db);
    for(const auto& tag : tags_to_insert)
    {
        l_query.clear();
        l_query.prepare("insert into questions_tags_mapper (question_id, tag_id) "
                        "VALUES (:question_id, :tag_id) ");
        l_query.bindValue(":question_id", question_id);
        l_query.bindValue(":tag_id", tag.id);

        if(!l_query.exec())
        {
           std::cerr << "DatabaseManager::insertQuestionsTags(const std::vector<Tag> &tags_to_insert, const int question_id)" << std::endl;
           return;
        }
    }
}

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{
    openDB();
    std::cout << "[DatabaseManager] object created" << std::endl;
}

Tag DatabaseManager::hydrateTag(QSqlQuery &query)
{
    Tag tag;
    tag.id = query.value(0).toInt();
    tag.name_ = query.value(1).toString();
    return tag;
}

Question DatabaseManager::hydrateQuestion(QSqlQuery &query)
{
//    query.isActive();
//    query.first();
    Question question;
    question.number_ = query.value(0).toInt();
    question.question_ = query.value(1).toString();
    question.description_ = query.value(2).toString();
    question.source_ = query.value(3).toString();
    question.answers_ = getAnswers(question.number_);
    return question;
}

Answer DatabaseManager::hydrateAnswer(QSqlQuery &query)
{
//    query.isActive();
//    query.first();
    Answer answer;
    answer.id = query.value(0).toInt();
    answer.value = query.value(1).toString();
    answer.isRightAnswer = query.value(2).toBool();
    return answer;
}

DatabaseManager::~DatabaseManager()
{
    if(!closeDB()) std::cerr << "Close DB error!!" << std::endl;
}

