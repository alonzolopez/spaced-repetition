#include <iostream>
#include "Card.h"
#include "Scheduler.h"

int main()
{
    // test the rating enum
    std::cout << Rating::AGAIN << std::endl;
    
    // test time
    char* dt = asctime(Card::getUTCTime());
    std::cout << "The UTC date and time is:"<< dt << std::endl;
    return 0;
}