#pragma once
#include<iostream>
#include<array>
#include<string>

class IPcalc
{
public:
	IPcalc(std::string = "192.168.0.1/24");

	std::string getLongNetmask();
	std::string getNetwork();
	std::string getBroadcast();
	std::string getHostMin();
	std::string getHostMax();
	uint32_t getUsableHosts();

	void setAddress(const std::string &);
private:
	void parse();
	std::string addrToString(const std::array<uint8_t, 4> &);
	void initAddr();

	std::array<uint8_t, 4> m_address, m_longNetmask, m_wildcard, m_network, m_broadcast, m_hostMin, m_hostMax;
	uint8_t m_netmask;
	std::string m_addressRaw;
	uint32_t m_hostsNumber;
};

