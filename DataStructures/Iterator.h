#pragma once

#ifndef Iterator_H
#define Iterator_H

template<class T>
class Iterator
{
public:
	virtual void MoveNext() noexcept = 0;
	virtual void Reset() noexcept = 0;
	virtual bool IsDone() const noexcept = 0;
	virtual T & GetCurrent() const noexcept(false) = 0;
};

#endif // !Iterator_H
