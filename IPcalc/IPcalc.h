#pragma once
#include<iostream>
#include<array>
#include<string>

class IPcalc
{
public:
	IPcalc(std::string);
	~IPcalc();
private:
	void parse();
	std::array<uint8_t, 4> m_address, m_longNetmask, m_network, m_broadcast, m_hostMin, m_hostMax;
	uint8_t m_netmask;
	std::string m_addressRaw;
	uint32_t m_hostsNumber;
};

