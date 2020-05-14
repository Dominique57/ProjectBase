#include <criterion/criterion.h>
#include <lib/time-tools.hh>

Test(TimeTools, simepleTimeConvert)
{
    // given
    std::string time("2019-04-29T00:00:00Z");
    // when
    auto const& result = TimeTools::DateFromStringIso8601(time);
    // then
    cr_assert_eq(result.date().year(), 2019);
    cr_assert_eq(result.date().month(), 4);
    cr_assert_eq(result.date().day(), 29);
    cr_assert_eq(result.time_of_day().hours(), 00);
    cr_assert_eq(result.time_of_day().minutes(), 00);
    cr_assert_eq(result.time_of_day().seconds(), 00);
}