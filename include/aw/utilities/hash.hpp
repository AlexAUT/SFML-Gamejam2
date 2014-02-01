#ifndef AWHASH_HPP
#define AWHASH_HPP

#include <string>

namespace aw
{
	//A really simple and fast hash function
	unsigned int hash(const std::string &s, unsigned int seed = 0);
}

#endif