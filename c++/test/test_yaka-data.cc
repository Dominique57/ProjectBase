#include <criterion/criterion.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <loader/fwd.hh>
#include <loader/data-bank.hh>

Test(YakaData, SimpleInput)
{
    loader::json input = {
            { "Prenom", "dominique" },
            { "Nom", "MICHEL" },
            { "Login", "dominique.michel" },
            { "Majeure", "MTI" },
            { "project", "Billeterie" }
    };

    // when
    loader::YakaData bank(input);
    // then
    cr_assert_str_eq(bank.login_get().c_str(), "dominique.michel");
}

Test(YakaData, SimpleInputNoPrpject)
{
    loader::json input = {
            { "Prenom", "dominique" },
            { "Nom", "MICHEL" },
            { "Login", "dominique.michel" },
            { "Majeure", "MTI" },
            { "project", "" }
    };

    // when
    loader::YakaData bank(input);
    // then
    cr_assert_str_eq(bank.login_get().c_str(), "dominique.michel");
}

Test(YakaData, BadSimpleInputType)
{
    loader::json input = {
            { "Prenom", "dominique" },
            { "Nom", "MICHEL" },
            { "Login", 10 },
            { "Majeure", "MTI" },
            { "projet", "Billeterie" }
    };

    // when / then
    cr_expect_throw(loader::YakaData bank(input),
                    nlohmann::json::type_error);
}

Test(YakaData, BadSimpleInputMissing)
{
    loader::json input = {
            { "Prenom", "dominique" },
            { "Nom", "MICHEL" },
            { "Majeure", "MTI" },
            { "projet", "Billeterie" }
    };

    // when / then
    cr_expect_throw(loader::YakaData bank(input),
                    nlohmann::json::out_of_range);
}