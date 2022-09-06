#include "Address.h"
#include <math.h>
#include <cstdint>
#include <bitset>

#include "ValidMasks.h"

//expressao regular para validar se o endereco esta no formato valido
const string Address::addressPattern = "^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$";

Address::Address() {}

Address::~Address() {}

void Address::setAddressCode(string code) {
    this->addressCode = code;
}

//rotina para validar se input é valido
bool Address::checkCode(string code) {

    regex str_expr(addressPattern);

    return regex_match(code,str_expr);
}

//metodo acessor de codigo do endereço
string Address::getAddressCode() {
    return this->addressCode;
}

/*  método para checar a classe de acordo com o primeiro octeto do endereço
*/
string Address::checkClass() {

    string firstItem  = * octects.begin();

    int firstItemInt = stoi(firstItem);

    if (firstItemInt <= 127) {
        return "A";
    }

    if (firstItemInt > 127 && firstItemInt <= 191 ) {
        return "B";
    }

    if (firstItemInt > 191 && firstItemInt <= 223) {
        return "C";
    }

    if (firstItemInt > 223 && firstItemInt <= 239) {
        return "D";
    }

    return "E";
}

//método atribuidor dos octetos
void Address::setOctects(string octects[4]) {

    for( int i = 0; i < 4; i++) {    
        this->octects.push_back(octects[i]);
    }
}

/*  método acessor do número cidr de um endereço
    pega o primeiro octeto do endereco e verifica o numero dele em decimal
*/
int Address::getCIDR() {

    string firstItem  = * octects.begin();

    int firstItemInt = stoi(firstItem);

    if (firstItemInt <= 127) {
        return 8;
    }

    if (firstItemInt > 127 && firstItemInt <= 191 ) {
        return 16;
    }

    return 24;    
}


/*  método para checar a mascara de um endereco
    pega o primeiro octeto do endereco e verifica o numero dele em decimal
*/
string Address::checkMask() {

    string firstItem  = * octects.begin();

    int firstItemInt = stoi(firstItem);

    if (firstItemInt <= 127) {
        return "255.0.0.0";
    }

    if (firstItemInt > 127 && firstItemInt <= 191 ) {
        return "255.255.0.0";
    }

    return "255.255.255.0";
}

//pega o numero de hosts de acordo com o cdr
double Address::getNumberOfHosts(int cdr) {
    return pow(2, (double) 32 -  cdr) - (double) 2;
}

//metodo para setar a mascara no atributo mask
void Address::setMask(string mask[4]) {
    for( int i = 0; i < 4; i++) {    
        this->mask.push_back(mask[i]);
    }
}

//metodo para pear o primeiro endereço
vector<int> Address::getFirstAddress() {

    vector<int> firstAddress;

    vector<string>::iterator maskIter = mask.begin();

    for (auto i = octects.begin(); i != octects.end(); ++i) {

        firstAddress.push_back( stoi(*i) & stoi(*maskIter));
        ++maskIter;
    }

    return firstAddress;
}

//metodo para calcular o broadcast do endereco
vector<int> Address::getBroadcast() {
    
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

//metodo para calcular o primeiro ip do endereco
vector<int> Address::getFirstIp(vector<int> firstAddress) {

    vector<int> firstIp = firstAddress;

    int lastOctect = * --firstIp.end();

    firstIp.pop_back();

    firstIp.push_back(++lastOctect);

    return firstIp;
}

//método para calcular o ultimo ip do endereco
vector<int> Address::getLastIp(vector<int> broadcast) {

    vector<int> lastIp = broadcast;

    int lastOctect = * --lastIp.end();
    
    lastIp.pop_back();

    lastIp.push_back(--lastOctect);

    return lastIp;
}

//método para validar a mascara decimal, de acordo com as mascaras no arquivo ValidMasks.h
bool Address::isValidDecimalMask(string mask) {
    return find(validMasks.begin(), validMasks.end(),mask) != validMasks.end();
}

//método para validar pegar o número cidr de acordo com a mascara fornecida
int Address::getClasslessCIDR(string mask) {
    return (find(validMasks.begin(), validMasks.end(),mask) - validMasks.begin()) + 8; 
}

//método para verificar se uma mascara é valida
bool Address::isValidCIDR(int cidr) {
    return (cidr >= 8 && cidr <= 30);
}

//método para achar a mascara pelo cidr
string Address::getMaskByCidr(int cdr) {
    return validMasks.at(cdr - 8);
}

