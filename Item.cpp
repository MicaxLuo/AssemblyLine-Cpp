// Course: 				OOP345 NDE
// Final Project:      	Milestone 3
// Name: 				Xiaomin (Mica) Luo
// Seneca Student ID:   133728170
// Seneca email: 		xluo42@myseneca.ca
// Date of completion:  Dec.1, 2019
//
// I confirm that the content of this file is created by me,
//   with the exception of the parts provided to me by my professor.

#include <iomanip>
#include "Item.h"
#include "Utilities.h"

size_t Item::m_widthField = 0;

Item::Item(const std::string& record) {
	Utilities util;
	size_t pos = 0;
	bool more = true;

	if (record.length() > 0) {
		m_name = util.extractToken(record, pos, more);

		if (util.getFieldWidth() > m_widthField) {
			m_widthField = util.getFieldWidth();
		}

		if (more) {
			m_serialNumber = std::stoi(util.extractToken(record, pos, more));

			if (more) {
				m_quantity = std::stoi(util.extractToken(record, pos, more));

				if (more) {
					m_description = util.extractToken(record, pos, more);
				}
			}
		}
	}
}

const std::string& Item::getName() const {
	return m_name;
}

const unsigned int Item::getSerialNumber() {
	return m_serialNumber++;
}

const unsigned int Item::getQuantity() {
	return m_quantity;
}

void Item::updateQuantity() {
	if (m_quantity > 0) {
		m_quantity--;
	}
}

void Item::display(std::ostream& os, bool full) const {
	std::string s = "0";
	std::string serialNum = to_string(m_serialNumber);

	if (serialNum.length() < 6) {
		s.append(serialNum);
	}
	else {
		s = serialNum;
	}

	os << std::setw(m_widthField) << std::left << m_name;
	os << " [" << std::setw(6) << s << "] ";

	if (full) {

		os << "Quantity: " << std::left << std::setw(m_widthField) << m_quantity
			<< "Description: " << m_description;
	}

	os << std::endl;
}