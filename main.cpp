#include <iostream>
#include <stdint.h>
#include "ec_access.h"
#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;

static constexpr uint32_t BAT_CONS_MODE = 0x44;
enum class EC_PORTS
{
    BAT_CONS_MODE_P1 = 0xEC,
    BAT_CONS_MODE_P2 = 0xED
};
enum class CHARGE_MODE
{
    FULL_CHARGE = 0,
    CONSERVATION_P1 = 0x20,
    CONSERVATION_P2 = 0x02
};
int getBatteryConservationMode(void)
{
    uint8_t reg1 = read_ec(uint32_t(EC_PORTS::BAT_CONS_MODE_P1));
    uint8_t reg2 = read_ec(uint32_t(EC_PORTS::BAT_CONS_MODE_P2));
    if(reg1 == uint8_t(CHARGE_MODE::CONSERVATION_P1) && reg2 == uint8_t(CHARGE_MODE::CONSERVATION_P2))
    {
        return 1;
    }
    else if(reg1 == uint8_t(CHARGE_MODE::FULL_CHARGE) && reg2 == uint8_t(CHARGE_MODE::FULL_CHARGE))
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

void setBatteryConservationMode(bool isConservMode)
{
    if(isConservMode)
    {
        //limit battery charge
        write_ec(uint32_t(EC_PORTS::BAT_CONS_MODE_P1), uint8_t(CHARGE_MODE::CONSERVATION_P1));
        write_ec(uint32_t(EC_PORTS::BAT_CONS_MODE_P2), uint8_t(CHARGE_MODE::CONSERVATION_P2));
    }
    else
    {
        //enable full charge
        write_ec(uint32_t(EC_PORTS::BAT_CONS_MODE_P1), uint8_t(CHARGE_MODE::FULL_CHARGE));
        write_ec(uint32_t(EC_PORTS::BAT_CONS_MODE_P2), uint8_t(CHARGE_MODE::FULL_CHARGE));
    }
}

void dump_all_regs(void)
{
    uint8_t val;
    printf("EC reg dump:");

    for(int i = 0x00; i <= 0xff; i++)
    {
        val = read_ec(i);
        printf("%02x\n", val);
    }
    printf("\n");
}

void show_info()
{
    std::cout << "Battery conservation mode:" << getBatteryConservationMode() << std::endl;
}

int main(int ac, char* av[])
{
    if(init() != 0)
    {
        printf("[ERROR]\t Failed to set permissions to access the port!\n");
        exit(1);
    }
    po::options_description desc("To enable/disable lenovo yoga 920 features.\nAllowed options");
    desc.add_options()
    ("help,h", "produce help message")
    ("dump,h", "dump the whole EC area")
    ("info,i", "Read known params from notebook")
    ("conserv,c", po::value<bool>(), "set battery conservation mode")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    if(vm.count("help"))
    {
        cout << desc << "\n";
        return 1;
    }
    if(vm.count("dump"))
    {
        dump_all_regs();
        return 1;
    }
    if(vm.count("info"))
    {
        show_info();
        return 1;
    }
    if(vm.count("conserv"))
    {
        bool setConserv = vm["conserv"].as<bool>();
        cout << "Setting battery conservation mode " << (setConserv ? "On" : "Off") << ".\n";
    }
    else
    {
        cout << desc << "\n";
        return 1;
    }
    return 0;
}
