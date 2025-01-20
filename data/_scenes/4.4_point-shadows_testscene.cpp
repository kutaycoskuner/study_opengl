#pragma once
// ----------------------------------------------------------------------------
//				libraries
// ----------------------------------------------------------------------------
#include "../../headers/data/scenes.h"

// ----------------------------------------------------------------------------
//				forward declarations
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
//				abstract
// ----------------------------------------------------------------------------
void PointShadowsTestScene::loadData()
{
	scene_state.animate = true;
	scene_state.emission_factor = -1.0f;
	scene_state.shininess = 32.0f;
	// scene_state.vertex_divider = 9.0f;
	//scene_state.b_model_refraction = true;
	scene_state.display_skybox = true;  
	// scene_state.model_shader_name = "explode";
	// scene_state.display_normals = true;
	scene_state.display_axes = true;

	// camera pos
	// ----------------------------------------------------------------
	cameras[0].position = Vec3(0.0f, 0.0f, 20.0f);
	cameras[0].position = Vec3(-7.0f, 0.0f, 20.0f);
	cameras[0].lookAtTarget(Vec3(0.0f, 0.0f, 0.0f));
	//cameras[0].position = Vec3(0.0f, 10.0f, 10.0f);
	//cameras[0].pitch_rad = 0.785f;
	//cameras[0].yaw_rad = -1.120f;

	// light definitions
	// ----------------------------------------------------------------
	// directional
	//directional_lights.push_back(PredefSceneLights::d_light);
	//directional_lights[0].brightness = 1.0f;

	// point6
	point_lights.push_back(PredefSceneLights::p_light);
	point_lights.back().brightness = 6.0f;
	//point_lights.push_back(PredefSceneLights::p_light);
	//point_lights.push_back(PredefSceneLights::p_light);

	// spot
	//spot_lights.push_back(PredefSceneLights::s_light);
	//spot_lights[0].position = Vec3(0.0f, 8.0f, 0.0f);
	//spot_lights[0].diffuse = Vec3(1.0f, 1.0f, 1.0f);
	//spot_lights[0].brightness = 2.0f;

	// objects
	// ----------------------------------------------------------------

	// front
	//predefined_scene_elements.push_back(PrimitiveSceneNodes::plane01);
	//predefined_scene_elements.back().transform.scale = Vec3(9.0f, 5.0f, 5.0f);
	//predefined_scene_elements.back().transform.rotation = Vec3(-90.0f, 0.0f, 0.0f);
	//predefined_scene_elements.back().transform.position = Vec3(0.0f, 0.0f, 5.0f);
	//predefined_scene_elements.back().texture_name = "out_planks023a";
	//predefined_scene_elements.back().shader_name = "plight-shadow";
	//predefined_scene_elements.back().element_bools.face_culling = true;
	//predefined_scene_elements.back().shader_name = "multiplelights";

	// back
	predefined_scene_elements.push_back(PrimitiveSceneNodes::plane01);
	predefined_scene_elements.back().transform.scale	= Vec3(9.0f, 5.0f, 5.0f);
	predefined_scene_elements.back().transform.rotation = Vec3(90.0f, 0.0f, 0.0f);
	predefined_scene_elements.back().transform.position = Vec3(0.0f, 0.0f, -5.0f);
	predefined_scene_elements.back().texture_name		= "out_planks023a";
	predefined_scene_elements.back().shader_name = "plight-shadow";
	//predefined_scene_elements.back().shader_name = "multiplelights";

	// bottom
	predefined_scene_elements.push_back(PrimitiveSceneNodes::plane01);
	predefined_scene_elements.back().transform.scale = Vec3(9.0f, 5.0f, 5.0f);
	predefined_scene_elements.back().transform.rotation = Vec3(0.0f, 0.0f, 0.0f);
	predefined_scene_elements.back().transform.position = Vec3(0.0f, -5.0f, 0.0f);
	predefined_scene_elements.back().texture_name = "out_planks023a";
	predefined_scene_elements.back().shader_name = "plight-shadow";

	// top
	predefined_scene_elements.push_back(PrimitiveSceneNodes::plane01);
	predefined_scene_elements.back().transform.scale = Vec3(9.0f, 5.0f, 5.0f);
	predefined_scene_elements.back().transform.rotation = Vec3(180.0f, 0.0f, 0.0f);
	predefined_scene_elements.back().transform.position = Vec3(0.0f, 5.0f, 0.0f);
	predefined_scene_elements.back().texture_name = "out_planks023a";
	predefined_scene_elements.back().shader_name = "plight-shadow";

	// left
	predefined_scene_elements.push_back(PrimitiveSceneNodes::plane01);
	predefined_scene_elements.back().transform.scale = Vec3(5.0f, 5.0f, 5.0f);
	predefined_scene_elements.back().transform.rotation = Vec3(0.0f, 0.0f, -90.0f);
	predefined_scene_elements.back().transform.position = Vec3(-9.0f, 0.0f, 0.0f);
	predefined_scene_elements.back().texture_name = "out_planks023a";
	predefined_scene_elements.back().shader_name = "plight-shadow";

	// right
	predefined_scene_elements.push_back(PrimitiveSceneNodes::plane01);
	predefined_scene_elements.back().transform.scale = Vec3(5.0f, 5.0f, 5.0f);
	predefined_scene_elements.back().transform.rotation = Vec3(0.0f, 0.0f, 90.0f);
	predefined_scene_elements.back().transform.position = Vec3(9.0f, 0.0f, 0.0f);
	predefined_scene_elements.back().texture_name = "out_planks023a";
	predefined_scene_elements.back().shader_name = "plight-shadow";


	// ----------------------------------------------------------------
	// cube top left
	predefined_scene_elements.push_back(PrimitiveSceneNodes::single_cube);
	predefined_scene_elements.back().transform.scale = Vec3(1.5f, 1.5f, 1.5f);
	predefined_scene_elements.back().transform.rotation = Vec3(15.0f, 21.0f, 13.0f);
	predefined_scene_elements.back().transform.position = Vec3(-3.0f, 1.0f, -1.5f);
	predefined_scene_elements.back().shader_name = "plight-shadow";

	// cube right
	predefined_scene_elements.push_back(PrimitiveSceneNodes::single_cube);
	predefined_scene_elements.back().transform.scale = Vec3(1.5f, 1.5f, 1.5f);
	predefined_scene_elements.back().transform.rotation = Vec3(0.0f, 36.0f, 45.0f);
	predefined_scene_elements.back().transform.position = Vec3(2.4f, 2.0f, -1.2f);
	predefined_scene_elements.back().shader_name = "plight-shadow";

	// cube bottom
	predefined_scene_elements.push_back(PrimitiveSceneNodes::single_cube);
	predefined_scene_elements.back().transform.scale = Vec3(1.5f, 1.5f, 1.5f);
	predefined_scene_elements.back().transform.rotation = Vec3(0.0f, 25.0f, 42.0f);
	predefined_scene_elements.back().transform.position = Vec3(2.0f, -3.0f, 2.0f);
	predefined_scene_elements.back().shader_name = "plight-shadow";
	// ----------------------------------------------------------------



	//// cube x+
	//predefined_scene_elements.push_back(PrimitiveSceneNodes::single_cube);
	//predefined_scene_elements.back().transform.scale = Vec3(1.5f, 1.5f, 1.5f);
	////predefined_scene_elements.back().transform.rotation = Vec3(15.0f, 21.0f, 13.0f);
	//predefined_scene_elements.back().transform.rotation = Vec3(10.0f, 0.0f, 22.0f);
	////predefined_scene_elements.back().transform.position = Vec3(-3.0f, 1.0f, -1.5f);
	//predefined_scene_elements.back().transform.position = Vec3(3.0f, 0.0f, 0.0f);
	//predefined_scene_elements.back().shader_name = "plight-shadow";

	////// cube x-
	//predefined_scene_elements.push_back(PrimitiveSceneNodes::single_cube);
	//predefined_scene_elements.back().transform.scale = Vec3(1.5f, 1.5f, 1.5f);
	//predefined_scene_elements.back().transform.rotation = Vec3(10.0f, 0.0f, 10.0f);
	////predefined_scene_elements.back().transform.position = Vec3(2.0f, -3.0f, -2.0f);
	//predefined_scene_elements.back().transform.position = Vec3(-4.0f, 0.0f, 0.0f);
	//predefined_scene_elements.back().shader_name = "plight-shadow";

	////// cube y+
	//predefined_scene_elements.push_back(PrimitiveSceneNodes::single_cube);
	//predefined_scene_elements.back().transform.scale = Vec3(1.5f, 1.5f, 1.5f);
	////predefined_scene_elements.back().transform.rotation = Vec3(0.0f, 36.0f, 45.0f);
	//predefined_scene_elements.back().transform.rotation = Vec3(0.0f, 12.0f, 0.0f);
	////predefined_scene_elements.back().transform.position = Vec3(3.0f, 2.0f, 2.5f);
	//predefined_scene_elements.back().transform.position = Vec3(0.0f, 3.0f, 0.0f);
	////predefined_scene_elements.back().transform.position = Vec3(0.0f, 3.0f, 0.0f);
	//predefined_scene_elements.back().shader_name = "plight-shadow";

	////// cube y-
	//predefined_scene_elements.push_back(PrimitiveSceneNodes::single_cube);
	//predefined_scene_elements.back().transform.scale = Vec3(1.5f, 1.5f, 1.5f);
	//predefined_scene_elements.back().transform.rotation = Vec3(0.0f, 20.0f, 0.0f);
	////predefined_scene_elements.back().transform.position = Vec3(3.0f, 2.0f, 2.5f);
	//predefined_scene_elements.back().transform.position = Vec3(0.0f, -3.0f, 0.0f);
	////predefined_scene_elements.back().transform.position = Vec3(0.0f, 3.0f, 0.0f);
	//predefined_scene_elements.back().shader_name = "plight-shadow";

	////// cube z-
	//predefined_scene_elements.push_back(PrimitiveSceneNodes::single_cube);
	//predefined_scene_elements.back().transform.scale = Vec3(1.5f, 1.5f, 1.5f);
	//predefined_scene_elements.back().transform.rotation = Vec3(0.0f, 0.0f, 5.0f);
	////predefined_scene_elements.back().transform.rotation = Vec3(0.0f, 25.0f, 42.0f);
	////predefined_scene_elements.back().transform.position = Vec3(2.0f, -3.0f, -2.0f);
	//predefined_scene_elements.back().transform.position = Vec3(0.0f, 0.0f, -3.0f);
	//predefined_scene_elements.back().shader_name = "plight-shadow";






	for (int i = 0; i < predefined_scene_elements.size(); i++)
	{
		Transform transform;
		predefined_scene_element_transforms.push_back(transform);
		predefined_scene_element_transforms[i].position = predefined_scene_elements[i].transform.position;
	}

	//predefined_scene_elements[0].texture_name = "out_planks023a";
	//predefined_scene_elements[0].transform = {
	//		Vec3(0.0f, -0.85f, 0.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(50.0f, 0.2f, 50.0f)
	//};

	//predefined_scene_elements[0].shader_name = "light-shadow";

	//predefined_scene_elements[0].tiling_factor = 4.0f;

	//predefined_scene_elements[1].transform = {
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		//Vec3(0.0f, 0.0f, -4.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(1.5f, 1.5f, 1.5f)
	//};
	//predefined_scene_elements[1].shader_name = "light-shadow";

	//predefined_scene_elements[2].transform = {
	//	Vec3(3.0f, 2.0f, 3.0f),
	//	//Vec3(0.0f, 0.0f, 4.0f),
	//	Vec3(0.0f, -48.0f, 0.0f),
	//	//Vec3(0.0f, 0.0f, 0.0f),
	//	Vec3(1.5f, 1.5f, 1.5f)
	//};
	//predefined_scene_elements[2].shader_name = "light-shadow";


	//predefined_scene_elements[3].transform = {
	//Vec3(-2.0f, 0.0f, 4.0f),
	//Vec3(0.0f, -28.0f, 0.0f),
	//Vec3(1.5f, 1.5f, 1.5f)
	//};
	//predefined_scene_elements[3].shader_name = "light-shadow";

	// textures to cache for objects
	// ----------------------------------------------------------------
	texture_names = { "out_planks023a", "out_container2" };

	// models
	// ----------------------------------------------------------------
	model_paths = {
		//"models/testobject0_frustum/testobject.obj",
		//"models/testobject1_dodecahedron/testobject.obj",
	};

	// ---- create bools for each imported model
	for (int i = 0; i < model_paths.size(); i++) {
		scene_state.model_element_bools.push_back(
			ElementBools(
				false,		// wireframe_mode
				false,		// depth testing
				false,		// stencil testing
				false		// blending
			)
		);
	}

}

void PointShadowsTestScene::update() {
	// emission pulse/breath
	// ----------------------------------------------------------------
	float time = scene_state.time;
	float sint = sin(scene_state.time);
	float cost = cos(scene_state.time);
	float sint10 = sin(scene_state.time + 1.0f) * .5f;
	//scene_state.emission_factor = sint10;


	// move lights radial
	// ----------------------------------------------------------------
	float distance_multiplier = 3.0f;
	const float pi = 3.141592f;

	//Vec3 origin = (0.0f, 0.0f, 0.0f);
	//directional_lights[0].direction = (origin - directional_lights[0].position);

	for (int ii = 0; ii < point_lights.size(); ii++)
	{
		// change light position
		point_lights[0].position.x 
			= distance_multiplier * cos(scene_state.time + 2 * pi / point_lights.size() * ii);
		point_lights[0].position.y
			= 4.0f * sinf(scene_state.time);
		//point_lights[0].position.z
		//	= distance_multiplier * sin(scene_state.time + 2 * pi / point_lights.size() * ii);


		// change light color
		float change_key = scene_state.time + ii;
		setTriangleLightColorShiftByTime(point_lights[ii].diffuse, point_lights[ii].specular, change_key);
	}


	// rotate obj x z 
	// ----------------------------------------------------------------
	for (int i = 0; i < predefined_scene_elements.size(); i++)
	{
		//if (predefined_scene_elements[i].name == "ground_plane")
		//	continue;
		//if (predefined_scene_elements[i].name == "light_placeholder")
		//	continue;
		//float x = predefined_scene_elements[i].transform.rotation.x;
		//float y = predefined_scene_elements[i].transform.rotation.y;
		//float z = predefined_scene_elements[i].transform.rotation.z;
		//predefined_scene_elements[i].transform.rotation
		//	= Vec3(fmod(time * 40.0f, 360.0f), y, fmod(time * 40.0f, 360.0f));
	}


	// move objects
	// ----------------------------------------------------------------
	bool b_offset = false;
	float time_offset = sint;

	//predefined_scene_elements[7].transform.position.x = 5.0f * sint;
	//predefined_scene_elements[7].transform.position.y = 3.0f * cost;
	//for (int i = 0; i < predefined_scene_elements.size(); i++)
	//{
	//	if (predefined_scene_elements[i].name == "ground_plane")
	//		continue;
	//	if (predefined_scene_elements[i].name == "light_placeholder")
	//		continue;
	//	b_offset = !b_offset;
	//	time_offset = sint;
	//	if (b_offset) time_offset = sin(time + 3.14f / 2.0f);
	//	float x = predefined_scene_element_transforms[i].position.x;
	//	float y = predefined_scene_elements[i].transform.position.y;
	//	float z = predefined_scene_element_transforms[i].position.z;
	//	predefined_scene_elements[i].transform.position
	//		= Vec3(time_offset * x, y, time_offset * z);
	//}
}

PointShadowsTestScene::PointShadowsTestScene() {
}


