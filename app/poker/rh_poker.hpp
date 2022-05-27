


#ifndef RH_APP_POKER
#define RH_APP_POKER

namespace rh_poker{

enum class Suit : char{
    kSpade     = 0,\
    kDiamond   ,\
    kClub      ,\
    kHeart     ,\
    kJoker
};

struct Card{
    Suit  suit;
    char   num;
    Card( Suit s, char n ):suit(s),num(n){}
    Card():suit(Suit::kJoker),num(0){}
    Card( const Card& rhs):suit(rhs.suit),num(rhs.num){}
};

}




#endif
