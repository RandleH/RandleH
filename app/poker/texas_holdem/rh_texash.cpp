
#include "./rh_texash.hpp"



namespace rh_app{


texash evaluate( std::vector<rh_poker::Card> cards){
    assert( cards.size()==5 );    // Incorrect number of cards
    
    uint8_t len_suit_same  = 1;   // 相同牌面最长长度
    uint8_t len_suit_flush = 1;   // 顺子排面最长长度
    uint8_t len_num_same   = 1;   // 相同数字最长长度
    
    std::sort( cards.begin(), cards.end(), [](const rh_poker::Card& a, const rh_poker::Card& b){return a.num > b.num;});
    
    for( size_t i=1, ss=1, sf=1, ns=1; i<5; ++i ){
        if( cards[i].num==cards[i-1].num ){
            ++ns;
        }else{
            len_num_same = std::max( len_num_same, (uint8_t)ns);
            ns = 1;
        }
        
        if( cards[i].num-cards[i-1].num == 1 ){
            ++sf;
        }else{
            len_suit_flush = std::max( len_suit_flush, (uint8_t)sf);
            sf = 1;
        }
        
        if( cards[i].suit==cards[i-1].suit ){
            ++ss;
        }else{
            len_suit_same = std::max( len_suit_same, (uint8_t)ss);
            ss = 1;
        }
    }
    ???
    return texash::kOnePair;
}


};
