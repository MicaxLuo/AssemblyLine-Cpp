
#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

using namespace std;

class Item {
	// encapsulates the information about a given item on the assembly line that can be filled within a customer order.
	std::string m_name = "";
	std::string m_description = "";
	size_t m_serialNumber = 0;
	size_t m_quantity = 0;
	static size_t m_widthField;
public:
	Item(const std::string& record);
	const std::string& getName() const;
	const unsigned int getSerialNumber();
	const unsigned int getQuantity();
	void updateQuantity();
	void display(std::ostream& os, bool full) const;
};

#endif // !SDDS_ITEM_H


