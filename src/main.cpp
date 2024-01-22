#include <iostream>
#include "Card.h"
#include "Scheduler.h"
#include <gtest/gtest.h>

TEST(TestCardInit, InitDifficulty)
{

}


// int main(int argc, char **argv)
// {
//     // test the rating enum
//     std::cout << Rating::AGAIN << std::endl;
    
//     // test time
//     char* dt = asctime(Card::getUTCTime());
//     std::cout << "The UTC date and time is:"<< dt << std::endl;
    
//     // create the card
//     std::vector<float> params{0.4, 0.6, 2.4, 5.8, 4.93, 0.94, 0.86, 0.01, 1.49, 0.14, 0.94, 2.18, 0.05, 0.34, 1.26, 0.29, 2.61};
//     float factor = 19.0/81.0;
//     float decay = -0.5;
//     Card card = Card(params, factor, decay);
    
//     // check initial rating function
//     card.registerInitialRating(Rating::EASY);
//     std::cout << "Initial Rating time: " << asctime(card.getLastReviewTime()) << "Initial Rating: " << Rating::EASY << ". Initial Difficulty: " << card.getDifficulty() << ". Initial Stability: " << card.getStability() << std::endl << std::endl;
//     card.registerInitialRating(Rating::GOOD);
//     std::cout << "Initial Rating time: " << asctime(card.getLastReviewTime()) << "Initial Rating: " << Rating::GOOD << ". Initial Difficulty: " << card.getDifficulty() << ". Initial Stability: " << card.getStability() << std::endl << std::endl;
//     card.registerInitialRating(Rating::HARD);
//     std::cout << "Initial Rating time: " << asctime(card.getLastReviewTime()) << "Initial Rating: " << Rating::HARD << ". Initial Difficulty: " << card.getDifficulty() << ". Initial Stability: " << card.getStability() << std::endl << std::endl;
//     card.registerInitialRating(Rating::AGAIN);
//     std::cout << "Initial Rating time: " << asctime(card.getLastReviewTime()) << "Initial Rating: " << Rating::AGAIN << ". Initial Difficulty: " << card.getDifficulty() << ". Initial Stability: " << card.getStability() << std::endl << std::endl;
    
    
//     // test getRetrievability
//     card.registerInitialRating(Rating::GOOD);
//     float retrievability = card.getRetrievability(2.4);
//     std::cout << "Retrievability: " << retrievability << std::endl;
    
//     testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();


//     // return 0;
// }