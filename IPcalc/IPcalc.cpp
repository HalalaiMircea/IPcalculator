#include "IPcalc.h"


IPcalcV4::IPcalcV4(const std::string& IPaddress) : m_addressRaw(IPaddress)
{
	initAddr();
	parse();
}

const std::string IPcalcV4::getLongNetmask() const
{
	return addrToString(m_longNetmask);
}

const std::string IPcalcV4::getNetwork() const
{
	return addrToString(m_network);
}

const std::string IPcalcV4::getBroadcast() const
{
	return addrToString(m_broadcast);
}

const std::string IPcalcV4::getHostMin() const
{
	if (m_netmask == 32 || m_netmask == 31)
		return "N/A";
	return addrToString(m_hostMin);
}

const std::string IPcalcV4::getHostMax() const
{
	if (m_netmask == 32 || m_netmask == 31)
		return "N/A";
	return addrToString(m_hostMax);
}

const uint32_t IPcalcV4::getUsableHosts() const
{
	return m_hostsNumber;
}

void IPcalcV4::setAddress(const std::string &addr)
{
	m_addressRaw = addr;
	initAddr();
	parse();
}

void IPcalcV4::parse()
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
	if (m_netmask == 32 || m_netmask == 31)
		m_hostsNumber = 0;
	else
	{
		m_hostMin = m_network;
		m_hostMax = m_broadcast;
		m_hostMin.at(m_network.size() - 1) += 1;
		m_hostMax.at(m_network.size() - 1) -= 1;
		//Number of usable hosts
		m_hostsNumber = (1 << (32 - m_netmask)) - 2;
	}
}

std::string IPcalcV4::addrToString(const std::array<uint8_t, 4> &addr) const
{
	std::string strAddr;
	size_t i;
	for (i = 0; i < addr.size() - 1; i++)
		strAddr += std::to_string(addr.at(i)) + '.';
	strAddr += std::to_string(addr.at(i));
	return strAddr;
}

void IPcalcV4::initAddr()
{
	m_longNetmask.fill(255);
	m_wildcard.fill(0);
	m_network.fill(0);
	m_broadcast.fill(0);
	m_hostMin.fill(0);
	m_hostMax.fill(0);
	m_hostsNumber = 0;
}

IPcalcV6::IPcalcV6(const std::string & IPaddress) : m_addressRaw(IPaddress)
{
	initAddr();
	parse();
}

const std::string IPcalcV6::getLongNetmask() const
{
	return addrToString(m_longNetmask);
}

const std::string IPcalcV6::getNetwork() const
{
	return addrToString(m_network);
}

const std::string IPcalcV6::getBroadcast() const
{
	return addrToString(m_broadcast);
}

const std::string IPcalcV6::getHostMin() const
{
	if (m_netmask == 128 || m_netmask == 127)
		return "N/A";
	return addrToString(m_hostMin);
}

const std::string IPcalcV6::getHostMax() const
{
	if (m_netmask == 128 || m_netmask == 127)
		return "N/A";
	return addrToString(m_hostMax);
}

const Dodecahedron::Bigint IPcalcV6::getUsableHosts() const
{
	return m_hostsNumber;
}

void IPcalcV6::setAddress(const std::string & addr)
{
	m_addressRaw = addr;
	initAddr();
	parse();
}

void IPcalcV6::parse()
{
	//Decomposes the string into array of ipv4 address bytes m_address and netmask prefix
	size_t i = 0;
	char *token;
	std::string c_address = m_addressRaw;
	token = strtok(&c_address[0], ":/");
	while (token != NULL)
	{
		if (i == m_address.max_size())
			m_netmask = (uint8_t)strtol(token, NULL, 10);
		else
			m_address.at(i) = (uint16_t)strtol(token, NULL, 16);
		i++;
		token = strtok(NULL, ":/");
	}
	//Builds the long netmask from the prefix m_netmask
	uint8_t bitShifts = 128 - m_netmask, hextetIndex = 7;
	while (bitShifts - 16 >= 0)
	{
		m_longNetmask.at(hextetIndex) <<= 16;
		bitShifts -= 16;
		hextetIndex--;
	}
	m_longNetmask.at(hextetIndex) <<= bitShifts;
	//Network address
	for (size_t i = 0; i < m_address.size(); i++)
		m_network.at(i) = m_address.at(i) & m_longNetmask.at(i);
	//Wildcard and broadcast
	for (size_t i = 0; i < m_address.size(); i++)
	{
		m_wildcard.at(i) = 0xffff - m_longNetmask.at(i);
		m_broadcast.at(i) = m_network.at(i) + m_wildcard.at(i);
	}
	//Lowest and highest IP address in network range
	if (m_netmask == 128 || m_netmask == 127)
		m_hostsNumber = 0;
	else
	{
		m_hostMin = m_network;
		m_hostMax = m_broadcast;
		m_hostMin.at(m_network.size() - 1) += 1;
		m_hostMax.at(m_network.size() - 1) -= 1;
		//Number of usable hosts
		m_hostsNumber = 2;
		m_hostsNumber = m_hostsNumber.pow(128 - m_netmask) - 2;
	}
}

std::string IPcalcV6::addrToString(const std::array<uint16_t, 8>& addr) const
{
	std::string strAddr;
	std::stringstream ss;
	size_t i;
	for (i = 0; i < addr.size() - 1; i++)
		ss << std::hex << addr.at(i) << ':';
	ss << std::hex << addr.at(i);
	ss >> strAddr;
	return strAddr;
}

void IPcalcV6::initAddr()
{
	m_longNetmask.fill(0xffff);
	m_wildcard.fill(0);
	m_network.fill(0);
	m_broadcast.fill(0);
	m_hostMin.fill(0);
	m_hostMax.fill(0);
	m_hostsNumber = 0;
}
