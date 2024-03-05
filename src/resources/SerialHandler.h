#include <list>
#include <vector>
#include <HardwareSerial.h>


class SerialHandlerClass; // so that i may refer to the class in the struct just underneath

typedef struct {
    char name[16];
    bool (*handler)(std::vector<std::string>&, SerialHandlerClass*);
    bool null;
} CMD;

class SerialHandlerClass {
protected:
    static const uint8_t bufferSize = 64;
    char _buffer[bufferSize] = {};
    char* pointer = _buffer;
    std::list<CMD> _commands;
    Stream& SerialStream;
    bool justRan = false;

public:
    void runLoop();

    inline void begin(std::list<CMD>& commands) {
        this->_commands = commands;
    }
    inline Stream& getSerial() {
        return this->SerialStream;
    }
    explicit inline SerialHandlerClass(Stream& SerialStream) : SerialStream(SerialStream) {
        memset(_buffer, 0, 64);
    };

protected:
    void parseCommand(char* buffer, uint8_t size);
    CMD findCommand(const std::string& name);

};


extern SerialHandlerClass SerialHandler;

