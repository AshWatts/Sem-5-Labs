#include <iostream>
#include <string>

using namespace std;

string xorfun(string encoded, string crc) {
    int crclen = crc.length();
    int encodedlen = encoded.length();
    
    for (int i = 0; i <= (encodedlen - crclen); ) {
        if (encoded[i] == '1') {
            for (int j = 0; j < crclen; j++) {
                encoded[i + j] = (encoded[i + j] == crc[j]) ? '0' : '1';
            }
        }
        for (i++; i < encodedlen && encoded[i] != '1'; i++);
    }
    
    return encoded;
}

int main() {
    string data, crc, encoded = "";
    cout << endl << "-----------Sender Side --------------" << endl;
    cout << "Enter Data bits: " << endl;
    cin >> data;

    cout << "Enter Generator: " << endl;
    cin >> crc;

    encoded += data;
    int datalen = data.length();
    int crclen = crc.length();
    
    for (int i = 1; i <= (crclen - 1); i++)
        encoded += '0';
    
    encoded = xorfun(encoded, crc);
    
    string checksum = encoded.substr(encoded.length() - crclen + 1);
    cout << "Checksum generated is: " << checksum << endl << endl;
    cout << "Message to be Transmitted over network: ";
    cout << data + checksum << endl;
    
    cout << endl << "---------------Receiver Side-----------------" << endl;
    cout << "Enter the message received: " << endl;
    string msg;
    cin >> msg;
    
    msg = xorfun(msg, crc);
    
    for (char i : msg.substr(msg.length() - crclen + 1)) {
        if (i != '0') {
            cout << "Error in communication " << endl;
            return 0;
        }
    }
    
    cout << "No Error !" << endl;
    return 0;
}
