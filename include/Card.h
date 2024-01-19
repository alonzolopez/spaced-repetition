#include <vector>
#include <iostream>
#include <ctime>
#include <math.h>

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
    Card(std::vector<float> params, float factor, float decay);
    
    void registerInitialRating(Rating rating);

    float getRetrievability();

    int getNextInterval();

    int DSRUpdate();

    static tm* getUTCTime();
    
    tm* getLastReviewTime();
    
    float getDifficulty();
    
    double getTimeElapsedSinceLastReview();
    
    float getStability();


private:
    std::vector<float> params;
    tm* lastUTCReviewTime;
    float factor;
    float difficulty;
    float stability;
    std::vector<float> stability_history;
    float decay;
};