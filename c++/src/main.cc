#include <iostream>
#include "argparse/argparse.hh"
#include "loader/data-loader.hh"
#include "loader/data-bank.hh"
#include "converter/converter.hh"
#include "scheduler/scheduler.hh"

int main(int argc, char** argv)
{
    try
    {
        // Handle parsing
        argparse::Argparse args(argc, argv);

        // Parse JSON file
        loader::DataBank bank;
        loader::DataLoader dataLoader(args.json_path_get());
        dataLoader.load_data(bank);

        // Reformat easier-manipulating data
        converter::Converter converter(bank);

        // compute output
        scheduler::Scheduler scheduler(converter);
        scheduler.convert_defences();
    }
    catch (std::runtime_error& e)
    {
        std::cerr << "[ERROR] " << e.what();
        return 1;
    }
    return 0;
}
