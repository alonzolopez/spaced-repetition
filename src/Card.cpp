#include "Card.h"

Card::Card()
{

}
Card::Card(std::vector<float> params, float factor, float decay, int cardID, bool initialized)
    :   factor{factor}, decay{decay}, cardID{cardID}, initialized{initialized}
{
    // initialize the param vector
    this->params = params;
}

Card::Card(std::vector<float> params, float factor, float decay, int cardID, 
            std::string lastReviewTimeUTCStr, float stability, float difficulty, 
            bool initialized)
    :   factor{factor}, decay{decay}, cardID{cardID}, initialized{initialized},
        stability{stability}, difficulty{difficulty}
{
    // initialize the param vector
    this->params = params;

    if (this->initialized){
        std::cout << "This card is initialized, so we're going to try and set the UTC time from a string" << std::endl;
        // set the last review time from a string
        this->setLastReviewTimeUTCFromString(lastReviewTimeUTCStr);    
    }
}

void Card::registerInitialRating(Rating rating)
{
    // initialize difficulty
    this->difficulty = this->calcD0(rating);
    
    // initialize stability
    this->stability = this->params[rating-1];
    
    // initial review time
    this->lastUTCReviewTime = Card::getUTCTime();

    // switch the initialized flag
    this->initialized = true;
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
    if (rating == Rating::EASY || rating == Rating::GOOD || rating == Rating::HARD)
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
    else if (rating == Rating::AGAIN)
    {
        float dw12 = pow(this->difficulty, - this->params[12]);
        float s1w13 = pow(this->stability + 1, this->params[13]);
        float ew141R = exp(this->params[14] * (1 - this->getRetrievability(time_elapsed_since_last_review)));
        this->stability = this->params[11] * dw12 * (s1w13 - 1) * ew141R;
    }
}

tm* Card::getUTCTime()
{
    time_t now = time(0);
    tm *gmtm = gmtime(&now);
    return gmtm;
}

tm* Card::getLastReviewTimeUTC() const
{
    return this->lastUTCReviewTime;
}

void Card::setLastReviewTimeUTCFromString(std::string lastReviewTimeUTCStr)
{
    // use strptime to convert a string to a tm struct
    // https://linux.die.net/man/3/strptime
    if (lastReviewTimeUTCStr == "0"){
        this->initialized = false;
    }
    else{
        // initialize lastUTCReviewTime tm struct (else strptime won't work)
        time_t now = time(0);
        this->lastUTCReviewTime = gmtime(&now);

        // populate this->lastUTCReviewTime with the string data
        strptime(lastReviewTimeUTCStr.c_str(), "%Y-%m-%dT%H:%M:%S", this->lastUTCReviewTime);
    }
}

std::string Card::getLastReviewTimeUTCAsString()
{
    // try using asctime https://www.softwaretestinghelp.com/date-and-time-in-cpp/
    if (this->initialized)
    {
        size_t size = 20;
        char buffer[size];
        strftime(buffer, size, "%Y-%m-%dT%H:%M:%S", this->getLastReviewTimeUTC());
        return buffer;
    }
    else
    {
        return "Not reviewed yet";
    }
}

tm* Card::getDueDate() const
{
    tm dueDate = *(this->getLastReviewTimeUTC()); // copy dueDate from lastReviewTimeUTC
    
    dueDate.tm_min += int(this->stability * 60.0) % 60;
    dueDate.tm_hour += int(this->stability) % 24;
    dueDate.tm_mday += int(this->stability / 24);
    time_t dueDate2 = mktime(&dueDate);
    // std::cout << "ctime: " << ctime(&dueDate2) << std::endl;
    return localtime(&dueDate2); // use localtime since it's already in UTC time
}

std::string Card::getDueDateAsString()
{
    if (this->initialized)
    {
        size_t size = 20;
        char buffer[size];
        strftime(buffer, size, "%Y-%m-%dT%H:%M:%S", this->getDueDate());
        return buffer;
    }
    else
    {
        return "No due date yet";
    }
}

float Card::getDifficulty() const
{
    return this->difficulty;
}

void Card::setDifficulty(float newDifficulty)
{
    this->difficulty = newDifficulty;
}

float Card::getStability() const
{
    return this->stability;
}

void Card::setStability(float newStability)
{
    this->stability = newStability;
}

double Card::getTimeElapsedSinceLastReview()
{
    time_t current_time = mktime(Card::getUTCTime());
    time_t last_time = mktime(this->lastUTCReviewTime);
    return difftime(current_time, last_time);
}

void Card::printCard()
{
    std::cout << "CARD ID: " << this->cardID << std::endl;
    std::cout << "Difficulty: " << this->difficulty << std::endl;
    std::cout << "Stability: " << this->stability << std::endl;
    if (this->initialized) 
        std::cout << "Retrievability: " << this->getRetrievability() << std::endl;
    std::cout << "Last review time: " << this->getLastReviewTimeUTCAsString() << std::endl;
    std::cout << "Due: " << this->getDueDateAsString() << std::endl;
}

json Card::asJSON()
{
    json jsoncard = 
    {
        {"cardID", this->cardID},
        {"due", this->getDueDateAsString()},
        {"difficulty", this->difficulty},
        {"stability", this->stability},
        {"lastReviewTimeUTC", this->getLastReviewTimeUTCAsString()},
        {"initialized", int(this->initialized)}
    };
    return jsoncard;
}

