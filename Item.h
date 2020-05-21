// Course: 				OOP345 NDE
// Final Project:      	Milestone 3
// Name: 				Xiaomin (Mica) Luo
// Seneca Student ID:   133728170
// Seneca email: 		xluo42@myseneca.ca
// Date of completion:  Dec.1, 2019
//
// I confirm that the content of this file is created by me,
//   with the exception of the parts provided to me by my professor.

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


