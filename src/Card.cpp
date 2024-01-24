#include "Card.h"

Card::Card()
{

}
Card::Card(std::vector<float> params, float factor, float decay)
    :   factor{factor}, decay{decay}
{
    // initialize the param vector
    this->params = params;
}

void Card::registerInitialRating(Rating rating)
{
    // initialize difficulty
    this->difficulty = this->calcD0(rating);
    
    // initialize stability
    this->stability = this->params[rating-1];
    
    // initial review time
    this->lastUTCReviewTime = Card::getUTCTime();
}

float Card::calcD0(Rating rating)
{
    return this->params[4] - this->params[5] * (rating - 3);
}

float Card::getRetrievability()
{
    double time_elapsed_since_last_review = this->getTimeElapsedSinceLastReview();
    return this->getRetrievability(time_elapsed_since_last_review);
}

float Card::getRetrievability(double time_elapsed_since_last_review)
{
    return pow((1 + this->factor * time_elapsed_since_last_review / this->stability), this->decay);
}

void Card::DSRUpdate(Rating rating)
{
    double time_elapsed_since_last_review = this->getTimeElapsedSinceLastReview();
    this->DSRUpdate(rating, time_elapsed_since_last_review);
}
void Card::DSRUpdate(Rating rating, double time_elapsed_since_last_review)
{
    // call the stability update function BEFORE difficulty update
    this->SUpdate(rating, time_elapsed_since_last_review);

    // call the difficulty update function
    this->DUpdate(rating);

    // update last review time
    this->lastUTCReviewTime = Card::getUTCTime();
}

void Card::DUpdate(Rating rating)
{
    float aaa = this->params[7] * this->calcD0(Rating::GOOD);
    float core_update = this->difficulty - this->params[6] * (rating - 3);
    float bbb = (1 - this->params[7]) * (core_update);
    this->difficulty = aaa + bbb;
}

void Card::SUpdate(Rating rating, double time_elapsed_since_last_review)
{
    float ew8 = exp(this->params[8]);
    float sw9 = pow(this->stability, - this->params[9]);
    float ew101r = exp(this->params[10] * (1-this->getRetrievability(time_elapsed_since_last_review)));
    float wjg = 0;
    if (rating == Rating::HARD) wjg = this->params[15];
    else if (rating == Rating::GOOD) wjg = 1;
    else if (rating == Rating::EASY) wjg = this->params[16];
    this->stability = this->stability * (ew8 * (11 - this->difficulty) * sw9 * (ew101r - 1) * wjg + 1);
}

tm* Card::getUTCTime()
{
    time_t now = time(0);
    tm *gmtm = gmtime(&now);
    return gmtm;
}

tm* Card::getLastReviewTime()
{
    return this->lastUTCReviewTime;
}

float Card::getDifficulty()
{
    return this->difficulty;
}

float Card::getStability()
{
    return this->stability;
}

double Card::getTimeElapsedSinceLastReview()
{
    time_t current_time = mktime(Card::getUTCTime());
    time_t last_time = mktime(this->lastUTCReviewTime);
    return difftime(current_time, last_time);
}





