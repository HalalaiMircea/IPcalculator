#include "IPcalc.h"
#include<cmath>


IPcalc::IPcalc(std::string IPaddress)
{
	m_addressRaw = IPaddress;
	m_longNetmask.fill(0);
	m_network.fill(0);
	m_broadcast.fill(0);
	m_hostMin.fill(0);
	m_hostMax.fill(0);
	parse();
}

IPcalc::~IPcalc()
{
}

void IPcalc::parse()
{
	//
	//Decomposes the string into array of ipv4 address bytes m_address and netmask prefix
	//
	int i = 0;
	char *token;
	std::string c_address = m_addressRaw;
	token = strtok(&c_address[0], "./");
	while (token != NULL)
	{
		if (i == m_address.max_size())
			m_netmask = (uint8_t)atoi(token);
		else
			m_address.at(i) = (uint8_t)atoi(token);
		i++;
		token = strtok(NULL, "./");
	}
	int byteIndex = 0, bitCount;
	//
	//Builds the long netmask from the prefix m_netmask
	//
	uint8_t cNet = m_netmask;
	while (cNet - 8 >= 0)
	{
		m_longNetmask.at(byteIndex) = 255;
		byteIndex++;
		cNet -= 8;
	}
	bitCount = m_netmask - byteIndex * 8;
	int power = 7;
	while (bitCount > 0)
	{
		m_longNetmask.at(byteIndex) += pow(2, power);
		bitCount--;
		power--;
	}
	/*std::cout << bitCount << std::endl;
	for (int i = 0; i < 4; i++)
		std::cout << (int)m_longNetmask.at(i) << std::endl;*/
}
