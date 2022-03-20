#pragma once
#include <string>
#include <array>

enum class AddressFamily{
    IPV4 = 4,
    IPV6 = 6
};

class IPAddress{
    public:

    IPAddress() = delete;

    IPAddress(const std::string& ipString)
    {
        if(IsIPV4(ipString)){
            addrFamily = AddressFamily::IPV4;
        }
        else if(IsIPV6(ipString)){
            addrFamily = AddressFamily::IPV6;
        }
        else{
            throw std::invalid_argument("ipString has to be a valid IPV4 or IPV6 address");
        }
        ipBytes = IpStringToIpBytes(ipString);
    }

    IPAddress(std::array<uint8_t, 16> ip, AddressFamily family){
        this->ipBytes = ip;
        this->addrFamily = family;
    }

    AddressFamily AddrFamily(){
        return addrFamily;
    }

    friend bool operator==(const IPAddress& a, const IPAddress& b);

    std::string ToString(){

        std::string result = "";
        if(addrFamily == AddressFamily::IPV4){
            for(int i = 0; i < 4; ++i){
                result += std::to_string(ipBytes[i]);
                result += ".";
            }
            result.pop_back();
        }

        else if(addrFamily == AddressFamily::IPV6){
            int currentByte = 1;
            std::string cache = "";
            for(uint8_t byte : ipBytes){

                uint8_t firstHalf = byte>>4;
                uint8_t secondHalf = 0x0F & byte;
                cache.push_back(IntToHexaDigit(firstHalf));
                cache.push_back(IntToHexaDigit(secondHalf));

                if(currentByte == 2){
                    result += cache;
                    cache = "";
                    result.push_back(':');
                    currentByte = 1;
                }
                else{
                    currentByte++;
                }
            }
            result.pop_back();
        }

        return result;
    }

    std::array<uint8_t, 16> Bytes(){
        return ipBytes;
    }

    static uint8_t HexaDigitToInt(char c){
        switch(c){
            case '0': return 0;
            case '1': return 1;
            case '2': return 2;
            case '3': return 3;
            case '4': return 4;
            case '5': return 5;
            case '6': return 6;
            case '7': return 7;
            case '8': return 8;
            case '9': return 9;
            case 'a':
            case 'A': return 10;
            case 'b':
            case 'B': return 11;
            case 'c':
            case 'C': return 12;
            case 'd':
            case 'D': return 13;
            case 'e':
            case 'E': return 14;
            case 'f':
            case 'F': return 15;
            default: throw std::invalid_argument("argument was not a valid hexadecimal digit");
        }
    }

    static char IntToHexaDigit(uint8_t i){
        switch(i){
            case 0: return '0';
            case 1: return '1';
            case 2: return '2';
            case 3: return '3';
            case 4: return '4';
            case 5: return '5';
            case 6: return '6';
            case 7: return '7';
            case 8: return '8';
            case 9: return '9';
            case 10: return 'A';
            case 11: return 'B';
            case 12: return 'C';
            case 13: return 'D';
            case 14: return 'E';
            case 15: return 'F';
            default: throw std::invalid_argument("hexa int value has to be 0-15");
        }
    }

    private:

    bool IsIPV4(const std::string& ipString){
        if(ipString == "localhost"){
            return true;
        }
        if(ipString.find(".") == std::string::npos){
            return false;
        }
        return true;
    }
    bool IsIPV6(const std::string& ipString){
        if(ipString.find(":") == std::string::npos){
            return false;
        }
        return true;
    }

    std::array<uint8_t, 16> IpStringToIpBytes(const std::string& ipString){
        if(IsIPV4(ipString)){
            return Ip4StringToIpBytes(ipString);
        }
        else if(IsIPV6(ipString)){
            return Ip6StringToIpBytes(ipString);
        }
        else{
            throw std::invalid_argument("ipString has to be a valid IPV4 or IPV6 address");
        }
    }

    std::array<uint8_t, 16> Ip4StringToIpBytes(const std::string& ipString){
        std::array<uint8_t, 16> result = std::array<uint8_t, 16>();
        if(ipString == "localhost"){
            result[0] = 127; result[1] = 0; result[2] = 0; result[3] = 1;
            return result;
        }

        if(ipString.size() > 15){
            throw std::invalid_argument("ipString has to be a valid IPV4 or IPV6 address");
        }
        if(ipString.size() < 7){
            throw std::invalid_argument("ipString has to be a valid IPV4 or IPV6 address");
        }
        if(std::count(ipString.begin(), ipString.end(), '.') != 3){
            throw std::invalid_argument("ipString has to be a valid IPV4 or IPV6 address");
        }

        std::string subString = "";
        int index = 0;
        for(int i = 0; i < ipString.size(); ++i){
            char c = ipString[i];
            if(c == '.' || i == ipString.size()-1) {
                if(i == ipString.size() -1){
                    subString += c;
                }
                try{
                    int ipPart = std::stoi(subString);
                    if(ipPart > 255 || ipPart < 0){
                        throw std::invalid_argument("ipString has to be a valid IPV4 or IPV6 address");
                    }
                    result[index] = ipPart;
                }
                catch(...){
                    throw std::invalid_argument("ipString has to be a valid IPV4 or IPV6 address");
                }
                ++index;
                subString = "";
                continue;
            }
            subString += c;
        }

        return result;
    }

    std::array<uint8_t, 16> Ip6StringToIpBytes(const std::string& ipString){
        std::array<uint8_t, 16> result = std::array<uint8_t, 16>();
        if(ipString == "::1"){
            result[15] = 1;
            return result;
        }

        if(ipString.size() > 39){
            throw std::invalid_argument("ipString has to be a valid IPV4 or IPV6 address");
        }

        if(std::count(ipString.begin(), ipString.end(), ':') != 7){
            throw std::invalid_argument("ipString has to be a valid IPV4 or IPV6 address");
        }

        int index = 0;
        bool firstHalf = true;
        uint8_t currentByte = 0;
        int digitsInFrontOfColon = 0;
        for(char c : ipString){
            if(c == ':'){
                if(digitsInFrontOfColon != 4 && digitsInFrontOfColon != 0){
                    throw std::invalid_argument("ipString has to be a valid IPV4 or IPV6 address");
                }
                if(digitsInFrontOfColon == 0){
                    index += 2;
                }
                digitsInFrontOfColon = 0;
                currentByte = 0;
                continue;
            }
            else{
                try{
                    if(firstHalf){
                        currentByte = HexaDigitToInt(c)<<4;
                        firstHalf = false;
                    }
                    else{
                        currentByte += HexaDigitToInt(c);
                        firstHalf = true;
                        result[index] = currentByte;
                        index++;
                    }
                }
                catch(...){
                    throw std::invalid_argument("ipString has to be a valid IPV4 or IPV6 address");
                }
                ++digitsInFrontOfColon;
            }
        }
        return result;
    }

    AddressFamily addrFamily;
    std::array<uint8_t, 16> ipBytes;
};

inline bool operator==(const IPAddress& a, const IPAddress& b){
    for(int i = 0; i < a.ipBytes.size(); ++i){
        if(a.ipBytes[i] != b.ipBytes[i]){
            return false;
        }
    } 
    return true;
}