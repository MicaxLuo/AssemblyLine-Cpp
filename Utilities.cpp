// Course: 				OOP345 NDE
// Final Project:      	Milestone 3
// Name: 				Xiaomin (Mica) Luo
// Seneca Student ID:   133728170
// Seneca email: 		xluo42@myseneca.ca
// Date of completion:  Dec.1, 2019
//
// I confirm that the content of this file is created by me,
//   with the exception of the parts provided to me by my professor.

#include "Utilities.h"

char Utilities::m_delimiter = ',';

void Utilities::setFieldWidth(size_t width) {
	m_widthField = width;
}

size_t Utilities::getFieldWidth() const {
	return m_widthField;
}

const std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
	std::string token = str.substr(next_pos, str.find(m_delimiter, next_pos) - next_pos);

	if (token != "") {
		if (str.find(m_delimiter, next_pos) == std::string::npos)
			more = false;
		else
			more = true;
		next_pos += token.length() + 1;
		if (token.length() > m_widthField) {
			setFieldWidth(token.length());
		}
	}
	else {
		more = false;
		throw "No token between two delimiters\n";
	}

	return token;
}

void Utilities::setDelimiter(const char delim) { // no static in the front
	m_delimiter = delim; // type difference --will have error if I don't have static var
}

const char Utilities::getDelimiter() const {
	return m_delimiter;
}
