#include "IPcalc.h"



IPcalc::IPcalc(std::string IPaddress)
{
	m_address = IPaddress;
	parse();
}

IPcalc::~IPcalc()
{
}

void IPcalc::parse()
{
	int i = 0;
	char seps[] = "./";
	char *token;
	std::string c_address = m_address;
	token = strtok(&c_address[0], seps);
	while (token != NULL)
	{
		if (i == m_octets.max_size())
			m_netmask = (uint16_t)atoi(token);
		else
			m_octets.at(i) = (uint16_t)atoi(token);
		i++;
		token = strtok(NULL, seps);
	}
}
