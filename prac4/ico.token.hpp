#pragma once

#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <string>

using namespace eosio;

namespace icotoken {

   class [[eosio::contract("icotoken")]] token : public eosio::contract {
      private:
         struct [[eosio::table]] account{
             name        owner;
             asset       balance;

             uint64_t primary_key()const { return owner.value; }
         };

         struct [[eosio::table]] record{
             uint64_t      id;
             name          from;
             name          to;
             asset         amount;
             std::string   memo;

             uint64_t primary_key()const { return id; }
         };

         typedef eosio::multi_index< "accounts"_n, account > _accounts;
         typedef eosio::multi_index< "record"_n, record > _record;

         void add_balance( name payer, name to, asset q, std::string);
         void sub_balance( name payer, name to, asset q, std::string);

      public:
         using contract::contract;

         [[eosio::action]]
         void issue( name to, asset quantity, std::string memo);

         [[eosio::action]]
         void transfer( name from, name to, asset quantity, std::string memo);

         [[eosio::action]]
         void invest( name from, asset quantity, std::string memo);

   };
}
