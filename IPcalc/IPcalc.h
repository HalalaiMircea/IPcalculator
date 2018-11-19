#pragma once
#include<iostream>
#include<array>
#include<string>
#include<sstream>


class IPcalcV4
{
public:
	IPcalcV4(const std::string& = "192.168.0.1/24");

	const std::string getLongNetmask() const;
	const std::string getNetwork() const;
	const std::string getBroadcast() const;
	const std::string getHostMin() const;
	const std::string getHostMax() const;
	const uint32_t getUsableHosts() const;

	void setAddress(const std::string &);
private:
	void parse();
	std::string addrToString(const std::array<uint8_t, 4> &) const;
	void initAddr();

	std::array<uint8_t, 4> m_address, m_longNetmask, m_wildcard, m_network, m_broadcast, m_hostMin, m_hostMax;
	uint8_t m_netmask;
	std::string m_addressRaw;
	uint32_t m_hostsNumber;
};

class IPcalcV6
{
public:
	IPcalcV6(const std::string& = "2001:0db8:85a3:0000:0000:8a2e:0370:7334/64");

	const std::string getLongNetmask() const;
	const std::string getNetwork() const;
	const std::string getBroadcast() const;
	const std::string getHostMin() const;
	const std::string getHostMax() const;
	const uint64_t getUsableHosts() const;

	void setAddress(const std::string &);
private:
	void parse();
	std::string addrToString(const std::array<uint16_t, 8> &) const;
	void initAddr();

	std::array<uint16_t, 8> m_address, m_longNetmask, m_wildcard, m_network, m_broadcast, m_hostMin, m_hostMax;
	uint8_t m_netmask;
	std::string m_addressRaw;
	uint64_t m_hostsNumber;
};
