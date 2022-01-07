// This file is part of the Luau programming language and is licensed under MIT License; see LICENSE.txt for details
#include "Luau/Symbol.h"
#include "Luau/Ast.h"

#include "Fixture.h"

#include "doctest.h"

using namespace Luau;

TEST_SUITE_BEGIN("SymbolTests");

TEST_CASE("hashing_globals")
{
    std::string s1 = "name";
    std::string s2 = "name";

    // These two names point to distinct memory areas.
    AstName one{s1.data()};
    AstName two{s2.data()};

    Symbol n1{one};
    Symbol n2{two};

    CHECK(n1 == n1);
    CHECK(n1 == n2);
    CHECK(n2 == n2);

    CHECK_EQ(std::hash<Symbol>()(one), std::hash<Symbol>()(one));
    CHECK_EQ(std::hash<Symbol>()(one), std::hash<Symbol>()(two));
    CHECK_EQ(std::hash<Symbol>()(two), std::hash<Symbol>()(two));

    std::unordered_map<Symbol, int> theMap;
    theMap[n1] = 5;
    theMap[n2] = 1;

    REQUIRE_EQ(1, theMap.size());
}

TEST_CASE("hashing_locals")
{
    std::string s1 = "name";
    std::string s2 = "name";

    // These two names point to distinct memory areas.
    AstLocal one{AstName{s1.data()}, Location(), nullptr, 0, 0, nullptr};
    AstLocal two{AstName{s2.data()}, Location(), &one, 0, 0, nullptr};

    Symbol n1{&one};
    Symbol n2{&two};

    CHECK(n1 == n1);
    CHECK(n1 != n2);
    CHECK(n2 == n2);

    CHECK_EQ(std::hash<Symbol>()(&one), std::hash<Symbol>()(&one));
    CHECK_NE(std::hash<Symbol>()(&one), std::hash<Symbol>()(&two));
    CHECK_EQ(std::hash<Symbol>()(&two), std::hash<Symbol>()(&two));

    std::unordered_map<Symbol, int> theMap;
    theMap[n1] = 5;
    theMap[n2] = 1;

    REQUIRE_EQ(2, theMap.size());
}

TEST_SUITE_END();
