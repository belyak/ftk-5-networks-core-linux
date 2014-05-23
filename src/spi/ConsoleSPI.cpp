#include "ConsoleSPI.h"
#include "commands/CommandResponse.h"

#include <stdio.h>
#include <iostream>
using std::cout;
using std::cin;
using std::flush;

void ConsoleSPI::send_message(const int code, wstring data) {
    CommandResponse * cr = new CommandResponse(code, data);
    cout << this->encoder.decode(cr->raw()) << flush;
    delete cr;
}

void ConsoleSPI::send_message(CommandResponse& response) {
    cout << this->encoder.decode(response.raw()) << flush;
}

unsigned char ConsoleSPI::read_byte(bool& read_ok) {
    int result = fgetc(stdin);
    if (result != EOF) {
        read_ok = true;
        return (unsigned char) result;
    } else {
        read_ok = false;
        return 0;
    }
}

ConsoleSPI::ConsoleSPI() {
	
}
