#pragma once
#include <string>
#include <fstream>
// #include <sstream>
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include "Card.h"
#include <set>
#include <queue>

class Deck
{
public:
    Deck();
    ~Deck() = default;


    void loadDeckFromJSONFile(std::string filepath);

    void printDeck();

    void writeDeckToFile(std::string filepath);

    Card getNextReviewCard();

    /**
     * @brief Draw the next card in the deck using the spaced repetition algorithm.
     */
    Card drawCard();

    void registerReview(Card card);

    struct DueNext{
        bool operator()(const Card& cardA, const Card& cardB) const{
            time_t timeA = mktime(cardA.getDueDate());
            time_t timeB = mktime(cardB.getDueDate());
            std::cout << "difftime(timeA, timeB) < 0: " << (difftime(timeA, timeB) < 0) << std::endl;
            return difftime(timeA, timeB) < 0;
        }
    };

    std::queue<Card> newCards;
    std::multiset<Card, DueNext> reviewNext;
    int numCards;
    float factor;
    float decay;
    std::vector<float> params;
};