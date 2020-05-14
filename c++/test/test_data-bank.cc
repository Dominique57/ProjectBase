#include <criterion/criterion.h>
#include <loader/data-loader.hh>
#include <loader/data-bank.hh>
#include <iostream>
#include <fstream>

Test(DataBankTest, CountResult)
{
    loader::DataBank bank;
    loader::DataLoader data_loader("information.json");
    // when
    data_loader.load_data(bank);
    // then
    cr_assert_eq(bank.configs_get().size(), 3);
    cr_assert_eq(bank.classes_get().size(), 14);
    cr_assert_eq(bank.students_get().size(), 504);
    cr_assert_eq(bank.yakas_get().size(), 34);
}
