/**
 * @author		creiterer
 * @date 		2019-03-16
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Utility class for handling filenames.
 */

#ifndef PROL16_AS_SRC_MAIN_CPP_FILENAME_H_INCLUDED
#define PROL16_AS_SRC_MAIN_CPP_FILENAME_H_INCLUDED

#include <string>

namespace util {

class Filename final {
public:
	Filename(std::string const &filename);
	Filename(char const * const filename);
	~Filename() = default;

	inline std::string asString() const { return filename; }
	operator std::string() const { return filename; }

	std::string getWithoutExtension() const;

	std::string getWithCustomExtension(std::string const &extension) const;

private:
	std::string const filename;
};

}

#endif /* PROL16_AS_SRC_MAIN_CPP_FILENAME_H_INCLUDED */
