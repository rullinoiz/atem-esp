#include "Arduino.h"
#include "resources/SerialHandler.h"

#include <vector>

void SerialHandlerClass::runLoop() {
    if (!this->SerialStream.available()) return;
//    if (pointer + 1 > _buffer + bufferSize)

    *this->pointer = (char) this->SerialStream.read();
    this->SerialStream.print(*this->pointer);

    if ((*this->pointer == '\n' || *this->pointer == '\r') && !this->justRan) {
        *this->pointer = ' ';
        this->parseCommand(_buffer, _buffer - pointer);
        this->pointer = _buffer;
        memset(this->_buffer, 0, bufferSize);
        this->justRan = true;
    } else {
        if (this->justRan) {
            this->justRan = false;
            return;
        }
        this->pointer++;
        this->justRan = false;
    }
}

void SerialHandlerClass::parseCommand(char* buffer, uint8_t size) {
    std::string str(buffer, size), cmdName;

    cmdName = str.substr(0, str.find(' '));
    this->SerialStream.printf("\"%s\"\n", cmdName.c_str());

    CMD cmd = this->findCommand(cmdName);
    if (cmd.null) {
        this->SerialStream.println("Command not found");
        return;
    }

    str.erase(0, str.find(' ') + 1);

    std::vector<std::string> args;
    size_t pos;
    while ((pos = str.find(' ')) != std::string::npos) {
        auto s = str.substr(0, pos);
        args.push_back(s);
        str.erase(0, pos + 1);
    }

    this->SerialStream.printf("%d\n", args.size());

    for (auto& i : args) {
        this->SerialStream.printf("\"%s\"\n", i.c_str());
    }

    if (!cmd.handler(args, this)) {
        this->SerialStream.println("An error occurred running this command!");
    }
}

CMD SerialHandlerClass::findCommand(const std::string& name) {
    for (auto _command : this->_commands) {
        if (name == _command.name) {
            return _command;
        }
    }
    return (CMD){.null = true};
}

// silence clang
// NOLINTNEXTLINE(cppcoreguidelines-interfaces-global-init)
SerialHandlerClass SerialHandler(Serial);