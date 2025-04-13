#pragma once
#include "BaseImportLibrary.h"
#include "Objects.h"

class AssimpLibrary : public BaseImportLibrary
{
public:
	AssimpLibrary();
	virtual void Import(const char* modelPath) override;
	~AssimpLibrary();
};