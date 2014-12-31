#include "MineralStore.h"
#include "Mineral.h"

#include <typeinfo>


MineralStore::MineralStore(int szhint)
{
	store.reserve(szhint);
}


MineralStore::~MineralStore()
{

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
	Mineral *inStore = nullptr;

	for(auto& r: rhs.store){
		for(auto& m: store){
			if(typeid(*m) == typeid(*r)){
				inStore = m;
				*m += *r;
			}
		}

		if(!inStore){
			store.push_back(&(*r));
		}
		inStore = nullptr;
	}

	Mineral *rmin;
	for(auto it = rhs.store.begin(); it != rhs.store.end(); ){
		rmin = *it;
		if(rmin->getYield() == 0){
			delete rmin;
			rhs.store.erase(it);
		}else{
			++it;
		}
	}

	return *this;
}
