#include "hash.hpp"

namespace aw
{
	unsigned int hash(const std::string &s, unsigned int seed)
	{
		unsigned hash = seed;
		for (std::size_t i = 0; i < s.size(); i++)
		{
			hash = hash * 101 + s[i];
		}
		return hash;
	}
}