#ifndef SCOPEDFILESTREAM_H_INCLUDED
#define SCOPEDFILESTREAM_H_INCLUDED

#include "NonCopyable.h"

#include <fstream>
#include <string>

namespace util {

template <typename StreamType>
class ScopedFileStream final : private NonCopyable {	// NOLINT(cppcoreguidelines-special-member-functions)
public:
	ScopedFileStream(std::string const &filename, std::ios_base::openmode const mode) : filename(filename), fileStream(filename, mode) {
		if (!fileStream) {
			throw std::ios_base::failure("Failed to open file " + filename);
		}
	}

	~ScopedFileStream() override {
		fileStream.close();
	}

	// NOLINTNEXTLINE(google-explicit-constructor)
	inline operator StreamType&() { return fileStream; }
	inline StreamType& stream() { return fileStream; }

	inline std::string getFilename() const { return filename; }

private:
	std::string const filename;
	StreamType fileStream;
};

}	// namespace util

#endif
