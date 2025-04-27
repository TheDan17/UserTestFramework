#ifndef TESTPARAMS_H
#define TESTPARAMS_H

class TestFactory;

class TestParams {
    friend class TestFactory;
private:
    short difficultyLevel;
    bool isRandomized;

    short datasetIndex; // 0 - is dataset with all avaliable data
    int testLinesAmount; // -1 - is unlimited, all elements in dataset
public:
    static const int isAllAmount = -1;
    TestParams(short d = 0, bool r = true, short i = 0, int l = -1) : difficultyLevel(d), isRandomized(r), datasetIndex(i), testLinesAmount(l) {}
};

#endif // TESTPARAMS_H
