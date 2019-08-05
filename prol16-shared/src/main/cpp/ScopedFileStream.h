#ifndef SCOPEDFILESTREAM_H_INCLUDED
#define SCOPEDFILESTREAM_H_INCLUDED

#include <string>
#include <fstream>

#include "NonCopyable.h"

namespace util {

template <typename StreamType>
class ScopedFileStream final : private NonCopyable {
public:
	ScopedFileStream(std::string const &filename, std::ios_base::openmode const mode) : filename(filename), fileStream(filename, mode) {
		if (!fileStream) {
			throw std::ios_base::failure("Failed to open file " + filename);
		}
	}

	virtual ~ScopedFileStream() {
		fileStream.close();
	}

	inline operator StreamType&() { return fileStream; }
	inline StreamType& stream() { return fileStream; }

	inline std::string getFilename() const { return filename; }

private:
	std::string const filename;
	StreamType fileStream;
};

}

#endif
