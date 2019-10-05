/**
 * @author		creiterer
 * @date 		2019-03-16
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Utility class for handling filenames.
 */

#include "Filename.h"

#include <utility>

namespace util {

Filename::SplitFilename Filename::split(std::string const &filename) {
	size_t const extensionDelimiterPos = filename.rfind('.');
	size_t const pathDelimiterPos = filename.rfind('/');

	std::string path;
	std::string name;
	std::string extension;

	if (pathDelimiterPos != std::string::npos) {
		path = filename.substr(0, pathDelimiterPos + 1);	// +1 to keep the trailing '/'

		if ((extensionDelimiterPos == std::string::npos) || (extensionDelimiterPos < pathDelimiterPos)) {
			// filename seems to have no extension
			name = filename.substr(pathDelimiterPos + 1);
		} else {
			name = filename.substr(pathDelimiterPos + 1, extensionDelimiterPos - pathDelimiterPos - 1);
			extension = filename.substr(extensionDelimiterPos + 1);
		}
	} else {
		name = filename.substr(0, extensionDelimiterPos);

		if (extensionDelimiterPos != std::string::npos) {
			extension = filename.substr(extensionDelimiterPos + 1);
		}
	}

	return std::make_tuple(path, name, extension);
}

std::string Filename::getName(std::string const &filename) {
	return std::get<1>(split(filename));
}

std::string Filename::getExtension(std::string const &filename) {
	return std::get<2>(split(filename));
}

std::string Filename::getPath(std::string const &filename) {
	return std::get<0>(split(filename));
}

Filename::Filename(std::string const &filename)
: name(getName(filename)), path(getPath(filename)), extension(getExtension(filename)) {

}

Filename::Filename(char const * const filename) : Filename(std::string(filename)) {

}

Filename::Filename(std::string path, std::string name, std::string extension)
: name(std::move(name)), path(std::move(path)), extension(std::move(extension)) {

}

std::string Filename::asString() const {
	if (extension.empty()) {
		return path + name;
	}

	return path + name + '.' + extension;
}

std::string Filename::getWithoutExtension() const {
	return path + name;
}

std::string Filename::getWithCustomExtension(std::string const &extension) const {
	return getWithoutExtension() + '.' + extension;
}

Filename Filename::appendToName(std::string const &appendix) {
	name += appendix;

	return *this;
}

Filename Filename::appendToName(std::string const &appendix) const {
	return Filename(path, name + appendix, extension);
}

}	// namespace util

bool operator==(util::Filename const &lhs, char const * const rhs) {
	return lhs.asString() == rhs;
}

bool operator==(char const * const lhs, util::Filename const &rhs) {
	return lhs == rhs.asString();
}
