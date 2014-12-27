#include "Base.h"
#include "Mineral.h"
#include "Surface.h"
#include "resources.h"


Base::Base(int w, int h, int y, int x, Surface *s) : width(w),
						     height(h),
						     y(y), x(x),
						     surface(s)
{
//	mine = SDL_LoadBMP("mine1.bmp");	
	SDL_RWops* mine_bmp_rwo = SDL_RWFromConstMem(static_cast<const void *>(mine1_bmp), mine1_bmp_len);
	mine = SDL_LoadBMP_RW(mine_bmp_rwo, 1);
	SDL_SetColorKey(mine, SDL_TRUE, 0x00);
}


Base::~Base()
{
	surface = nullptr;
	SDL_FreeSurface(mine);
}


void Base::deposit(std::vector<Mineral *>& cargo)
{
	bool present = false;
	Mineral *inStore = nullptr;

	for(auto it = cargo.begin() ; it != cargo.end() ; ){
		for(auto& m: store){
			if(m->getName() == (*it)->getName()){
				present = true;
				inStore = m;
			}
		}
		if(!present){
			store.push_back(*it);
			cargo.erase(it);
		}else{
			inStore->setYield(inStore->getYield() + (*it)->getYield());
			(*it)->setYield(0);
			it++;
			present = false;
			inStore = nullptr;
		}
	}
	listStore();
}


void Base::listStore() const
{
	int idx=1;
	std::cout << "Base store contains:" << std::endl;
	for(auto& m: store){
		std::cout << "\t[" << idx++ << "]  "
			  << m->getYield() << " units "
			  << m->getName() << std::endl;
	}
}


int Base::getX() const
{
	return x;
}


int Base::getY() const
{
	return y;
}


int Base::getWidth() const
{
	return width;
}


int Base::getHeight() const
{
	return height;
}


void Base::draw(SDL_Surface *destsurf)
{
/*	for(int r=0; r<height; ++r){
		for(int c=0; c<width; ++c){
			pixels[r*surface->getWidth()+c] = 0x00606060;
		}
	}

	for(int p=0; p<width; p+=width/6){
		for(int r=0; r<4; ++r){
			for(int c=0; c<(3-r); ++c){
				pixels[r*surface->getWidth()+p+c] = 0x00528EFF;
			}
		}
	}
*/
	SDL_Rect dest = {destsurf->w/2-mine->w/2+2, destsurf->h-mine->h-6, mine->w, mine->h};
	SDL_BlitSurface(mine, nullptr, destsurf, &dest);

}
