
#include <vector>
#include <queue>

#include "../rh_poker.hpp"

#ifndef RH_APP_TEXAS_HOLDEM
#define RH_APP_TEXAS_HOLDEM


namespace rh_app{

enum class texash : char{
    kHighCard  = 0,\
    kOnePair   ,\
    kTwoPair   ,\
    k3_kind    ,\
    kStraight  ,\
    kFlush     ,\
    kFullHouse ,\
    k4_kind    ,\
    kStraightFlush ,\
    kRoyalFlush
};

texash evaluate( const std::vector<rh_poker::Card> &cards);


};


#endif


