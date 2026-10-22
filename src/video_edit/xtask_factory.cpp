#include "xtask_factory.h"
#include <iostream>
#include "fftask.h"
std::unique_ptr<XTask> XTaskFactory::Creat(int type) {
	switch (type)
	{
	case 0:
		return std::make_unique<FFtask>();
	default:
		std::cerr << "Type" << type << "not support!" << std::endl;
		break;
	}
		
	return nullptr;
			
}