#include "../RS-232/rs232.h"
#include "../headers/comms.h"
#include "../headers/relay.h"
#include "../headers/bank.h"
#include "../headers/error.h"

int main()
{ 

    std::vector<gv_error*> gv_errors;

    load_errors("errors.txt", gv_errors);
    
    Bank stephBank;
    stephBank._setConnection(new RS232Connection(38400, 16));


    stephBank.remove();   

    std::cout << "Success!!!" << std::endl;

    stephBank.on();   

    std::cout << "Success!!!" << std::endl;

    stephBank.off();   

    std::cout << "Success!!!" << std::endl;


    return 0;
}
