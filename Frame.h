#ifndef _FRAME_H_
#define _FRAME_H_

class Cell;
class Ground;
class Surface;

class Frame
{
public:
	Frame(int w, int h);
	virtual ~Frame();
	Surface *getSurface() const;
	void draw();
protected:
	int width;
	int height;
	Ground *ground;
	Surface *surface;
};

#endif
