#include"IPcalc.h"
#include<iostream>

using std::cin;
using std::cout;
using std::endl;

int main()
{
	IPcalcV6 ob;
	//for (int i = 1; i <= 128; i++)
	//{
	//	ob.setAddress("2001:0db8:85a3:0000:0000:8a2e:0370:7334/" + std::to_string(i));
	//	cout << ob.getLongNetmask() /*<< " " << ob.getUsableHosts()*/ << endl;
	//}
	cout << "Long netmask:  " << ob.getLongNetmask() << endl;
	cout << "Network:       " << ob.getNetwork() << endl;
	cout << "Broadcast:     " << ob.getBroadcast() << endl;
	cout << "Address Range: " << ob.getHostMin() << " - " << ob.getHostMax() << endl;
	cout << "Maximum hosts: " << ob.getUsableHosts();
	cin.get();
	return 0;
}