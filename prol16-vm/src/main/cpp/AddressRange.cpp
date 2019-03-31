#include "AddressRange.h"

#include <cassert>

AddressRange::AddressRange(Prol16::TAddress begin, Prol16::TAddress end) : mBegin(begin), mEnd(end) {
	assert(begin <= end);
}

bool AddressRange::operator<(AddressRange const& adressRange) const {
	return mEnd < adressRange.mBegin;
}

Prol16::TAddress AddressRange::Begin() const {
	return mBegin;
}

Prol16::TAddress AddressRange::End() const {
	return mEnd;
}