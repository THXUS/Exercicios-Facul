
#include "Address.h"
#include "Address.cpp"
#include <vector>

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
  

int main() {
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

        vector<int> lastAddress = address.getLastAddress();

        cout << "\n";

        cout << "Last Address: ";

        for ( auto i = lastAddress.begin(); i != lastAddress.end(); ++i) {
            cout << *i << ".";
        }

        cout <<"\n";


    } else {
        cout << "is Invalid\n";
    }
    return 0;
}