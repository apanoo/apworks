#include "BatchRenderer2d.h"

nario::BatchRenderer2d::~BatchRenderer2d()
{
	delete _IBO;
}

void nario::BatchRenderer2d::submit(Renderable2d* renderable)
{

}

void nario::BatchRenderer2d::flush()
{

}

void nario::BatchRenderer2d::init()
{

}

nario::BatchRenderer2d::BatchRenderer2d()
{
	init();
}

