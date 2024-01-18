#include "Card.h"

tm* Card::getUTCTime()
{
    time_t now = time(0);
    tm *gmtm = gmtime(&now);
    return gmtm;
}