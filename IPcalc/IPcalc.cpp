#include "IPcalc.h"


IPcalc::IPcalc(std::string IPaddress)
{
	m_addressRaw = IPaddress;
	initAddr();
	parse();
}

IPcalc::~IPcalc()
{
}

std::string IPcalc::getLongNetmask()
{
	return addrToString(m_longNetmask);
}

std::string IPcalc::getNetwork()
{
	return addrToString(m_network);
}

void IPcalc::setAddress(const std::string &addr)
{
	m_addressRaw = addr;
	initAddr();
	parse();
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
		m_longNetmask.at(byteIndex) += 1 << power;
		bitCount--;
		power--;
	}
	//
	//Generates the network address m_network
	//
	for (int i = 0; i < m_address.size(); i++)
		m_network.at(i) = m_address.at(i) & m_longNetmask.at(i);
}

std::string IPcalc::addrToString(const std::array<uint8_t, 4> &addr)
{
	std::string strAddr;
	int i;
	for (i = 0; i < addr.size() - 1; i++)
		strAddr += std::to_string(addr.at(i)) + '.';
	strAddr += std::to_string(addr.at(i));
	return strAddr;
}

void IPcalc::initAddr()
{
	m_longNetmask.fill(0);
	m_network.fill(0);
	m_broadcast.fill(0);
	m_hostMin.fill(0);
	m_hostMax.fill(0);
}
