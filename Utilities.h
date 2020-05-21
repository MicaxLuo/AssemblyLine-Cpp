
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


