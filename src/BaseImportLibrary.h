#pragma once

class BaseImportLibrary
{
public:
	virtual void Import(const char* path);
	virtual ~BaseImportLibrary();
};