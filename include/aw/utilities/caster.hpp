#ifndef AWCASTER_HPP
#define AWCASTER_HPP

#include <sstream>
#include <vector>

namespace aw
{
	template<class T>
	std::vector<T> inline castStr(const std::string &string)
	{
		std::stringstream sstr(string);
		std::vector<T> container;
		while (!sstr.eof())
		{
			T temp;
			sstr >> temp;
			container.push_back(temp);
		}

		return container;
	}
	/////////////////////////////////////////////////
	template<class T, class V>
	T inline cast(const V &val)
	{
		return static_cast<T>(val);
	}
}

#endif