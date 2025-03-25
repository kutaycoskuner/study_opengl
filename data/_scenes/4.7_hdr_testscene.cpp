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
void HDRTestScene::loadData()
{
	scene_state.animate = true;
	scene_state.emission_factor = -1.0f;
	scene_state.shininess = 32.0f;
	// scene_state.vertex_divider = 9.0f;
	//scene_state.b_model_refraction = true;
	//scene_state.display_skybox = true;  
	// scene_state.model_shader_name = "explode";
	// scene_state.display_normals = true;
	scene_state.display_axes = true;
        scene_state.use_ssao     = true;

	// camera pos
	// ----------------------------------------------------------------
	cameras[0].position = Vec3(0.0f, 0.0f, 20.0f);
	cameras[0].position = Vec3(-2.0f, 0.0f, 10.0f);
	cameras[0].position = Vec3(-8.0f, 4.0f, 0.0f);
	//cameras[0].position = Vec3(-3.0f, 1.0f, 0.0f);
	//cameras[0].position = Vec3(0.0f, 0.0f, 14.0f);
	//cameras[0].position = Vec3(0.0f, 1.86f, 0.0f);
	cameras[0].lookAtDirection(Vec3(1.0f, 0.0f, 0.0f));
	//cameras[0].lookAtTarget(Vec3(0.0f, 0.0f, 0.0f));
	//cameras[0].position = Vec3(0.0f, 10.0f, 10.0f);
	cameras[0].yaw_rad   = +1.520f;
	cameras[0].pitch_rad = -0.200f;

	// light definitions
	// ----------------------------------------------------------------
	// directional
	//directional_lights.push_back(PredefSceneLights::d_light);
	//DirectionalLight& dl0 = directional_lights[0];
	//dl0.brightness = 1.0f;
	//dl0.direction = Vec3(0.0f, -1.0f, 0.0f);

	// point6
	point_lights.push_back(PredefSceneLights::p_light);
	point_lights.back().diffuse     = Vec3(1.0f, 1.0f, 1.0f);
	point_lights.back().brightness  = 100.0f;
	point_lights.back().position    = Vec3(1.0, 2.0f, 1.0f);

	point_lights.push_back(PredefSceneLights::p_light);
	point_lights.back().diffuse = Vec3(1.0f, 0.0f, 0.0f);
	point_lights.back().brightness = 1.0f;
	point_lights.back().position = Vec3(-1.0, 2.0f, 1.0f);

	point_lights.push_back(PredefSceneLights::p_light);
	point_lights.back().diffuse = Vec3(0.0f, 1.0f, 0.0f);
	point_lights.back().brightness = 1.0f;
	point_lights.back().position = Vec3(1.0, 2.0f, -1.0f);

	point_lights.push_back(PredefSceneLights::p_light);
	point_lights.back().diffuse = Vec3(0.0f, 0.0f, 1.0f);
	point_lights.back().brightness = 1.0f;
	point_lights.back().position = Vec3(-1.0, 2.0f, -1.0f);


	// spot
	//spot_lights.push_back(PredefSceneLights::s_light);
	//spot_lights[0].position = Vec3(0.0f, 8.0f, 0.0f);
	//spot_lights[0].diffuse = Vec3(1.0f, 1.0f, 1.0f);
	//spot_lights[0].brightness = 2.0f;

	// primitive scene objects
	// ----------------------------------------------------------------
	//predefined_scene_elements.push_back(PrimitiveSceneNodes::plane01);
	//PrimitiveSceneNode& element				 = predefined_scene_elements.back();
	//element.transform.scale					 = Vec3(1.0f, 1.0f, 1.0f);
	//element.transform.rotation				 = Vec3(0.0f, -90.0f, 0.0f);
	//element.transform.position				 = Vec3(0.0f, 1.0f, 0.0f);
	//element.texture_name					 = "gamma-test-rgb";
	//element.shader_name						 = "diffuse";
	//element.element_bools.is_using_tan_space = true;


	for (int i = 0; i < predefined_scene_elements.size(); i++)
	{
		Transform transform;
		predefined_scene_element_transforms.push_back(transform);
		predefined_scene_element_transforms[i].position = predefined_scene_elements[i].transform.position;
	}

	// textures to cache for objects
	// ----------------------------------------------------------------
	texture_names = { "out_planks023a", "out_container", "out_brickwall", "gamma-test-rgb", "gamma-test-srgb"};

	// models
	// ----------------------------------------------------------------
	scene_state.model_shader_name = "hdr";
	model_paths = {
		//"models/out_kokorecci_by_berkgedik/out_kokorecci_by_berk gedik.obj"
		"yurt/scenes/sponza_crytek/gltf/Sponza.gltf"
		//"models/testobject0_frustum/testobject.obj",
		//"models/testobject1_dodecahedron/testobject.obj",
	};

	// ---- create bools for each imported model
	for (int i = 0; i < model_paths.size(); i++) {
		scene_nodes.push_back(SceneNode("ModelName", Transform()));
		scene_state.model_element_bools.push_back(
			ElementBools{
				.wireframe_mode      = false,
				.depth_testing       = false,
				.stencil_testing	 = false,
				.blending			 = false,
				.partial_render	     = false,
				.indexed		     = false,
				.is_triangle		 = true,
				.is_using_tan_space  = false,
				.face_culling		 = false,
				.gamma			     = false
			}
		);
	}

	if (scene_nodes.size() > 0)
		scene_nodes[0].transform.scale = Vec3(0.01f, 0.01f, 0.01f);

}

void HDRTestScene::update() {
	// emission pulse/breath
	// ----------------------------------------------------------------
	float time = scene_state.time;
	float sint = sin(scene_state.time);
	float cost = cos(scene_state.time);
	float sint10 = sin(scene_state.time + 1.0f) * .5f;
	//scene_state.emission_factor = sint10;


	// move lights radial
	// ----------------------------------------------------------------


	// light move rectangular
	// ----------------------------------------------------------------


	// rotate obj x z 
	// ----------------------------------------------------------------


	// move objects
	// ----------------------------------------------------------------
}

HDRTestScene::HDRTestScene() {
}


