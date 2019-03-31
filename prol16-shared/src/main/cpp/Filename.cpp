/**
 * @author		creiterer
 * @date 		2019-03-16
 * @copyright 	Copyright (c) 2019 Christopher Reiterer
 * @brief 		Utility class for handling filenames.
 */

#include "Filename.h"

namespace util {

Filename::Filename(std::string const &filename) : filename(filename) {

}

Filename::Filename(char const * const filename) : filename(filename) {

}

std::string Filename::getWithoutExtension() const {
	size_t const extensionDelimiterPos = filename.rfind('.');
	size_t const pathDelimiterPos = filename.rfind('/');

	if ((extensionDelimiterPos == std::string::npos) ||
		(pathDelimiterPos != std::string::npos && extensionDelimiterPos < pathDelimiterPos)) {
		// filename seems to have no extension -> return it directly
		return filename;
	}

	return filename.substr(0, extensionDelimiterPos);
}

std::string Filename::getWithCustomExtension(std::string const &extension) const {
	return getWithoutExtension().append(".").append(extension);
}

}
