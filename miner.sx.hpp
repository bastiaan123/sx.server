#pragma once

#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>

#include <optional>

using namespace eosio;
using namespace std;

class [[eosio::contract("miner.sx")]] minerSx : public contract {
public:
    using contract::contract;

    [[eosio::action]]
    void mine( const name executor, const optional<symbol_code> symcode );

    [[eosio::action]]
    void rewards( const string pair_id );

    [[eosio::action]]
    void profit( const name contract, const symbol_code symcode );

    [[eosio::action]]
    void repay( const name contract, const asset quantity );

    [[eosio::on_notify("flash.sx::callback")]]
    void on_callback( const name to, const name contract, asset quantity, const string memo, const name recipient );

    using mine_action = eosio::action_wrapper<"mine"_n, &minerSx::mine>;
    using rewards_action = eosio::action_wrapper<"rewards"_n, &minerSx::rewards>;
    using profit_action = eosio::action_wrapper<"profit"_n, &minerSx::profit>;
    using repay_action = eosio::action_wrapper<"repay"_n, &minerSx::repay>;

private:
    void transfer( const name from, const name to, const name contract, const asset quantity, const string memo );

    // miner actions
    void box_swap_arb( const name contract, const asset quantity );
    bool sx_to_defibox( const name contract, const asset quantity );
    bool defibox_to_dfs( const asset quantity, const uint8_t pair_id, const uint8_t mid );
};