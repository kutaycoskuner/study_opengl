#include "../../headers/abstract/application.h"
#include "../../headers/abstract/uniforms.h"
#include "../../headers/abstract/shader.h"
#include "../../headers/data/data.h"
#include "../../headers/utils/utilities.h"
#include "../../headers/abstract/model.h"

#include <iostream>

// self keywords
// ----------------------------------------------------------------------------
using uint = unsigned int;		// unsigned int yerine uint kisayolu tanim
using namespace math_utils;
using namespace str_utils;
using namespace file_utils;
using namespace img_utils;

// functions definitions
// ----------------------------------------------------------------------------

void Application::importModelScene(Uniforms& uni)
{


	// setting abbreviations
	const SceneState& ss = scene_state;
	// setting uniform names
	UniformsPerObject& uni_obj = uni.upo;
	UniformsPerView& uni_view = uni.upv;
	UniformsPerFrame& uni_frame = uni.upf;
	// create transformations
	uni_obj.world_matrix = mat_utils::rotationX(radian(-45.0f))
		* mat_utils::rotationXYZ(ss.time, Vec3(1.0f, 1.0f, 1.0f).normalized())
		;
	uni_view.view_matrix = ss.camera.calcViewMatrix(world_up);
	uni_view.projection_matrix
		= mat_utils::projectPerspective(radian(ss.camera.fov), ss.camera.aspect_ratio, ss.camera.near, ss.camera.far);
	uni_view.view_proj_matrix = uni_view.projection_matrix * uni_view.view_matrix;



	//drawAxis(vaos[0], "3d", uni);
	drawLightPlaceholder(vaos[0], "3d", uni);
	drawModel(ss.model, lit_vao, "multiplelights", uni);

}