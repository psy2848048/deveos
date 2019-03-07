#pragma once

#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/time.hpp>
#include <string>

using namespace eosio;

class [[eosio::contract("simpletoken")]] token : public eosio::contract {
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

        struct [[eosio::table]] checkpoint {
            name owner;
            uint32_t time_sec;
            asset balance;

            uint64_t primary_key() const { return owner.value; }
        };

        struct [[eosio::table]] authority {
            name authorized;

            uint64_t primary_key() const { return authorized.value; }
        };

        typedef eosio::multi_index< "accounts"_n, account > _accounts;
        typedef eosio::multi_index< "record"_n, record > _record;
        typedef eosio::multi_index< "checkpoints"_n, checkpoint > _checkpoints;
        typedef multi_index< "authorities"_n, authority > _authorities;

        void add_balance( name payer, name to, asset q, std::string);
        void sub_balance( name payer, name to, asset q, std::string);
        void check_auth( name sender );

    public:
        using contract::contract;

        [[eosio::action]]
            void issue( name self, name to, asset quantity, std::string memo);

        [[eosio::action]]
            void transfer( name from, name to, asset quantity, std::string memo);

        [[eosio::action]]
            void delrecord( uint64_t rec_id);

        [[eosio::action]]
            void createchkpt( name self );

        [[eosio::action]]
            void addauth( name authorizing );
        [[eosio::action]]
            void delauth( name authorized );
};
