#pragma once
#define _CRT_SECURE_NO_WARNINGS
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
	std::array<uint16_t, 4> m_octets;
	uint16_t m_netmask;
	std::string m_address, m_network, m_broadcast, m_hostMin, m_hostMax;
	uint32_t m_hostsNumber;
};

