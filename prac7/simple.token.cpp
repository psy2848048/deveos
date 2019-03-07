#include "simple.token.hpp"

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

void token::check_auth(name self) {
    require_auth(self);
    _authorities auth(_self, _self.value);

    auto itr = auth.find(self.value);
    eosio_assert(itr != auth.end(), "You do not have authority for this function.");
}


void token::issue( name self, name to, asset q, std::string memo){
    check_auth(self);

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
    require_auth( from );
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

void token::delrecord(uint64_t rec_id){
    _record rec(_self, _self.value);

    auto itr = rec.find( rec_id );
    rec.erase( itr );
}

/*
 * Name: void token::createchkpt()
 * Usage: Updates checkpoints table with every accounts' balance and epoch second
 */

void token::createchkpt(name self) {
    check_auth(self);
    _accounts acc( _self, _self.value );
    _checkpoints chkpt( _self, _self.value);

    // Class built in <eosiolib/time.hpp>
    time_point_sec tps(now());

    for ( auto& acnt : acc ) {
        auto it = chkpt.find( acnt.owner.value );
        if( it == chkpt.end() ) {
            chkpt.emplace( _self, [&]( auto& a ){
                    a.owner = acnt.owner;
                    a.time_sec = tps.sec_since_epoch();
                    a.balance = acnt.balance;
                    });
        } else {
            chkpt.modify( it, same_payer, [&]( auto& a ) {
                    a.owner = acnt.owner;
                    a.time_sec = tps.sec_since_epoch();
                    a.balance = acnt.balance;
                    });
        }
    }
}

void token::addauth(name authorizing) {
    require_auth( _self );
    _authorities auth( _self, _self.value);

    auto itr = auth.find( authorizing.value );
    eosio_assert(itr == auth.end(), "That account is already authorized");


    auth.emplace( _self, [&]( auto& a ){
            a.authorized = authorizing;
            });
}

void token::delauth(name authorized) {
    require_auth( _self );
    _authorities auth(_self, _self.value);

    auto itr = auth.find( authorized.value );
    auth.erase( itr );
}


EOSIO_DISPATCH( token, (issue)(transfer)(delrecord)(createchkpt)(addauth)(delauth) )
