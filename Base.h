#ifndef _BASE_H_
#define _BASE_H_

#include <vector>
#include <iostream>

class Mineral;
class Surface;

class Base
{
public:
	Base(int w, int h, int y, int x, Surface *s=nullptr);
	virtual ~Base();
	virtual void deposit(std::vector<Mineral *>& cargo);
	void listStore() const;
	int getY() const;
	int getX() const;
	virtual void draw(uint32_t *pixels);
	int getWidth() const;
	int getHeight() const;
protected:
	int width, height;
	int y, x;
	Surface *surface;
	std::vector<Mineral *> store;
};

#endif
