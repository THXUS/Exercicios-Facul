#ifndef ADDRESS_H
#define ADDRESS_H

#include <iostream>
#include <string>
#include <regex>
#include <vector>


using namespace std;

class Address {
    private:
        string addressCode;
        // string octects[4];
    public:
        vector<string> octects;
        vector<string> mask;
        static const string addressPattern;
        Address();
        ~Address();
        void setAddressCode(string code);
        bool checkCode(string code);
        string getAddressCode();
        void checkClass();
        void setOctects(string octects[4]);
        int getCIDR();
        string checkMask();
        void setMask(string mask[4]);
        double getNumberOfHosts(int cidr);
        vector<int> getFirstAddress();
        vector<int> getBroadcast();
        vector<int> getFirstIp(vector<int> firstAddress);
        vector<int> getLastIp(vector<int> broadcast);
        bool isValidDecimalMask(string mask);
        int getClasslessCIDR(string mask);
        bool isValidCIDR( int cidr);
        string getMaskByCidr( int cdr);
};


#endif

