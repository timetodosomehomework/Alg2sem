#pragma once
class Iterator
{
public:
	virtual bool has_current() = 0;
	virtual void next() = 0;
	virtual int freq() = 0;
	virtual char symbol() = 0;
	virtual std::string code() = 0;
};
