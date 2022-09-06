
#include "Address.h"
#include "Address.cpp"
#include <vector>
#include "validMasks.h"
string octects[4];
string maskOctects[4];
  
int len(string str) {  
    int length = 0;  
    for (int i = 0; str[i] != '\0'; i++)  
    {  
        length++;  
          
    }  
    return length;     
}  
  
void split (string str, char seperator, string *arr) {  
    int currIndex = 0, i = 0;  
    int startIndex = 0, endIndex = 0;  
    while (i <= len(str))  {  
        if (str[i] == seperator || i == len(str)) {  
            endIndex = i;  
            string subStr = "";  
            subStr.append(str, startIndex, endIndex - startIndex);  
            arr[currIndex] = subStr;  
            currIndex += 1;  
            startIndex = endIndex + 1;  
        }  
        i++;  
    }     
}

int printScreen( ) {

    int option;

    cout << "THE MAGIC IP CALCULATOR OF MATHEUS GUILHERME SOUZA SANTANA" << "\n";
    cout << "Class: Redes De Computadores II                           " << "\n";
    cout << "\n";
    cout << "Options:                                                  " << "\n";
    cout << "1 - Calculate Class IP                                    " << "\n";
    cout << "2 - Calculate Classless IP with CIDR                      " << "\n";
    cout << "3 - Calculate Classless IP with Decimal Notation          " << "\n";
    cout << "4 - Exit                                                  " << "\n";
    cout << "Enter your option: ";
    cin >> option;

    return option;
}

void calculateClassIP() {

    Address address;

    string input;
    
    cout<< "Type something bruh... ";
    
    cin >> input;

    bool isValid = address.checkCode(input);

    if(isValid) {
        cout << "is Valid\n";
        
        address.setAddressCode(input);

        split(address.getAddressCode(), '.', octects);

        address.setOctects(octects);

        address.checkClass();

        int cidr = address.getCIDR();

        cout << "/" << cidr << endl;

        string mask = address.checkMask();

        cout << "Mask: " << mask << "\n";

        split(mask,'.',maskOctects );

        address.setMask(maskOctects);

        int numberOfHosts  = address.getNumberOfHosts(cidr);

        cout << "Number of Hosts: " << numberOfHosts << "\n";

        vector<int> firstAddress = address.getFirstAddress();

        cout << "First Address: ";

        for ( auto i = firstAddress.begin(); i != firstAddress.end(); ++i) {
            cout << *i << ".";
        }

        vector<int> broadcast = address.getBroadcast();

        cout << "\n";

        cout << "Broadcast: ";

        for ( auto i = broadcast.begin(); i != broadcast.end(); ++i) {
            cout << *i << ".";
        }

        cout <<"\n";

        cout << "First IP: ";

        vector<int> firstIp = address.getFirstIp(firstAddress);

        for( auto i = firstIp.begin(); i != firstIp.end(); ++i ) {
            cout << *i <<".";
        }
        cout << "\n";

        cout << "Last IP: ";

        vector<int> lastIp = address.getLastIp(broadcast);

        for( auto i = lastIp.begin(); i != lastIp.end(); ++i) {
            cout << *i << ".";
        }

    } else {
        cout << "is Invalid\n";
    }
}

void calculateClasslessIP() {

    string ipCode;
    
    Address address;

    cout << "Enter yout ip bruh... " << "\n";
    cin >> ipCode;

    bool isValid = address.checkCode(ipCode);

    if(isValid) {

    }else {
        cout << "Oopsie, sorry its invalid :(" << "\n";
    }







}
  

int main() {

    int option = printScreen();

    switch (option) {

        case 1:
        calculateClassIP();
        break;
        case 2:
        break;
        case 3:
        break;
        default:
        cout << "BUUUUHH" << "\n";
    }

    return 0;
}