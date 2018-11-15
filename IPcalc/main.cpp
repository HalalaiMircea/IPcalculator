#include"IPcalc.h"
#include<iostream>

using std::cin;
using std::cout;
using std::endl;

int main()
{
	IPcalc ob("192.24.123.2/18");
	/*for (int i = 1; i <= 32; i++)
	{
		ob.setAddress("192.168.1.1/" + std::to_string(i));
		cout << ob.getLongNetmask() << endl;
	}*/
	cout << ob.getNetwork() << endl << ob.getBroadcast() << endl;
	cout << ob.getHostMin() << endl << ob.getHostMax() << endl;
	cout << ob.getUsableHosts();
	cin.get();
	return 0;
}