#ifndef ADRESS_RANGE_H
#define ADRESS_RANGE_H

#include "Prol16.h"

class AddressRange final {
public:
	AddressRange(Prol16::TAddress begin, Prol16::TAddress end);
	bool operator<(AddressRange const& adressRange) const;
	Prol16::TAddress Begin() const;
	Prol16::TAddress End() const;

private:
	Prol16::TAddress const mBegin;
	Prol16::TAddress const mEnd;
};

#endif
