#include <criterion/criterion.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <loader/fwd.hh>
#include <loader/data-bank.hh>

Test(StudentData, SimpleInput)
{
    loader::json input = {
            { "chef", "login.1" },
            { "login", "login.1" },
            { "class", "C1" },
            { "project", "Billeterie" }
    };

    // when
    loader::StudentData bank(input);
    // then
    cr_assert_str_eq(bank.login_get().c_str(), "login.1");
}

Test(StudentData, BadSimpleInputType)
{
    loader::json input = {
            { "chef", "login.1" },
            { "login", "login.1" },
            { "class", 10 },
            { "project", "Billeterie" }
    };

    // when / then
    cr_expect_throw(loader::StudentData bank(input),
            nlohmann::json::type_error);
}

Test(StudentData, BadSimpleInputMissing)
{
    loader::json input = {
            { "chef", "login.1" },
            { "login", "login.1" },
            { "project", "Billeterie" }
    };

    // when / then
    cr_expect_throw(loader::StudentData bank(input),
                    nlohmann::json::out_of_range);
}
