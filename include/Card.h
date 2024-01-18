#include <vector>
#include <iostream>
#include <ctime>

enum Rating
{
    AGAIN = 1,
    HARD,
    GOOD,
    EASY
};

class Card
{
public:
    Card();

    float getRetrievability();

    int getNextInterval();

    int DSRUpdate();

    static tm* getUTCTime();


private:
    tm* lastUTCReviewTime;
    float factor;
    float stability;
    std::vector<float> stability_history;
    float decay;
};