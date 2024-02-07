#pragma once
// ---------------------------------------------------------------------------------------
// ----- libraries
// ---------------------------------------------------------------------------------------
#include "../abstract/camera.h"
#include "../abstract/light.h"
#include "../abstract/scene_state.h"
#include "../abstract/uniforms.h"
#include "../events/events.h"
#include "../events/input_observer.h"
#include "../data/data.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>


// ---------------------------------------------------------------------------------------
// ----- forward declarations
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
// ----- abstract
// ---------------------------------------------------------------------------------------
class Scene : public InputListener// see :root > headers > scenes > ...
{
private:
	std::unordered_set<InputEvent> active_input_events;
public:
	// cameras
	std::vector<PredefSceneElement> predefined_scene_elements;
	std::vector<Transform>			predefined_scene_element_transforms;
	
	std::vector<std::string>		model_paths;
	std::vector<Model>				models;

	std::vector<RelativePaths>		shader_paths;
	std::unordered_set<std::string> texture_names;
	std::vector<Material>			materials;

	std::vector<Camera>				cameras;
	
	std::vector<DirectionalLight>	directional_lights;
	std::vector<PointLight>			point_lights;
	std::vector<SpotLight>			spot_lights;
	
	SceneState						scene_state;
	// lights

	// shaders

	// state

	// models
	virtual void loadData() = 0; // = 0 varsa pure virtual implement edilmesi zorunlu
	virtual void update() = 0;

	// handlers
	//void onKeyPress(int keys) override;
	//void onKeyRelease(int key) override;
	void onMultipleKeyPress(std::vector<int> keys) override;

	// default constructor
		// Default constructor
	Scene() {}
	//	: test(2) {}

	// Virtual destructor
	virtual ~Scene() {}
};