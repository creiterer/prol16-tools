/**
 * @author		creiterer
 * @date 		2019-03-16
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Utility class for handling filenames.
 */

#ifndef PROL16_AS_SRC_MAIN_CPP_FILENAME_H_INCLUDED
#define PROL16_AS_SRC_MAIN_CPP_FILENAME_H_INCLUDED

#include <string>
#include <tuple>

namespace util {

class Filename final {
public:
	using SplitFilename = std::tuple<std::string, std::string, std::string>;

	static SplitFilename split(std::string const &filename);
	static std::string getName(std::string const &filename);
	static std::string getExtension(std::string const &filename);
	static std::string getPath(std::string const &filename);

	explicit Filename(std::string const &filename);
	explicit Filename(char const * const filename);
	Filename(std::string path, std::string name, std::string extension);

	std::string asString() const;
	explicit operator std::string() const { return asString(); }

	std::string getWithoutExtension() const;

	std::string getWithCustomExtension(std::string const &extension) const;

	Filename appendToName(std::string const &appendix);
	Filename appendToName(std::string const &appendix) const;

	Filename replaceExtensionWith(std::string const &extension);

private:
	std::string name;
	std::string const path;
	std::string extension;
};

}	// namespace util

bool operator==(util::Filename const &lhs, char const * const rhs);
bool operator==(char const * const lhs, util::Filename const &rhs);

#endif /* PROL16_AS_SRC_MAIN_CPP_FILENAME_H_INCLUDED */
