#pragma once
#include "Object.h"

class Player : public Object {
private:
	void CreateMissile();

public:
	virtual void Update();
	
};

