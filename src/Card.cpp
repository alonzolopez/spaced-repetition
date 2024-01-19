#include "Card.h"

Card::Card(std::vector<float> params, float factor, float decay)
    :   factor{factor}, decay{decay}
{
    // initialize the param vector
    this->params = params;
}

void Card::registerInitialRating(Rating rating)
{
    // initialize difficulty
    this->difficulty = params[4] - params[5] * (rating - 3);
    
    // initialize stability
    this->stability = params[rating-1];
    
    // initial review time
    this->lastUTCReviewTime = Card::getUTCTime();
}

float Card::getDifficulty()
{
    return this->difficulty;
}

tm* Card::getLastReviewTime()
{
    return this->lastUTCReviewTime;
}

float Card::getStability()
{
    return this->stability;
}

tm* Card::getUTCTime()
{
    time_t now = time(0);
    tm *gmtm = gmtime(&now);
    return gmtm;
}

double Card::getTimeElapsedSinceLastReview()
{
    time_t current_time = mktime(Card::getUTCTime());
    time_t last_time = mktime(this->lastUTCReviewTime);
    return difftime(current_time, last_time);
}

float Card::getRetrievability()
{
    double time_elapsed = this->getTimeElapsedSinceLastReview();
    float retrievability = pow((1 + this->factor * time_elapsed / this->stability), this->decay);
    return retrievability;
}