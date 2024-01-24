#include <iostream>
#include "Card.h"
#include "Scheduler.h"
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
        std::vector<float> params{0.4, 0.6, 2.4, 5.8, 4.93, 0.94, 0.86, 0.01, 1.49, 0.14, 0.94, 2.18, 0.05, 0.34, 1.26, 0.29, 2.61};
        float factor = 19.0/81.0;
        float decay = -0.5;
        card = Card(params, factor, decay);
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

TEST_F(TestCardFixture, InitDifficulty)
{
    card.registerInitialRating(Rating::AGAIN);
    EXPECT_NEAR(card.getDifficulty(), 6.81, 0.01);
    card.registerInitialRating(Rating::HARD);
    EXPECT_NEAR(card.getDifficulty(), 5.87, 0.01);
    card.registerInitialRating(Rating::GOOD);
    EXPECT_NEAR(card.getDifficulty(), 4.93, 0.01);
    card.registerInitialRating(Rating::EASY);
    EXPECT_NEAR(card.getDifficulty(), 3.99, 0.01);
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

// TEST_F(TestCardFixture, TestRetrievability1)
// {
    
// }

// TEST_F(TestCardFixture, TestRetrievability2)
// {
    
// }

// TEST_F(TestCardFixture, TestRetrievability3)
// {
    
// }

// TEST_F(TestCardFixture, TestDSRUpdate1)
// {
    
// }

// TEST_F(TestCardFixture, TestDSRUpdate2)
// {
    
// }

// TEST_F(TestCardFixture, TestDSRUpdate3)
// {
    
// }