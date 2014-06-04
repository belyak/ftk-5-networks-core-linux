#include <iostream>
#include <string>

#include <stdlib.h>
#include <stdio.h>
#include <sstream>

#include "../SPI.h"
#include "SPICommand.h"
#include "CommandResponse.h"
#include "../../engine/Statistics.h"

#include "../create_message.h"
#include "../../lgs_constants.h"


void SPICommand::init(Statistics & statistics, Encoder * encoder, SPI * spi, std::string keyword) {
    this->statistics = &statistics;
    this->encoder = encoder;
    this->keyword = keyword;
    this->spi = spi;
}

std::string SPICommand::get_keyword() {
    return keyword;
}

std::string SPICommand::get_rest() {
    static std::string rest;
    rest = this->current_line.replace(0, this->keyword.length() + 1, "");
    return rest;
}

void SPICommand::set_current_line(std::string current_line) {
    this->current_line = std::string(current_line);
}

CommandResponse * SPICommand::run() {
    return new CommandResponse(200, L"Abstract response");  
}


CommandResponse * VersionCommand::run() { 
    return new CommandResponse(200, SERVER_VERSION);
}

CommandResponse * ExitCommand::run() {
    return new CommandResponse(200, L"Good bye!");
}

CommandResponse * PutLineCommand::run() {
    std::string rest = get_rest();
    
    std::wstring line = this->encoder->encode(rest);
    
    std::cout << " going to putLine, len:" << line.length() << std::endl;
    this->statistics->putLine(line);
    int lCount = this->statistics->getLinesCount();
    std::wstringstream wss;
    wss << L"line has been collected (" << lCount << L" at the moment).";
    return new CommandResponse(200, wss.str());
}

CommandResponse * PutTextCommand::run() {
    std::string rest = get_rest();
    std::wstring endMarker = this->encoder->encode(rest);
    std::cout << "Marker found" << std::endl;
    int collectedLinesCount = 0;
    while (true) {
        std::string inLine(this->spi->read_line());
        
        std::wstring line = this->encoder->encode(inLine);
        
        if (line.find(endMarker) != line.npos) {
            std::cout << "Marker has been found!" << std::endl;
            break;
        } else {
            this->statistics->putLine(line);
            collectedLinesCount++;
            std::cout << "line collected (" << collectedLinesCount << ")" << std::endl;
        }
    }
    
    int totalLinesCount = this->statistics->getLinesCount();
    std::cout << "Here" << std::endl;
    std::wstringstream wss;
    wss << collectedLinesCount << L" lines has been collected (" << totalLinesCount << L" total)";
    return new CommandResponse(200, wss.str());
}

CommandResponse * ClearBufferCommand::run() {
    this->statistics->clearBuffer();
    return new CommandResponse(200, L"Buffer has been cleared.");
}

CommandResponse * CalcCommand::run() {
    this->statistics->calculate();
    std::wstringstream wss;
    int lCount = this->statistics->getLinesCount();
    int wCount = this->statistics->getWordsCount();
    wss << L"Calculated (" << lCount << L" lines, " << wCount << L" words)";
    return new CommandResponse(200, wss.str());
}

CommandResponse * SetEncodingCommand::run() {
    std::string encoding = get_rest();
    std::wstring w_encoding = std::wstring(encoding.begin(), encoding.end());
    
    bool setEncodingResult = encoder->setEncoding(encoding.c_str());
    std::wstringstream wss;
    if (setEncodingResult) {
        wss << L"Encoding has been changed to `" << w_encoding << "`";
        return new CommandResponse(200, wss.str());
    } else {
        wss << L"Unable to find/set encoding`" << w_encoding << "`!!!";
        return new CommandResponse(404, wss.str());
    }
}

CommandResponse * SetTransferModeCommand::run() {
    return new CommandResponse(400, L"Not implemented in c++ version yet!");
}

CommandResponse * PrintStatisticsCommand::run() {
    StatisticsMap & statistics_map = this->statistics->data;
    unsigned int lines_count = statistics_map.size();
    if (lines_count > 1) {
        std::wstring * lines = new std::wstring[lines_count];
        int i = 0;
        for (StatisticsMap::iterator e = statistics_map.begin(); e != statistics_map.end(); e++) {
            StatisticsEntry entry = *e;
            std::wstringstream wss;
            wss << entry.first << L" " << entry.second;
            lines[i] = wss.str();
            i++;
        }
        return new CommandResponse(200, lines, lines_count);
    } else if (lines_count == 1) {
        std::wstringstream wss;
        StatisticsEntry entry = *statistics_map.begin();
        wss << entry.first << L" " << entry.second;
        return new CommandResponse(200, wss.str());
    } else { // lines_count == 0
        return new CommandResponse(200, L"");
    }
}


CommandResponse * SaveCommand::run() {
    std::string rest = get_rest();
    std::wstring name = encoder->encode(rest);
    
    if (name.length() == 0) {
        return new CommandResponse(400, L"You should provide name");
    }
    
    this->statistics->save(name);
    
    std::wstringstream wss;
    wss << L"Statistics \"" << name << L"\" has been saved";
    
    return new CommandResponse(200, wss.str());
}

CommandResponse * LoadCommand::run() {
    std::string rest = get_rest();
    std::wstring name = encoder->encode(rest);
    
    if (name.length() == 0) {
        return new CommandResponse(400, L"You should provide name!!!");
    }
    
    bool isLoaded = this->statistics->load(name);
    
    std::wstringstream wss;
    if (isLoaded) {
        wss << L"Statistics \"" << name << L"\" has been loaded.";
        return new CommandResponse(200, wss.str());
    } else {
        wss << L"Statistics \"" << name << L"\" has not been loaded!!!";
        return new CommandResponse(404, wss.str());
    }
}


CommandResponse * MergeCommand::run() {
    std::string rest = get_rest();
    std::wstring name = encoder->encode(rest);
    std::wstringstream wss;
    
    
    if (name.length() == 0) {
        return new CommandResponse(400, L"You should provide name!!!");
    }
    
    Statistics anotherStatistics(L"Another");
    bool isLoaded = anotherStatistics.load(name);
    
    if (!isLoaded) {
        wss << L"Statistics \"" << name << L"\" has not been loaded!!!";
        return new CommandResponse(404, wss.str());
    } else {
        this->statistics->merge(anotherStatistics);
        wss << L"Statistics \"" << name << L"\" has been merge into current";
        return new CommandResponse(200, wss.str());
    }
}


RegisteredCommands init_registered_commands(Statistics & statistics, Encoder & encoder, SPI * spi) {
    
    static RegisteredCommands registered_commands;
    
    #define REGISTER_CMD(CMD_CLS, CMD_KW) { SPICommand * cmd = new CMD_CLS(); \
    cmd->init(statistics, &encoder, spi, #CMD_KW); \
    registered_commands[cmd->get_keyword()] = cmd; }
    
    REGISTER_CMD(VersionCommand, ver);
    REGISTER_CMD(ExitCommand, exit);
    REGISTER_CMD(PutLineCommand, pl);
    REGISTER_CMD(PutTextCommand, pt);
    REGISTER_CMD(ClearBufferCommand, cl);
    REGISTER_CMD(CalcCommand, calc);
    REGISTER_CMD(PrintStatisticsCommand, ps);
    REGISTER_CMD(SaveCommand, st);
    REGISTER_CMD(LoadCommand, ld);
    REGISTER_CMD(MergeCommand, mrg);
    REGISTER_CMD(SetEncodingCommand, enc);
    REGISTER_CMD(SetTransferModeCommand, mode)
    
    return registered_commands;
}