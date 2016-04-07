#ifndef __CGLOBALS_H__
#define __CGLOBALS_H__
#include <string>
#include <map>

class cGlobals
{
public:
	static std::map<std::string, double> doubles;
	static std::map<std::string, int> ints;
	static std::map<std::string, bool> flags;
	static std::map<std::string, std::string> strings;
};


#endif
