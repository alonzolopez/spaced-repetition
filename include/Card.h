#pragma once
#include <vector>
#include <iostream>
#include <ctime>
#include <math.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

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
    /**
     * @brief Default constructor
     */
    Card();

    /**
     * @brief Construct an unreviewed (i.e. uninitialized) card
     * @param params 
     * @param factor 
     * @param decay 
     * @param cardID 
     * @param initialized 
     */
    Card(std::vector<float> params, float factor, float decay, int cardID, bool initialized);

    /**
     * @brief Construct a reviewed (i.e. initialized) card
     * @param params 
     * @param factor 
     * @param decay 
     * @param cardID 
     * @param lastReviewTimeUTC 
     * @param stability 
     * @param difficulty 
     * @param initialized 
     */
    Card(std::vector<float> params, float factor, float decay, int cardID, std::string lastReviewTimeUTC, float stability, float difficulty, bool initialized);

    /**
     * @brief Default destructor
     */
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
    
    tm* getLastReviewTimeUTC() const;

    /**
     * @brief Set the last UTC review time from a string
     * @param lastReviewTimeUTCStr 
     * 
     * Takes in a std::string and sets the review time using that string.
     * If the card has been reviewed previously, a string of the format "YYYY-MM-DDTHH:MM:SS"
     * should be passed in. If the card has not been reviewed yet, the string "0" should be
     * passed in.
     */
    void setLastReviewTimeUTCFromString(std::string lastReviewTimeUTCStr);

    std::string getLastReviewTimeUTCAsString();

    tm* getDueDate() const;

    std::string getDueDateAsString();
    
    
    float getDifficulty() const;
    void setDifficulty(float newDifficulty);
    
    float getStability() const;
    void setStability(float newStability);

    double getTimeElapsedSinceLastReview();

    void printCard();

    json asJSON();
    
private:
    std::vector<float> params;
    tm* lastUTCReviewTime;
    float factor;
    float difficulty;
    float stability;
    std::vector<float> stability_history;
    float decay;
    int cardID;
    bool initialized;
};