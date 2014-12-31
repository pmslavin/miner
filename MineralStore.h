#ifndef _MINERALSTORE_H_
#define _MINERALSTORE_H_

#include <vector>
#include <string>

class Mineral;

class MineralStore
{
public:
	MineralStore(int szhint=8);
	virtual ~MineralStore();
	int mineralCount() const;
	void emptyStore();
	MineralStore& operator+=(MineralStore& rhs);
	MineralStore& operator+=(Mineral& rhs);
protected:
	std::vector<Mineral *> store;
};

#endif
