// Course: 				OOP345 NDE
// Final Project:      	Milestone 3
// Name: 				Xiaomin (Mica) Luo
// Seneca Student ID:   133728170
// Seneca email: 		xluo42@myseneca.ca
// Date of completion:  Dec.1, 2019
//
// I confirm that the content of this file is created by me,
//   with the exception of the parts provided to me by my professor.

#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

using namespace std;

class Utilities {
	// an object used to support the parsing of input files to setup and configure the assembly line simulation.
	size_t m_widthField = 1;
	static char m_delimiter;
public:
	void setFieldWidth(size_t width);
	size_t getFieldWidth() const;
	const std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
	const char getDelimiter() const;
	static void setDelimiter(const char delim);
};

#endif


