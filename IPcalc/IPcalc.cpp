#include "IPcalc.h"


IPcalc::IPcalc(std::string IPaddress)
{
	m_addressRaw = IPaddress;
	initAddr();
	parse();
}

std::string IPcalc::getLongNetmask() const
{
	return addrToString(m_longNetmask);
}

std::string IPcalc::getNetwork() const
{
	return addrToString(m_network);
}

std::string IPcalc::getBroadcast() const
{
	return addrToString(m_broadcast);
}

std::string IPcalc::getHostMin() const
{
	return addrToString(m_hostMin);
}

std::string IPcalc::getHostMax() const
{
	return addrToString(m_hostMax);
}

uint32_t IPcalc::getUsableHosts() const
{
	return m_hostsNumber;
}

void IPcalc::setAddress(const std::string &addr)
{
	m_addressRaw = addr;
	initAddr();
	parse();
}

void IPcalc::parse()
{
	//Decomposes the string into array of ipv4 address bytes m_address and netmask prefix
	size_t i = 0;
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
	//Builds the long netmask from the prefix m_netmask
	uint8_t bitShifts = 32 - m_netmask, byteIndex = 3;
	while (bitShifts - 8 >= 0)
	{
		m_longNetmask.at(byteIndex) <<= 8;
		bitShifts -= 8;
		byteIndex--;
	}
	m_longNetmask.at(byteIndex) <<= bitShifts;
	//Network address
	for (size_t i = 0; i < m_address.size(); i++)
		m_network.at(i) = m_address.at(i) & m_longNetmask.at(i);
	//Wildcard and broadcast
	for (size_t i = 0; i < m_address.size(); i++)
	{
		m_wildcard.at(i) = 255 - m_longNetmask.at(i);
		m_broadcast.at(i) = m_network.at(i) + m_wildcard.at(i);
	}
	//Lowest and highest IP address in network range
	m_hostMin = m_network;
	m_hostMin.at(m_network.size() - 1) += 1;
	m_hostMax = m_broadcast;
	m_hostMax.at(m_network.size() - 1) -= 1;
	//Number of usable hosts
	m_hostsNumber = (1 << (32 - m_netmask)) - 2;
}

std::string IPcalc::addrToString(const std::array<uint8_t, 4> &addr) const
{
	std::string strAddr;
	size_t i;
	for (i = 0; i < addr.size() - 1; i++)
		strAddr += std::to_string(addr.at(i)) + '.';
	strAddr += std::to_string(addr.at(i));
	return strAddr;
}

void IPcalc::initAddr()
{
	m_longNetmask.fill(255);
	m_wildcard.fill(0);
	m_network.fill(0);
	m_broadcast.fill(0);
	m_hostMin.fill(0);
	m_hostMax.fill(0);
}
