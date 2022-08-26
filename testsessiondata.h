#ifndef TESTSESSIONDATA_H
#define TESTSESSIONDATA_H

#include <vector>
#include "question.h"
#include "tag.h"

struct TestSessionData
{
    std::vector<Question> questions;
    std::vector<Tag> tags;
};

#endif // TESTSESSIONDATA_H
