// ----- Libraries
// ----------------------------------------------------------------------------
#include "../headers/data/data.h"     

// ----- Data
// ----------------------------------------------------------------------------
PredefSceneElement PredefSceneElements::big_cube = {
	.name = "cube"
	,.mesh = Predef3D::cube_vrts__pos_norm_uv
	,.transform = {
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(10.0f, 10.0f, 10.0f)
		}
	,.shader_name = "multiplelights"
	,.texture_name = "test_2k"
	,.element_bools = ElementBools(
					false,		// wireframe_mode
					true,		// depth testing
					true,		// stencil testing
					false,		// blending
					false,		// partial render
					true		// is indexed
				)
};

PredefSceneElement PredefSceneElements::single_cube = {
	.name = "cube"
	,.mesh = Predef3D::cube_vrts__pos_norm_uv
	,.transform = {
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.5f, 1.5f, 1.5f)
		}
	,.shader_name = "multiplelights"
	,.texture_name = "out_container2"
	,.element_bools = ElementBools(
					false,		// wireframe_mode
					false,		// depth testing
					false,		// stencil testing
					false,		// blending
					false,		// partial render
					false		// is indexed
				)
};


PredefSceneElement PredefSceneElements::cube_10_0 = {
	.name = "cube"
	,.mesh = Predef3D::cube_vrts__pos_norm_uv
	,.transform = {
			Vec3(8.0f, 2.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.5f, 1.5f, 1.5f)
		}
	,.shader_name = "multiplelights"
	,.texture_name = "test_2k"
	,.element_bools = ElementBools(
					false,		// wireframe_mode
					false,		// depth testing
					false,		// stencil testing
					false,		// blending
					true,		// partial render
					false		// is indexed
				)
};


PredefSceneElement PredefSceneElements::cube_0_10 = {
	.name = "cube"
	,.mesh = Predef3D::cube_vrts__pos_norm_uv
	,.transform = {
			Vec3(0.0f, 2.0f, 8.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.5f, 1.5f, 1.5f)
		}
	,.shader_name = "multiplelights"
	,.texture_name = "test_2k"
	,.element_bools = ElementBools(
					false,		// wireframe_mode
					false,		// depth testing
					false,		// stencil testing
					false,		// blending
					false,		// partial render
					false		// is indexed
				)
};

PredefSceneElement PredefSceneElements::paircube1 = {
	.name = "pair cube"
	,.mesh = Predef3D::cube_vrts__pos_norm_uv
	,.transform = {
			Vec3(0.5f, 1.0f, 1.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f)
		}
	,.shader_name = "multiplelights"
	,.texture_name = "grid_2k_white"
	,.element_bools = ElementBools(
					false,		// wireframe_mode
					false,		// depth testing
					false,		// stencil testing
					false,		// blending
					false,		// partial render
					false		// is indexed
				)
};

PredefSceneElement PredefSceneElements::paircube2 = {
	.name = "pair cube"
	,.mesh = Predef3D::cube_vrts__pos_norm_uv
	,.transform = {
			Vec3(0.5f, 1.0f, -1.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f)
		}
	,.shader_name = "multiplelights"
	,.texture_name = "grid_2k_white"
	,.element_bools = ElementBools(
					false,		// wireframe_mode
					false,		// depth testing
					false,		// stencil testing
					false,		// blending
					false,		// partial render
					false		// is indexed
				)
};

PredefSceneElement PredefSceneElements::box_10_0 = {
	.name = "box2"
	,.mesh = Predef3D::cube_vrts__pos_norm_uv
	,.transform = {
			Vec3(8.0f, 2.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.5f, 1.5f, 1.5f)
		}
	,.shader_name = "multiplelights"
	,.texture_name = "out_container2"
	,.element_bools = ElementBools(
					false,		// wireframe_mode
					false,		// depth testing
					false,		// stencil testing
					false,		// blending
					true,		// partial render
					false		// is indexed
				)
};


PredefSceneElement PredefSceneElements::box_0_10 = {
	.name = "box2"
	,.mesh = Predef3D::cube_vrts__pos_norm_uv
	,.transform = {
			Vec3(0.0f, 2.0f, 8.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.5f, 1.5f, 1.5f)
		}
	,.shader_name = "multiplelights"
	,.texture_name = "out_container2"
	,.element_bools = ElementBools(
					false,		// wireframe_mode
					false,		// depth testing
					false,		// stencil testing
					false,		// blending
					true,		// partial render
					false		// is indexed
				)
};

PredefSceneElement PredefSceneElements::ground_plane = {
	.name = "ground_plane"
	,.mesh = Predef3D::cube_vrts__pos_norm_uv
	,.transform = {
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(14.0f, 0.2f, 14.0f)
		}
	,.shader_name = "multiplelights"
	,.texture_name = "linegrid_2k_darkgray"
	,.element_bools = ElementBools(
					false,		// wireframe_mode
					false,		// depth testing
					false,		// stencil testing
					false,		// blending
					false,		// partial render
					false		// is indexed
				)
};

PredefSceneElement PredefSceneElements::axis_x = {
	.name = "axis"
	,.mesh = Predef3D::cube_vrts__pos_norm_uv
	,.transform = {
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(10.0f, 0.02f, 0.02f)
		}
	,.shader_name = "axis-x"
	,.texture_name = ""
	,.element_bools = ElementBools(
					false,		// wireframe_mode
					false,		// depth testing
					false,		// stencil testing
					false,		// blending
					false,		// partial render
					false		// is indexed
				)
};

PredefSceneElement PredefSceneElements::axis_z = {
	.name = "axis"
	,.mesh = Predef3D::cube_vrts__pos_norm_uv
	,.transform = {
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.02f, 0.02f, 10.0f)
		}
	,.shader_name = "axis-z"
	,.texture_name = ""
	,.element_bools = ElementBools(
					false,		// wireframe_mode
					false,		// depth testing
					false,		// stencil testing
					false,		// blending
					false,		// partial render
					false		// is indexed
				)
};

PredefSceneElement PredefSceneElements::light_placeholder = {
	.name = "light_placeholder"
	,.mesh = Predef3D::cube_vrts__pos_norm_uv
	,.transform = {
			Vec3(0.0f, 2.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.1f, 0.1f, 0.1f)
		}
	,.shader_name = "3d"
	,.texture_name = "test_2k"
	,.element_bools = ElementBools(
					false,		// wireframe_mode
					false,		// depth testing
					false,		// stencil testing
					false,		// blending
					true,		// partial render
					false		// is indexed
				)
};

PredefSceneElement PredefSceneElements::nobg_grass = {
	.name = "grass"
	,.mesh = Predef3D::cube_vrts__pos_norm_uv
	,.transform = {
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f)
		}
	,.shader_name = "blending"
	,.texture_name = "out_grass"
	,.element_bools = ElementBools(
					false,		// wireframe_mode
					false,		// depth testing
					false,		// stencil testing
					false,		// blending
					true,		// partial render
					false		// is indexed
				)
};

PredefSceneElement PredefSceneElements::transparent_window = {
	.name = "window"
	,.mesh = Predef3D::cube_vrts__pos_norm_uv
	,.transform = {
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f)
		}
	,.shader_name = "blending"
	,.texture_name = "out_blending_window_blue"
	,.element_bools = ElementBools(
					false,		// wireframe_mode
					false,		// depth testing
					false,		// stencil testing
					false,		// blending
					true,		// partial render
					false		// is indexed
				)
};




