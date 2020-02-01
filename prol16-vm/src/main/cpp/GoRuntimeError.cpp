/**
 * @author		creiterer
 * @date 		2020-01-15
 * @copyright 	Copyright (c) 2020 Christopher Reiterer
 * @brief 		Class representing a Go runtime error
 */

#include "GoRuntimeError.h"

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace go { namespace rtlib {

GoRuntimeError::GoRuntimeError(RuntimeErrorKind const errorKind) : runtime_error(errorKindToString(errorKind)) {}

std::string GoRuntimeError::errorKindToString(RuntimeErrorKind const errorKind) noexcept {
	switch (errorKind) {
	case RuntimeErrorKind::SLICE_INDEX_OUT_OF_BOUNDS:
	case RuntimeErrorKind::ARRAY_INDEX_OUT_OF_BOUNDS:
	case RuntimeErrorKind::STRING_INDEX_OUT_OF_BOUNDS:
		return "index out of bounds";

	case RuntimeErrorKind::SLICE_SLICE_OUT_OF_BOUNDS:
	case RuntimeErrorKind::ARRAY_SLICE_OUT_OF_BOUNDS:
	case RuntimeErrorKind::STRING_SLICE_OUT_OF_BOUNDS:
		return "slice out of bounds";

	case RuntimeErrorKind::NIL_DEREFERENCE:
		return "nil pointer dereference";

	case RuntimeErrorKind::MAKE_SLICE_OUT_OF_BOUNDS:
		return "make slice len or cap out of bounds";

	case RuntimeErrorKind::MAKE_MAP_OUT_OF_BOUNDS:
		return "make map len out of bounds";

	case RuntimeErrorKind::MAKE_CHAN_OUT_OF_BOUNDS:
		return "make chan len out of bounds";

	case RuntimeErrorKind::DIVISION_BY_ZERO:
		return "integer division by zero";

	default:
		return "unknown runtime error";
	}
}

}	// namespace rtlib
}	// namespace go
}	// namespace PROL16
