#include "simple.token.hpp"
#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <string>

using namespace eosio;
namespace simpletoken {
void token::add_balance(name payer, name to, asset q, std::string memo){
    _accounts acc(_self, _self.value);

    auto toitr = acc.find( to.value );
    if (toitr == acc.end() ){
        acc.emplace(payer, [&]( auto& a ){
            a.owner = to;
            a.balance = q;
        });
    } else {
        acc.modify(toitr, _self, [&]( auto& a ){
            a.balance += q;
            eosio_assert( a.balance >= q, "overflow detected" );
        });
    }
}

void token::sub_balance(name payer, name to, asset q, std::string memo){
    _accounts acc(_self, _self.value);

    auto toitr = acc.find( to.value );
    acc.modify( toitr, _self, [&]( auto& a ){
        eosio_assert(a.balance >= q, "Not enough token balance" );
        a.balance -= q;
    });
}

void token::issue( name to, asset q, std::string memo){
    add_balance( _self, to, q, memo);
    _record rec(_self, _self.value);

    rec.emplace(_self, [&](auto& a){
        a.id = rec.available_primary_key();
        a.from = _self;
        a.to = to;
        a.amount = q;
        a.memo = memo;
    });
}

void token::transfer( name from, name to, asset q, std::string memo){
    add_balance( from, to, q, memo);
    sub_balance( to, from, q, memo);
    _record rec(_self, _self.value);

    rec.emplace(from, [&](auto& a){
        a.id = rec.available_primary_key();
        a.from = from;
        a.to = to;
        a.amount = q;
        a.memo = memo;
    });
}

}
EOSIO_DISPATCH( simpletoken::token, (issue)(transfer) )
