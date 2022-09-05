#include "Address.h"
#include <math.h>
#include <cstdint>
#include <bitset>


const string Address::addressPattern = "^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$";

Address::Address() {}

Address::~Address() {}

void Address::setAddressCode(string code) {
    this->addressCode = code;
}

bool Address::checkCode(string code) {

    regex str_expr(addressPattern);

    return regex_match(code,str_expr);
}

string Address::getAddressCode() {
    return this->addressCode;
}

void Address::checkClass() {

    string firstItem  = * octects.begin();

    int firstItemInt = stoi(firstItem);

    if (firstItemInt <= 127) {
        cout << "class A" << "\n";
    }

    if (firstItemInt > 127 && firstItemInt <= 191 ) {
        cout <<"class B" << "\n";
    }

    if (firstItemInt > 191) {
        cout << "class C" << "\n";
    }    
}

void Address::setOctects(string octects[4]) {

    for( int i = 0; i < 4; i++) {    
        this->octects.push_back(octects[i]);
    }
}

int Address::getCIDR() {

    string firstItem  = * octects.begin();

    int firstItemInt = stoi(firstItem);

    if (firstItemInt <= 127) {
        return 8;
    }

    if (firstItemInt > 127 && firstItemInt <= 191 ) {
        return 16;
    }

    if (firstItemInt > 191) {
        return 24;
    }

    return 0;    
}

string Address::checkMask() {

    string firstItem  = * octects.begin();

    int firstItemInt = stoi(firstItem);

    if (firstItemInt <= 127) {
        return "255.0.0.0";
    }

    if (firstItemInt > 127 && firstItemInt <= 191 ) {
        return "255.255.0.0";
    }

    if (firstItemInt > 191 ) {
        return "255.255.255.0";
    }

    return "0.0.0.0";    
}

double Address::getNumberOfHosts(int cdr) {
    return pow(2, (double) 32 -  cdr) - (double) 2;
}

void Address::setMask(string mask[4]) {
    for( int i = 0; i < 4; i++) {    
        this->mask.push_back(mask[i]);
    }
}

vector<int> Address::getFirstAddress() {

    vector<int> firstAddress;

    vector<string>::iterator maskIter = mask.begin();

    for (auto i = octects.begin(); i != octects.end(); ++i) {

        firstAddress.push_back( stoi(*i) & stoi(*maskIter));
        ++maskIter;
    }

    return firstAddress;
}

vector<int> Address::getLastAddress() {
    
    vector<int> lastAddress;

    vector<string>::iterator maskIter = mask.begin();

    for (auto i = octects.begin(); i != octects.end(); ++i) {

        bitset<8> maskIterBinary = bitset<8>(stoi(*maskIter));

        bitset<8> binaryOctect = (bitset<8>(stoi(*i))|= maskIterBinary.flip());

        lastAddress.push_back((stoi(binaryOctect.to_string(), 0, 2)));

        ++maskIter;
    }

    return lastAddress;
}