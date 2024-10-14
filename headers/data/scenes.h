#pragma once
// ----------------------------------------------------------------------------
// ----- libraries
// ----------------------------------------------------------------------------
#include "../../headers/abstract/scene.h"
#include "../../headers/data/data.h"
#include <iostream>


// ----------------------------------------------------------------------------
// ----- forward declarations
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// ----- abstract
// ----------------------------------------------------------------------------
class TestScene : public Scene {
public:
	void loadData() override;
	void update() override;

	TestScene();
};


class MultipleLightsTestScene : public Scene {
public:
	void loadData() override;
	void update() override;

	MultipleLightsTestScene();
};

class ImportModelTestScene : public Scene {
public:
	void loadData() override;
	void update() override;

	ImportModelTestScene();
};

class OutlinerTestScene : public Scene {
public:
	void loadData() override;
	void update() override;

	OutlinerTestScene();
};

class BlendingTestScene : public Scene {
public:
	void loadData() override;
	void update() override;

	BlendingTestScene();
};

class FaceCullingTestScene : public Scene {
public:
	void loadData() override;
	void update() override;

	FaceCullingTestScene();
};

class FrameBufferTestScene : public Scene {
public:
	void loadData() override;
	void update() override;

	FrameBufferTestScene();
};

class CubemapTestScene : public Scene {
public:
	void loadData() override;
	void update() override;

	CubemapTestScene();
};

class AdvancedGLSLTestScene : public Scene {
public:
	void loadData() override;
	void update() override;

	AdvancedGLSLTestScene();
};

class GeoShaderTestScene : public Scene {
public:
	void loadData() override;
	void update() override;

	GeoShaderTestScene();
};

class InstancingTestScene : public Scene {
public:
	void loadData() override;
	void update() override;

	InstancingTestScene();
};

class AntiAliasingTestScene : public Scene {
public:
	void loadData() override;
	void update() override;

	AntiAliasingTestScene();
};

class BlinnPhongTestScene : public Scene {
public:
	void loadData() override;
	void update() override;

	BlinnPhongTestScene();
};

class GammaCorrectionTestScene : public Scene {
public:
	void loadData() override;
	void update() override;

	GammaCorrectionTestScene();
};

