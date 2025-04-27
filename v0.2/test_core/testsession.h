#ifndef TESTSESSION_H
#define TESTSESSION_H

#include "../test/test.h"
#include "../test/testparams.h"

class TestSession {
    Test* test;
    TestParams* params;
public:
    TestSession(Test* test, TestParams* params);
};

#endif // TESTSESSION_H
