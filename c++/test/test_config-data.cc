#include <criterion/criterion.h>
#include <loader/data-bank.hh>
#include <iostream>
#include <loader/fwd.hh>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <nlohmann/json.hpp>

Test(ConfigData, SimpleInput)
{
    loader::json input = {
            { "name", "Billeterie" },
            { "time", 30 },
            { "begin", "2019-04-29T00:00:00Z" }
    };

    // when
    loader::ConfigData bank(input);
    // then
    cr_assert_str_eq(bank.name_get().c_str(), "Billeterie");
    cr_assert_eq(bank.duration_get().minutes(), 30);
    std::string result("2019-04-29 00:00:00");
    boost::posix_time::ptime time(boost::posix_time::time_from_string(result));
    cr_assert_eq(bank.start_get(), time);
}

Test(ConfigData, BadSimpleInputType)
{
    loader::json input = {
            { "name", "Billeterie" },
            { "time", "BAD_TYPE" },
            { "begin", "2019-04-29T00:00:00Z" }
    };

    // when / then
    cr_expect_throw(loader::ConfigData bank(input), nlohmann::json::type_error);
}

Test(ConfigData, BadSimpleInputMissing)
{
    loader::json input = {
            { "name", "Billeterie" },
            { "begin", "2019-04-29T00:00:00Z" }
    };

    // when / then
    cr_expect_throw(loader::ConfigData bank(input),
            nlohmann::json::out_of_range);
}
