// asaf0604@gmail.com 325362457
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "player.hpp"
#include "catan.hpp"
#include "board.hpp"
#include "deck.hpp"
#include "Houses.hpp"
#include "Road.hpp"
#include "Plot.hpp"

TEST_CASE("Player Initialization")
{
    Player p("Amit");
    CHECK(p.getName() == "Amit");
    CHECK(p.getVictoryPoints() == 0);
    CHECK(p.getResourceAmount("wood") == 0);
    CHECK(p.getResourceAmount("bricks") == 0);
}

TEST_CASE("Game Initialization")
{
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    CatanGame catan(p1, p2, p3);

    CHECK(&catan.get_turn() == &p1);

    catan.nextTurn();
    CHECK(&catan.get_turn() == &p2);

    catan.nextTurn();
    CHECK(&catan.get_turn() == &p3);
}

TEST_CASE("Player Actions")
{
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    CatanGame catan(p1, p2, p3);
    Board &board = catan.getBoard();

    SUBCASE("Placing Settlements and Roads")
    {
        p1.placeSettlement(10, board, catan);
        CHECK(p1.getVictoryPoints() == 1);

        p1.placeRoad(10, 11, board, p1, p2, p3, catan);
        CHECK(p1.getResourceAmount("wood") == 0);
        CHECK(p1.getResourceAmount("bricks") == 0);

        p1.placeSettlement(12, board, catan);
        CHECK(p1.getVictoryPoints() == 2);

        p1.placeRoad(12, 11, board, p1, p2, p3, catan);
        CHECK(p1.getResourceAmount("wood") == 0);
        CHECK(p1.getResourceAmount("bricks") == 0);
    }
}

TEST_CASE("Trading")
{
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    CatanGame catan(p1, p2, p3);

    p1.addResource("wood", 2);
    p2.addResource("bricks", 1);

    CHECK(p1.offerTrade(p2, "wood", 2, "bricks", 1, catan));
    CHECK(p1.getResourceAmount("wood") == 0);
    CHECK(p1.getResourceAmount("bricks") == 1);
    CHECK(p2.getResourceAmount("wood") == 2);
    CHECK(p2.getResourceAmount("bricks") == 0);
}

TEST_CASE("Development Cards")
{
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    CatanGame catan(p1, p2, p3);
    Deck deck;

    p1.addResource("wheat", 1);
    p1.addResource("sheep", 1);
    p1.addResource("ore", 1);

    CHECK_NOTHROW(p1.buyDevelopmentCard(deck, catan));

    p1.useDevelopmentCard(DevCardType::Knight, p1, p2, p3, catan);
    CHECK(p1.getVictoryPoints() == 0);
}

TEST_CASE("Building Cities")
{
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    CatanGame catan(p1, p2, p3);
    Board &board = catan.getBoard();

    p1.addResource("wheat", 2);
    p1.addResource("ore", 3);

    p1.placeSettlement(10, board, catan);
    p1.placeRoad(10, 11, board, p1, p2, p3, catan);

    p1.buildCity(10, board, catan);
    CHECK(p1.getVictoryPoints() == 2);
}

TEST_CASE("Advanced Trading and Resource Management")
{
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    CatanGame catan(p1, p2, p3);

    p1.addResource("wood", 5);
    p1.addResource("bricks", 5);
    p2.addResource("wheat", 5);
    p2.addResource("ore", 5);

    CHECK_FALSE(p1.offerTrade(p2, "wood", 5, "wheat", 5, catan)); // Trade should not be accepted because it's not beneficial enough

    CHECK(p1.offerTrade(p2, "wood", 3, "wheat", 2, catan));
    CHECK(p1.getResourceAmount("wood") == 2);
    CHECK(p1.getResourceAmount("wheat") == 2);
    CHECK(p2.getResourceAmount("wood") == 3);
    CHECK(p2.getResourceAmount("wheat") == 3);

    p1.placeSettlement(10, catan.getBoard(), catan);
    p1.placeRoad(10, 11, catan.getBoard(), p1, p2, p3, catan);
    CHECK(p1.getVictoryPoints() == 1);
}

TEST_CASE("Using Multiple Development Cards")
{
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    CatanGame catan(p1, p2, p3);
    Deck deck;

    p1.addResource("wheat", 2);
    p1.addResource("sheep", 2);
    p1.addResource("ore", 2);

    CHECK_NOTHROW(p1.buyDevelopmentCard(deck, catan));
    CHECK_NOTHROW(p1.buyDevelopmentCard(deck, catan));

    p1.useDevelopmentCard(DevCardType::Knight, p1, p2, p3, catan);
    p1.useDevelopmentCard(DevCardType::YearOfPlenty, p1, p2, p3, catan);

    CHECK(p1.getVictoryPoints() == 0);
}
