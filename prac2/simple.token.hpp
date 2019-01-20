#pragma once

#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <string>

using namespace eosio;

namespace simpletoken {

   class [[eosio::contract("simpletoken")]] token : public eosio::contract {
      private:
         struct [[eosio::table]] account{
             name        owner;
             asset       balance;

             uint64_t primary_key()const { return owner.value; }
         };

         typedef eosio::multi_index< "accounts"_n, account > _accounts;

         void add_balance( name payer, name to, asset q, std::string);
         void sub_balance( name payer, name to, asset q, std::string);

      public:
         using contract::contract;

         [[eosio::action]]
         void issue( name to, asset quantity, std::string memo);

         [[eosio::action]]
         void transfer( name from, name to, asset quantity, std::string memo);

   };
}
