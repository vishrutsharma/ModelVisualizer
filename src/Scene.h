#pragma once

#include "Model.h"

class Scene
{
public:
	Scene();
	~Scene();
	void Init();
	void Update();

private :
	Model* m_model;
};