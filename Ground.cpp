#include "Ground.h"

Ground::Ground(int w, int h, Frame *fr) : width(w), height(h), frame(fr)
{
	cell_rows = width/8;
	cell_cols = height/8;

//	cells.resize(cell_rows * cell_cols);

	for(int i=0; i<cell_rows*cell_cols; ++i){
		cells.push_back(Cell(8, 8, i%cell_cols, i/cell_cols, frame));
	}
}


Ground::~Ground()
{

}


Cell& Ground::getCell(int x, int y)
{
	if((x < 0 || x >= cell_cols) || (y < 0 || y >= cell_rows)){
		//Error...
	}
	return cells[y*cell_cols + x]; 
}


void Ground::calcMinerals()
{
//	for(auto& c: cells){
//		
//	}
}


int Ground::getRows() const
{
	return cell_rows;
}


int Ground::getCols() const
{
	return cell_cols;
}
