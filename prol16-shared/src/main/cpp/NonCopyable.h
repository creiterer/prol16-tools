#ifndef NONCOPYABLE_H_INCLUDED
#define NONCOPYABLE_H_INCLUDED

class NonCopyable {
public:
	NonCopyable() = default;
	virtual ~NonCopyable() = default;

private:
	NonCopyable(NonCopyable const &other) = delete;
	NonCopyable& operator= (NonCopyable const &other) = delete;
};

#endif