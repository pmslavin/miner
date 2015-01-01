#include "MineralStore.h"
#include "Mineral.h"

#include <typeinfo>


MineralStore::MineralStore(int szhint)
{
	store.reserve(szhint);
}


MineralStore::~MineralStore()
{
	if(store.size() != 0)
		emptyStore();
}


int MineralStore::mineralCount() const
{
	return store.size();
}


void MineralStore::emptyStore()
{
	for(auto& m: store)
		delete m;
	
	store.clear();
}


void MineralStore::emptyNulls()
{
	Mineral * m;
	for(auto it = store.begin(); it != store.end(); ){
		m = *it;
		if(!m->getYield()){
			delete m;
			store.erase(it);
		}else{
			++it;
		}
	}
}


MineralStore& MineralStore::operator+=(Mineral& rhs)
{
	if(!rhs.getYield())
		return *this;

	bool present = false;
	for(auto& m: store){
		if(typeid(*m) == typeid(rhs)){
			*m += rhs;
			present = true;
		}
	}

	if(!present)
		store.push_back(&rhs);

	return *this;
}


MineralStore& MineralStore::operator+=(MineralStore& rhs)
{
	Mineral *inStore = nullptr, *r;

	for(auto it = rhs.store.begin(); it != rhs.store.end(); ){
		r = *it;
		for(auto& m: store){
			if(typeid(*m) == typeid(*r)){
			/* Increment yield of existing type */
				inStore = m;
				*m += *r;
			}
		}

		if(!inStore){
		/* Transfer ownership to this */
			store.push_back(&(*r));
			rhs.store.erase(it);
		}else{
			++it;
			inStore = nullptr;
		}
	}
/* rhs will now contain only 0-yield entries so... */
	rhs.emptyStore();
	return *this;
}


int MineralStore::size() const
{
	int total = 0;

	for(auto& m: store)
		total += m->getYield();

	return total;
}


std::ostream& operator<<(std::ostream& ostr, const MineralStore& mstore)
{
	int idx = 1;
	for(const auto& m: mstore.store){
		ostr << "\t[" << idx++ << "]  "
			  << m->getName() << " : "
			  << m->getYield() << " units"
			  << std::endl;
	}

	return ostr;
}


std::vector<Mineral *>::iterator MineralStore::begin()
{
	return store.begin();
}


std::vector<Mineral *>::iterator MineralStore::end()
{
	return store.end();
}


Mineral *MineralStore::operator[](int idx)
{
	return store[idx];
}


bool MineralStore::isEmpty() const
{
	return store.empty();
}
