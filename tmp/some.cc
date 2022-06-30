#include <iostream>
using namespace std;
 
int main()
{
		unsigned int r = 255;
		unsigned int hexR = r << 16;
		unsigned int g = 125;
		unsigned int hexg = g << 8;
		unsigned int b = 75;
		unsigned int hexAll = hexR + hexg + b;
    unsigned char arr[] = "\x0a\375\000l\264i";
    cout << "[0] = " << hex << (int)arr[0] << '\n';
    cout << "[1] = " << hex << (int)arr[1] << '\n';
    cout << "[2] = " << hex << (int)arr[2] << '\n';
    cout << "[3] = " << hex << (int)arr[3] << '\n';
    cout << "r = " << hex << r << '\n';
    cout << "rh = " << hex << hexR << '\n';
    cout << "g = " << hex << g << '\n';
    cout << "gh = " << hex << hexg << '\n';
    cout << "b = " << hex << b << '\n';
    cout << "hexAll = " << hex << hexAll << '\n';

}
