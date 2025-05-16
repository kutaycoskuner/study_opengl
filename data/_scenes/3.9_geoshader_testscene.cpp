	#pragma once
// ----------------------------------------------------------------------------
// ----- libraries
// ----------------------------------------------------------------------------
#include "../../source/headers/data/scene_data.h"
#include "../../headers/utils/utilities.h"
#include <cmath>
#include <ctime>

// ----------------------------------------------------------------------------
// ----- forward declarations
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// ----- abstract
// ----------------------------------------------------------------------------
void GeoShaderTestScene::loadData()
{
	scene_state.animation_stage = 1;
	scene_state.animate = true;
	scene_state.emission_factor = 10.0f;
	scene_state.shininess = 32.0f;
	scene_state.vertex_divider = 9.0f;
	//scene_state.b_model_refraction = true;
	scene_state.display_skybox = true;
	scene_state.model_shader_id = ShaderID::Explode;
	scene_state.display_normals = true;
	scene_state.display_axes = true;

	// ----- camera position
	Camera& cam = cameras[0];
	cam.position = Vec3(-3.3f, 3.6f, 5.6f);
	cam.lookAtTarget(Vec3(0.0f, 1.6f, 0.0f));	
	// normal cam
	//cam.position = Vec3(0.0f, 0.0f, 10.0f);
	//cam.lookAtTarget(Vec3(.2f, 0.0f, -.2f));

	// ----- define lights
	// directional
	directional_lights.push_back(PredefSceneLights::d_light);
	// point
	point_lights.push_back(PredefSceneLights::p_light);
	point_lights.push_back(PredefSceneLights::p_light);
	point_lights.push_back(PredefSceneLights::p_light);
	// spot
	spot_lights.push_back(PredefSceneLights::s_light);
	spot_lights[0].brightness = 0.4f;

	// ----- define predefined elements
	//predefined_scene_elements.push_back(PrimitiveSceneNodes::origin);
	//predefined_scene_elements.push_back(PrimitiveSceneNodes::points);
	//predefined_scene_elements.push_back(PrimitiveSceneNodes::single_cube);
	//predefined_scene_elements[0].shader_name = "cubemaplit";
	//predefined_scene_elements.push_back(PrimitiveSceneNodes::paircube1);
	//predefined_scene_elements.push_back(PrimitiveSceneNodes::paircube2);

	// ----- define model paths
	model_paths = {
		//"models/testobject0_frustum/testobject.obj"
		//,"models/testobject1_dodecahedron/testobject.obj"
		//,"models/testobject2_sphere/testobject.obj"
		//,"models/testobject3_cube0/testobject.obj"
		//,"models/testobject4_cube1/testobject.obj"
		//,"models/testobject5_cube2/testobject.obj"
		//,"models/testobject6_cube3/testobject.obj"
		//,"models/testobject7_torus/testobject.obj"
		//,"models/testobject8_mine/testobject.obj"
		//,"models/testobject9_cylinder/testobject.obj"
		//"models/testobject10_suzanne/testobject.obj"
		//,"models/testobject11_cone/testobject.obj"
		//{"models/out_backpack_by_berkgedik/backpack.obj"}
		{"yurt/models/kokorec_by-berk-gedik_sketchfab/gltf/kokorec.gltf"}

	};


	// ----- create bools for each imported model

	for (int i = 0; i < model_paths.size(); i++) {
        scene_nodes.push_back(SceneNode("ModelName", Transform()));
		scene_state.model_element_bools.push_back(
			ElementBools(
				false,		// wireframe_mode
				false,		// depth testing
				false,		// stencil testing
				false,		// blending
				false,		// partial render
				false		// is indexed
			)
		);
	}


	scene_nodes[0].transform.rotation = Vec3(90.0f, 0.0f, 0.0f);
	//for (int i = 0; i < model_paths.size(); i++)
 //   {
 //           scene_nodes[i].transform
 //   }

	// ----- define texture names
	texture_names = { "out_container", "linegrid_darkgray_2k", "grid_2k_white" };


	// ----- specific position
	scene_state.time_pin = scene_state.time;
}

void GeoShaderTestScene::update() {

	// emission pulse/breath
	// --------------------------------------------------------------------------------------
	float time = scene_state.time;
	float sint = sin(scene_state.time);
	float cost = cos(scene_state.time);
	float sint10 = sin(scene_state.time + 1.0f) * .5f;

	scene_state.emission_factor = sint10 * 0.4f;

	// move camera
	// --------------------------------------------------------------------------------------
	//float camera_pos_multiplier = 12.0f;
	//cameras[0].position = Vec3(camera_pos_multiplier * cost, cameras[0].position.y, camera_pos_multiplier * sint);
	//cameras[0].lookAtTarget(Vec3(0.0f, 3.0f, 0.0f));

	// move lights radial
	// --------------------------------------------------------------------------------------
	float distance_multiplier = 3.0f;
	const float pi = 3.141592f;
	for (int ii = 0; ii < point_lights.size(); ii++)
	{
		// change light position
		point_lights[ii].position = Vec3(
			distance_multiplier * cos(scene_state.time + 2 * pi / point_lights.size() * ii),
			3.0f,
			distance_multiplier * sin(scene_state.time + 2 * pi / point_lights.size() * ii))
			;

		// change light color
		float change_key = scene_state.time + ii;
		setTriangleLightColorShiftByTime(point_lights[ii].diffuse, point_lights[ii].specular, change_key);
	}


	// rotate obj x z 
	// --------------------------------------------------------------------------------------

	// move objects
	// --------------------------------------------------------------------------------------
	float waiting_delay = 4.0f;
	if (scene_state.animation_stage == 1)
	{
		scene_state.tant = 0.0f;
		if (scene_state.time > scene_state.time_pin + waiting_delay)
		{
			scene_state.time_difference = scene_state.time - scene_state.time_pin;
			scene_state.animation_stage += 1;
		}
	}
	else if (scene_state.animation_stage == 2)
	{
		scene_state.tant = abs(tan(scene_state.time - scene_state.time_difference));

		if (scene_state.tant > 6.0f)
		{
			scene_state.tant = 2000.0f;
			scene_state.time_pin = scene_state.time;
			scene_state.animation_stage += 1;
		}
	}
	else if (scene_state.animation_stage == 3)
	{
		scene_state.tant = 2000.0f;
		if (scene_state.time > scene_state.time_pin + waiting_delay - .8f)
		{
			scene_state.time_difference = scene_state.time - scene_state.time_pin;
			scene_state.animation_stage += 1;
		}
	}
	else if (scene_state.animation_stage == 4)
	{
		scene_state.tant = abs(tan(scene_state.time));

		if (scene_state.tant < 0.05f)
		{
			scene_state.tant = 0.0f;
			scene_state.time_pin = scene_state.time;
			scene_state.animation_stage = 1;
		}
	}
	// sort objects
	// --------------------------------------------------------------------------------------


}

GeoShaderTestScene::GeoShaderTestScene() {
}


