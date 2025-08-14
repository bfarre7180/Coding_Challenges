#include <iostream>
#include <string>
#include <cctype>

int parseObject();
int parseString();
int parseNumber();
int parseArray();

bool isNumber(char);

//-----------------State Enum's-----------------------------
enum class StringState : uint8_t {
    EXPECT_CHAR_OR_END,
    DONE
};

enum class NumberState : uint8_t {
    EXPECT_NEGATIVE_OR
    DONE
};

enum class ArrayState : uint8_t {

};

enum class JSONState : uint8_t {
    EXPECT_KEY_OR_END,     //State, Since a JSON object can contain 0 elements it can end here
    EXPECT_COLON,
    EXPECT_VALUE,
    EXPECT_COMMA_OR_END,
    DONE
};

int main() {
    return 0;
}

int parseObject() {

    JSONState state = JSONState::EXPECT_KEY_OR_END;

    char c;

    while(std::cin.get(c)) {
        if(isspace(c)) {
            continue;
        }
        switch(state) {

            case JSONState::EXPECT_KEY_OR_END:
                if(c == '"') {
                    if(!parseString()) {
                        return 1;
                    }
                    state = JSONState::EXPECT_COLON;
                } else if(c == '}') {
                    state = JSONState::DONE;
                } else {
                    std::cout << "Error, expected a key or '}'";
                    return 1;
                }
                break;

            case JSONState::EXPECT_COLON:
                if(c != ':') {
                    std::cout << "Error, expected a ':'";
                    return 1;
                }
                state = JSONState::EXPECT_VALUE;
                break;
            
            case JSONState::EXPECT_VALUE:
                switch(c) {
                    case '{':
                        if(!parseObject()) {
                            return 1;
                        }
                        break;
                    case '"':
                        if(!parseString()) {
                            return 1;
                        }
                        break;
                    case '[':
                        if(!parseArray()) {
                            return 1;
                        }
                        break;
                    case 't':
                        std::string true_string = "t";
                        int i = 0;
                        while(std::cin.get(c) && i < 3) {
                            true_string += c;
                        }
                        if(true_string != "true") {
                            std::cout << "Error, expected true";
                            return 1;
                        }
                        break;
                    case 'f':
                        std::string false_string = "f";
                        int i = 0;
                        while(std::cin.get(c) && i < 4) {
                            false_string += c;
                        }
                        if(false_string != "false") {
                            std::cout << "Error, expected false";
                            return 1;
                        }
                        break;
                    case 'n':
                        std::string null_string = "n";
                        int i = 0;
                        while(std::cin.get(c) && i < 3) {
                            null_string += c;
                        }
                        if(null_string != "null") {
                            std::cout << "Error, expected null";
                            return 1;
                        }
                        break;
                    default:
                        if(!isNumber(c)) {
                            std::cout << "Error with value, not recognized";
                            return 1;
                        }
                        if(!parseNumber()) {
                            std::cout << "Error with value, expected number";
                            return 1;
                        }
                        break;
                state = JSONState::EXPECT_COMMA_OR_END;
                break;
            
            case JSONState::EXPECT_COMMA_OR_END:
                if(c == ',') {
                    state = JSONState::EXPECT_KEY_OR_END;
                } else if (c == '}') {
                    state = JSONState::DONE;
                } else {
                    std::cout << "Error expected a comma or end of object";
                    return 1;
                }
                break;
            
            case JSONState::DONE:
                std::cout << "Successfully parsed JSON object";
                return 0;
                break;
            
            default:
                std::cout << "Error Parsing Object, Default state not defined" << std::endl;
                return 1;
                break;
        }
    }
    return 1;
}

int parseString() {
    
    char c;
    StringState state = StringState::EXPECT_CHAR_OR_END;
    
    while(std::cin.get(c)) {
        if (isspace(c)) {
            continue;
        }
        switch(state) {
            case StringState::EXPECT_CHAR_OR_END:
                if(c == '"') {
                    state = StringState::END;
                }
                break;
            case StringState::END;
                return 0;
                break;
            default:
                return 1;
                break;
        }
    return 1;
}

int parseNumber(std::string token) {
    
    char c;
    NumberState state = 
    return 0;
}

int parseArray() {
    return 0;
}

bool isNumber(char c) {
    return c == '-' || (c <= 57 && c >= 48);
}
