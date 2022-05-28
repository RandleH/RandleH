
#include "./rh_texash.hpp"



namespace rh_app{


texash evaluate( std::vector<rh_poker::Card> cards){
    assert( cards.size()==5 );    // Incorrect number of cards
    
    uint8_t len_suit_same    = 1;   // 相同牌面最长长度
    uint8_t len_num_straight = 1;   // 顺子排面最长长度
    uint8_t len_num_same     = 1;   // 相同数字最长长度
    
    std::sort( cards.begin(), cards.end(), [](const rh_poker::Card& a, const rh_poker::Card& b){return a.num > b.num;});
    
    
    uint8_t buf[4] = {0};
    for( size_t i=0, sf=1, ns=1; i<=5; ++i ){
        if( i==5 ){
            len_num_same     = std::max( len_num_same    , (uint8_t)ns);
            len_num_straight = std::max( len_num_straight, (uint8_t)sf);
            break;
        }
        if( i==0 ) goto CNT_SUIT;
        if( cards[i].num==cards[i-1].num ){
            ++ns;
        }else{
            len_num_same = std::max( len_num_same, (uint8_t)ns);
            ns = 1;
        }
        
        if( cards[i].num-cards[i-1].num == 1 ){
            ++sf;
        }else{
            len_num_straight = std::max( len_num_straight, (uint8_t)sf);
            sf = 1;
        }
CNT_SUIT:
        if( cards[i].suit!=rh_poker::Suit::kJoker )
            ++buf[ (int)(cards[i].suit) ];
    }
    for( size_t i=0; i<4; ++i ){
        len_suit_same = std::max( len_suit_same, buf[i]);
    }
    
    if( len_suit_same==5 && len_num_straight==5 && len_num_same==1 ){  // 同花顺
        if( cards[0].num==10 && cards[0].suit==rh_poker::Suit::kHeart )
            return texash::kRoyalFlush;
        return texash::kStraightFlush;
    }
    
    if( len_num_same==4 ){       // 炸弹
        return texash::k4_kind;
    }
    
    if( len_num_same==3 ){       // 有三张牌相同数字
        if( (cards[0].num==cards[1].num && cards[0].num!=cards[2].num) ||
            (cards[4].num==cards[3].num && cards[4].num!=cards[2].num) )
            return texash::kFullHouse;
        return texash::k3_kind;
    }
    
    if( len_suit_same==5 ){      // 有五张牌相同牌面
        return texash::kFlush;
    }
    
    if( len_num_straight==5 ){   // 顺子
        return texash::kStraight;
    }
    
    if( len_num_same==2 ){
        if( (cards[0].num==cards[1].num && cards[2].num==cards[3].num) ||
            (cards[1].num==cards[2].num && cards[3].num==cards[4].num) ||
            (cards[0].num==cards[1].num && cards[3].num==cards[4].num)){
            return texash::kTwoPair;
        }
        return texash::kOnePair;
    }
    
    return texash::kHighCard;
}


};
