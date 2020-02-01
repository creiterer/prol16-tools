/**
 * @author		creiterer
 * @date 		2020-01-15
 * @copyright 	Copyright (c) 2020 Christopher Reiterer
 * @brief 		Class representing a Go runtime error
 */

#ifndef PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_GORUNTIMEERROR_H_INCLUDED
#define PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_GORUNTIMEERROR_H_INCLUDED

#include <cstdint>
#include <stdexcept>
#include <string>

// NOLINTNEXTLINE(readability-identifier-naming)
namespace PROL16 { namespace go { namespace rtlib {

class GoRuntimeError final : public std::runtime_error {
public:
	/// @see llvm-project/llgo/third_party/gofrontend/libgo/runtime/go-runtime-error.c
	enum class RuntimeErrorKind : int32_t {
		/* Slice index out of bounds: negative or larger than the length of
		 the slice.  */
		SLICE_INDEX_OUT_OF_BOUNDS = 0,

		/* Array index out of bounds.  */
		ARRAY_INDEX_OUT_OF_BOUNDS = 1,

		/* String index out of bounds.  */
		STRING_INDEX_OUT_OF_BOUNDS = 2,

		/* Slice slice out of bounds: negative or larger than the length of
		 the slice or high bound less than low bound.  */
		SLICE_SLICE_OUT_OF_BOUNDS = 3,

		/* Array slice out of bounds.  */
		ARRAY_SLICE_OUT_OF_BOUNDS = 4,

		/* String slice out of bounds.  */
		STRING_SLICE_OUT_OF_BOUNDS = 5,

		/* Dereference of nil pointer.  This is used when there is a
		 dereference of a pointer to a very large struct or array, to
		 ensure that a gigantic array is not used a proxy to access random
		 memory locations.  */
		NIL_DEREFERENCE = 6,

		/* Slice length or capacity out of bounds in make: negative or
		 overflow or length greater than capacity.  */
		MAKE_SLICE_OUT_OF_BOUNDS = 7,

		/* Map capacity out of bounds in make: negative or overflow.  */
		MAKE_MAP_OUT_OF_BOUNDS = 8,

		/* Channel capacity out of bounds in make: negative or overflow.  */
		MAKE_CHAN_OUT_OF_BOUNDS = 9,

		/* Integer division by zero.  */
		DIVISION_BY_ZERO = 10,
	};

	explicit GoRuntimeError(RuntimeErrorKind const errorKind);

private:
	static std::string errorKindToString(RuntimeErrorKind const errorKind) noexcept;
};

}	// namespace rtlib
}	// namespace go
}	// namespace PROL16

#endif /* PROL16_TOOLS_PROL16_SHARED_SRC_MAIN_CPP_GORUNTIMEERROR_H_INCLUDED */
