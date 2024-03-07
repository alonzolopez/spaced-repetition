#include <iostream>
#include "Card.h"
#include "Deck.h"
// #include "Scheduler.h"
#include <gtest/gtest.h>

class TestCardFixture : public testing::Test
{
protected:
    
    void SetUp() override
    {
    }

    TestCardFixture()
    {
        // create the card
        std::vector<float> params{  0.4,    // w_0 initial stability after Rating::AGAIN
                                    0.6,    // w_1 initial stability after Rating::HARD
                                    2.4,    // w_2 initial stability after Rating::GOOD
                                    5.8,    // w_3 initial stability after Rating::EASY
                                    4.93,   // w_4 initial difficulty constant: D0 = w_4 - (G-3)*w_5
                                    0.94,   // w_5 initial difficulty slope: D0 = w_4 - (G-3)*w_5
                                    0.86,   // w_6 difficulty update factor. Without mean reversion, D' = D - w_6*(G-3)
                                    0.01,   // w_7 mean reversion factor to avoid ease hell in difficulty update
                                    1.49,   // w_8 successful stability update param
                                    0.14,   // w_9 successful stability update param
                                    0.94,   // w_10 successful stability update param
                                    2.18,   // w_11 unsuccessful stability update param
                                    0.05,   // w_12 unsuccessful stability update param
                                    0.34,   // w_13 unsuccessful stability update param
                                    1.26,   // w_14 unsuccessful stability update param
                                    0.29,   // w_15 successful stability update param
                                    2.61};  // w_16 successful stability update param
        float factor = 19.0/81.0;
        float decay = -0.5;
        card = Card(params, factor, decay, 1000001, false);
    }

    Card card;
    
};

TEST_F(TestCardFixture, TestD0)
{
    EXPECT_NEAR(card.calcD0(Rating::AGAIN), 6.81, 0.01);
    EXPECT_NEAR(card.calcD0(Rating::HARD), 5.87, 0.01);
    EXPECT_NEAR(card.calcD0(Rating::GOOD), 4.93, 0.01);
    EXPECT_NEAR(card.calcD0(Rating::EASY), 3.99, 0.01);
}

TEST_F(TestCardFixture, InitDifficultyStability)
{
    card.registerInitialRating(Rating::AGAIN);
    EXPECT_NEAR(card.getDifficulty(), 6.81, 0.01);
    EXPECT_NEAR(card.getStability(), 0.4, 0.001);
    card.registerInitialRating(Rating::HARD);
    EXPECT_NEAR(card.getDifficulty(), 5.87, 0.01);
    EXPECT_NEAR(card.getStability(), 0.6, 0.001);
    card.registerInitialRating(Rating::GOOD);
    EXPECT_NEAR(card.getDifficulty(), 4.93, 0.01);
    EXPECT_NEAR(card.getStability(), 2.4, 0.001);
    card.registerInitialRating(Rating::EASY);
    EXPECT_NEAR(card.getDifficulty(), 3.99, 0.01);
    EXPECT_NEAR(card.getStability(), 5.8, 0.001);
}

TEST_F(TestCardFixture, TestTimePrints)
{
    // test time
    char* dt = asctime(Card::getUTCTime());
    std::cout << "The UTC date and time is:"<< dt << std::endl;
}

TEST_F(TestCardFixture, InitRetrievability)
{
    card.registerInitialRating(Rating::AGAIN);
    EXPECT_EQ(card.getRetrievability(0.0), 1.00);
    card.registerInitialRating(Rating::HARD);
    EXPECT_EQ(card.getRetrievability(0.0), 1.00);
    card.registerInitialRating(Rating::GOOD);
    EXPECT_EQ(card.getRetrievability(0.0), 1.00);
    card.registerInitialRating(Rating::EASY);
    EXPECT_EQ(card.getRetrievability(0.0), 1.00);
}

TEST_F(TestCardFixture, TestRetrievabilityAt90PercentProbability)
{
    card.registerInitialRating(Rating::AGAIN);
    EXPECT_NEAR(card.getRetrievability(0.4), 0.9, 0.001);
    card.registerInitialRating(Rating::HARD);
    EXPECT_NEAR(card.getRetrievability(0.6), 0.9, 0.001);
    card.registerInitialRating(Rating::GOOD);
    EXPECT_NEAR(card.getRetrievability(2.4), 0.9, 0.001);
    card.registerInitialRating(Rating::EASY);
    EXPECT_NEAR(card.getRetrievability(5.8), 0.9, 0.001);
}


/*********** Initial rating: Easy ***********/
TEST_F(TestCardFixture, TestDSRUpdateEasyEasy)
{
    // register initial rating
    card.registerInitialRating(Rating::EASY);

    // register a new rating with a DSR update
    double time_elapsed_since_last_review = 5.8; // test at 90% recall probability
    card.DSRUpdate(Rating::EASY, time_elapsed_since_last_review);

    // check the values
    EXPECT_NEAR(card.getDifficulty(), 3.1480000000000006, 0.001); // with Rating::EASY
    EXPECT_NEAR(card.getStability(), 42.0831473930719, 0.001);
}

TEST_F(TestCardFixture, TestDSRUpdateEasyGood)
{
    // register initial rating
    card.registerInitialRating(Rating::EASY);

    // register a new rating with a DSR update
    double time_elapsed_since_last_review = 5.8; // test at 90% recall probability
    card.DSRUpdate(Rating::GOOD, time_elapsed_since_last_review);

    // check the values
    EXPECT_NEAR(card.getDifficulty(), 3.9994000000000005, 0.001); // with Rating::GOOD
    EXPECT_NEAR(card.getStability(), 19.701589039491147, 0.001);
}

TEST_F(TestCardFixture, TestDSRUpdateEasyHard)
{
    // register initial rating
    card.registerInitialRating(Rating::EASY);

    // register a new rating with a DSR update
    double time_elapsed_since_last_review = 5.8; // test at 90% recall probability
    card.DSRUpdate(Rating::HARD, time_elapsed_since_last_review);

    // check the values
    EXPECT_NEAR(card.getDifficulty(), 4.8508000000000004, 0.001); // with Rating::HARD
    EXPECT_NEAR(card.getStability(), 9.831460821452433, 0.001);
}

TEST_F(TestCardFixture, TestDSRUpdateEasyAgain)
{
    // register initial rating
    card.registerInitialRating(Rating::EASY);

    // register a new rating with a DSR update
    double time_elapsed_since_last_review = 5.8; // test at 90% recall probability
    card.DSRUpdate(Rating::AGAIN, time_elapsed_since_last_review);

    // check the values
    EXPECT_NEAR(card.getDifficulty(), 5.7021999999999995, 0.001); // with Rating::AGAIN
    EXPECT_NEAR(card.getStability(), 2.120306480230755, 0.001);
}

/*********** Initial rating: Good ***********/
TEST_F(TestCardFixture, TestDSRUpdateGoodEasy)
{
    // register initial rating
    card.registerInitialRating(Rating::GOOD);

    // register a new rating with a DSR update
    double time_elapsed_since_last_review = 2.4; // test at 90% recall probability
    card.DSRUpdate(Rating::EASY, time_elapsed_since_last_review);

    // check the values
    EXPECT_NEAR(card.getDifficulty(), 4.078599999999999, 0.001); // with Rating::EASY
    EXPECT_NEAR(card.getStability(), 17.10988303781303, 0.001);
}

TEST_F(TestCardFixture, TestDSRUpdateGoodGood)
{
    // register initial rating
    card.registerInitialRating(Rating::GOOD);

    // register a new rating with a DSR update
    double time_elapsed_since_last_review = 2.4; // test at 90% recall probability
    card.DSRUpdate(Rating::GOOD, time_elapsed_since_last_review);

    // check the values
    EXPECT_NEAR(card.getDifficulty(), 4.93, 0.001); // with Rating::GOOD
    EXPECT_NEAR(card.getStability(), 8.035970512572042, 0.001);
}

TEST_F(TestCardFixture, TestDSRUpdateGoodHard)
{
    // register initial rating
    card.registerInitialRating(Rating::GOOD);

    // register a new rating with a DSR update
    double time_elapsed_since_last_review = 2.4; // test at 90% recall probability
    card.DSRUpdate(Rating::HARD, time_elapsed_since_last_review);

    // check the values
    EXPECT_NEAR(card.getDifficulty(), 5.7814, 0.001); // with Rating::HARD
    EXPECT_NEAR(card.getStability(), 4.0344314486458925, 0.001);
}

TEST_F(TestCardFixture, TestDSRUpdateGoodAgain)
{
    // register initial rating
    card.registerInitialRating(Rating::GOOD);

    // register a new rating with a DSR update
    double time_elapsed_since_last_review = 2.4; // test at 90% recall probability
    card.DSRUpdate(Rating::AGAIN, time_elapsed_since_last_review);

    // check the values
    EXPECT_NEAR(card.getDifficulty(), 6.632799999999999, 0.001); // with Rating::AGAIN
    EXPECT_NEAR(card.getStability(), 1.178136524731929, 0.001);
}

/*********** Initial rating: Hard ***********/
TEST_F(TestCardFixture, TestDSRUpdateHardEasy)
{
    // register initial rating
    card.registerInitialRating(Rating::HARD);

    // register a new rating with a DSR update
    double time_elapsed_since_last_review = 0.6; // test at 90% recall probability
    card.DSRUpdate(Rating::EASY, time_elapsed_since_last_review);

    // check the values
    EXPECT_NEAR(card.getDifficulty(), 5.009199999999999, 0.001); // with Rating::EASY
    EXPECT_NEAR(card.getStability(), 4.373690695564387, 0.001);

}

TEST_F(TestCardFixture, TestDSRUpdateHardGood)
{
    // register initial rating
    card.registerInitialRating(Rating::HARD);

    // register a new rating with a DSR update
    double time_elapsed_since_last_review = 0.6; // test at 90% recall probability
    card.DSRUpdate(Rating::GOOD, time_elapsed_since_last_review);

    // check the values
    EXPECT_NEAR(card.getDifficulty(), 5.8606, 0.001); // with Rating::GOOD
    EXPECT_NEAR(card.getStability(), 2.0458585040476582, 0.001);

}

TEST_F(TestCardFixture, TestDSRUpdateHardHard)
{
    // register initial rating
    card.registerInitialRating(Rating::HARD);

    // register a new rating with a DSR update
    double time_elapsed_since_last_review = 0.6; // test at 90% recall probability
    card.DSRUpdate(Rating::HARD, time_elapsed_since_last_review);

    // check the values
    EXPECT_NEAR(card.getDifficulty(), 6.712, 0.001); // with Rating::HARD
    EXPECT_NEAR(card.getStability(), 1.0192989661738208, 0.001);

}

TEST_F(TestCardFixture, TestDSRUpdateHardAgain)
{
    // register initial rating
    card.registerInitialRating(Rating::HARD);

    // register a new rating with a DSR update
    double time_elapsed_since_last_review = 0.6; // test at 90% recall probability
    card.DSRUpdate(Rating::AGAIN, time_elapsed_since_last_review);

    // check the values
    EXPECT_NEAR(card.getDifficulty(), 7.5634, 0.001); // with Rating::AGAIN
    EXPECT_NEAR(card.getStability(), 0.3921825063812797, 0.001);

}


/*********** Initial rating: Again ***********/
TEST_F(TestCardFixture, TestDSRUpdateAgainEasy)
{
    // register initial rating
    card.registerInitialRating(Rating::AGAIN);

    // register a new rating with a DSR update
    double time_elapsed_since_last_review = 0.4; // test at 90% recall probability
    card.DSRUpdate(Rating::EASY, time_elapsed_since_last_review);

    // check the values
    EXPECT_NEAR(card.getDifficulty(), 5.939799999999999, 0.001); // with Rating::EASY
    EXPECT_NEAR(card.getStability(), 2.574825798535859, 0.001);

}

TEST_F(TestCardFixture, TestDSRUpdateAgainGood)
{
    // register initial rating
    card.registerInitialRating(Rating::AGAIN);

    // register a new rating with a DSR update
    double time_elapsed_since_last_review = 0.4; // test at 90% recall probability
    card.DSRUpdate(Rating::GOOD, time_elapsed_since_last_review);

    // check the values
    EXPECT_NEAR(card.getDifficulty(), 6.791199999999999, 0.001); // with Rating::GOOD
    EXPECT_NEAR(card.getStability(), 1.2332665894773407, 0.001);

}

TEST_F(TestCardFixture, TestDSRUpdateAgainHard)
{
    // register initial rating
    card.registerInitialRating(Rating::AGAIN);

    // register a new rating with a DSR update
    double time_elapsed_since_last_review = 0.4; // test at 90% recall probability
    card.DSRUpdate(Rating::HARD, time_elapsed_since_last_review);

    // check the values
    EXPECT_NEAR(card.getDifficulty(), 7.6426, 0.001); // with Rating::HARD
    EXPECT_NEAR(card.getStability(), 0.6416473109484289, 0.001);

}

TEST_F(TestCardFixture, TestDSRUpdateAgainAgain)
{
    // register initial rating
    card.registerInitialRating(Rating::AGAIN);

    // register a new rating with a DSR update
    double time_elapsed_since_last_review = 0.4; // test at 90% recall probability
    card.DSRUpdate(Rating::AGAIN, time_elapsed_since_last_review);

    // check the values
    EXPECT_NEAR(card.getDifficulty(), 8.494, 0.001); // with Rating::AGAIN
    EXPECT_NEAR(card.getStability(), 0.2722870338920606, 0.001);

}

class TestDeckFixture : public testing::Test
{
protected:
    
    void SetUp() override
    {
    }

    TestDeckFixture()
    {
        deck = Deck();
        deck.loadDeckFromJSONFile("../resources/deck_intervals.jsonl");
    }
    Deck deck;
};

TEST_F(TestDeckFixture, TestLoadDeck)
{
    std::cout << std::endl;
    std::cout << "Initial deck:" << std::endl;
    deck.printDeck();

    // draw and review the first card
    Card card = deck.drawCard();
    std::cout << std::endl << "Card pre-review:" << std::endl;
    card.printCard();
    card.registerInitialRating(Rating::HARD);
    std::cout << std::endl << "Card post-review:" << std::endl;
    card.printCard();
    deck.registerReview(card);
    std::cout << std::endl << "Deck:" << std::endl;
    deck.printDeck();
    deck.writeDeckToFile("../resources/deck_intervals_test_output_1.jsonl");
    std::cout << std::endl << std::endl << std::endl;

    // draw the second card
    Card card2 = deck.drawCard();
    std::cout << std::endl << "Card pre-review:" << std::endl;
    card2.printCard();
    card2.registerInitialRating(Rating::EASY);
    std::cout << std::endl << "Card post-review:" << std::endl;
    card2.printCard();
    deck.registerReview(card2);
    std::cout << std::endl << "Deck:" << std::endl;
    deck.printDeck();
    deck.writeDeckToFile("../resources/deck_intervals_test_output_2.jsonl");
    std::cout << std::endl;

    // draw the third card
    Card card3 = deck.drawCard();
    std::cout << std::endl << "Card pre-review:" << std::endl;
    card3.printCard();
    card3.registerInitialRating(Rating::HARD);
    std::cout << std::endl << "Card post-review:" << std::endl;
    card3.printCard();
    deck.registerReview(card3);
    std::cout << std::endl << "Deck:" << std::endl;
    deck.printDeck();
    deck.writeDeckToFile("../resources/deck_intervals_test_output_3.jsonl");
    std::cout << std::endl;
}

TEST_F(TestDeckFixture, TestLoadDeckWithUTCTime)
{
    // intermediate jsonl file
    std::string savepath = "../resources/deck_intervals_test_output_4.jsonl";

    // draw and review the first card
    Card card = deck.drawCard();
    card.registerInitialRating(Rating::HARD);
    deck.registerReview(card);

    // draw and review the second card
    Card card2 = deck.drawCard();
    card2.registerInitialRating(Rating::HARD);
    deck.registerReview(card2);

    // write the deck to the file
    deck.writeDeckToFile(savepath);
    
    
    // load a new deck from the intermediate deck
    Deck deck2 = Deck();
    deck2.loadDeckFromJSONFile(savepath);

    // review one of the cards in this deck
    Card card4 = deck2.drawCard();
    std::cout << std::endl;
    std::cout << "Card to review in deck2:" << std::endl;
    card4.printCard();
    card4.registerInitialRating(Rating::EASY);
    deck2.registerReview(card4);
    deck2.printDeck();
}