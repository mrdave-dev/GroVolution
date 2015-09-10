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

    stephBank.userSetName();    //should repeat (non-fatal)

    stephBank._fetchTimers(); //should throw fatal error

    return 0;
}
