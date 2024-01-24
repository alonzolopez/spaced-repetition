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
    Card();
    Card(std::vector<float> params, float factor, float decay);
    ~Card() = default;
    
    void registerInitialRating(Rating rating);

    float calcD0(Rating rating);

    float getRetrievability();
    float getRetrievability(double time_elapsed);

    int getNextInterval();

    void DSRUpdate(Rating rating);
    void DSRUpdate(Rating rating, double time_elapsed_since_last_review);

    void DUpdate(Rating rating);

    void SUpdate(Rating rating, double time_elapsed_since_last_review);

    static tm* getUTCTime();
    
    tm* getLastReviewTime();
    
    float getDifficulty();
    
    float getStability();

    double getTimeElapsedSinceLastReview();
    
private:
    std::vector<float> params;
    tm* lastUTCReviewTime;
    float factor;
    float difficulty;
    float stability;
    std::vector<float> stability_history;
    float decay;
};