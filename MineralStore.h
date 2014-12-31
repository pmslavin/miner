#ifndef _MINERALSTORE_H_
#define _MINERALSTORE_H_

#include <vector>
#include <iostream>
#include <string>

class Mineral;

class MineralStore
{
public:
	MineralStore(int szhint=8);
	virtual ~MineralStore();
	int mineralCount() const;
	int size() const;
	void emptyStore();
	void emptyNulls();
	friend std::ostream& operator<<(std::ostream& ostr, const MineralStore& m);
	MineralStore& operator+=(MineralStore& rhs);
	MineralStore& operator+=(Mineral& rhs);
protected:
	std::vector<Mineral *> store;
};

#endif
