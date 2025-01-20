// ----- Libraries
// ----------------------------------------------------------------------------
#include "data.h"     

// ----- Data
// ----------------------------------------------------------------------------
PrimitiveSceneNode PrimitiveSceneNodes::origin = {
	.name = "origin"
	,.vertex_array_name = "origin"
	,.transform = {
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f)
		}
	,.shader_name = "axes"
	,.texture_name = ""
	,.element_bools = ElementBools(
					false		// wireframe_mode
					,false		// depth testing
					,false		// stencil testing
					,false		// blending
					,false		// partial render
					,false		// is indexed
					,false		// is triangle
				)
};

PrimitiveSceneNode PrimitiveSceneNodes::points = {
	.name = "points"
	,.vertex_array_name = "plane"
	,.transform = {
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f)
		}
	,.shader_name = "geo"
	,.texture_name = ""
	,.element_bools = ElementBools(
					false,		// wireframe_mode
					false,		// depth testing
					false,		// stencil testing
					false,		// blending
					true,		// partial render
					false		// is indexed
					,false		// is triangle
				)
};


PrimitiveSceneNode PrimitiveSceneNodes::big_cube = {
	.name = "cube"
	,.vertex_array_name = "cube"
	,.transform = {
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(10.0f, 10.0f, 10.0f)
		}
	,.shader_name = "multiplelights"
	,.texture_name = "test_2k",
	.element_bools = ElementBools{
		.wireframe_mode		= false,
		.depth_testing		= true,
		.stencil_testing    = true,
		.blending			= false,
		.partial_render		= false,
		.indexed			= true,
		.is_triangle		= true,
		.is_using_tan_space = false,
		.face_culling		= true,
		.gamma				= false
	}
};


PrimitiveSceneNode PrimitiveSceneNodes::single_cube = {
	.name = "cube"
	,.vertex_array_name = "cube"
	,.transform = {
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.5f, 1.5f, 1.5f)
		}
	,.shader_name = "multiplelights"
	,.texture_name = "out_container"
	,.element_bools = ElementBools(
					false,		// wireframe_mode
					false,		// depth testing
					false,		// stencil testing
					false,		// blending
					false,		// partial render
					false		// is indexed
				)
};


PrimitiveSceneNode PrimitiveSceneNodes::cube_10_0 = {
	.name = "cube"
	,.vertex_array_name = "cube"
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


PrimitiveSceneNode PrimitiveSceneNodes::cube_0_10 = {
	.name = "cube"
	,.vertex_array_name = "cube"
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

PrimitiveSceneNode PrimitiveSceneNodes::paircube1 = {
	.name = "pair cube"
	,.vertex_array_name = "cube"
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

PrimitiveSceneNode PrimitiveSceneNodes::paircube2 = {
	.name = "pair cube"
	,.vertex_array_name = "cube"
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

PrimitiveSceneNode PrimitiveSceneNodes::box_10_0 = {
	.name = "box2"
	,.vertex_array_name = "cube"
	,.transform = {
			Vec3(8.0f, 2.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.5f, 1.5f, 1.5f)
		}
	,.shader_name = "multiplelights"
	,.texture_name = "out_container"
	,.element_bools = ElementBools(
					false,		// wireframe_mode
					false,		// depth testing
					false,		// stencil testing
					false,		// blending
					true,		// partial render
					false		// is indexed
				)
};


PrimitiveSceneNode PrimitiveSceneNodes::box_0_10 = {
	.name = "box2"
	,.vertex_array_name = "cube"
	,.transform = {
			Vec3(0.0f, 2.0f, 8.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.5f, 1.5f, 1.5f)
		}
	,.shader_name = "multiplelights"
	,.texture_name = "out_container"
	,.element_bools = ElementBools(
					false,		// wireframe_mode
					false,		// depth testing
					false,		// stencil testing
					false,		// blending
					true,		// partial render
					false		// is indexed
				)
};

PrimitiveSceneNode PrimitiveSceneNodes::plane01 = {
	.name = "plane01"
	,.vertex_array_name = "plane01"
	,.transform = {
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f)
		}
	,.shader_name = "plight-shadow"
	,.texture_name = ""
	,.element_bools = ElementBools(
					false		// wireframe_mode
					,false		// depth testing
					,false		// stencil testing
					,false		// blending
					,false		// partial render
					,false		// is indexed
					,true		// is triangle
				)
};

PrimitiveSceneNode PrimitiveSceneNodes::plane = {
	.name = "plane"
	,.vertex_array_name = "small_plane"
	,.transform = {
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(10.0f, 10.0f, 10.0f)
		}
	,.shader_name = "green"
	,.texture_name = ""
	,.element_bools = ElementBools(
					false		// wireframe_mode
					,false		// depth testing
					,false		// stencil testing
					,false		// blending
					,false		// partial render
					,false		// is indexed
					,true		// is triangle
				)
};

PrimitiveSceneNode PrimitiveSceneNodes::small_plane = {
	.name = "small_plane"
	,.vertex_array_name = "small_plane"
	,.transform = {
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f)
		}
	,.shader_name = "instance"
	,.texture_name = ""
	,.element_bools = ElementBools(
					false,		// wireframe_mode
					false,		// depth testing
					false,		// stencil testing
					false,		// blending
					false,		// partial render
					false		// is indexedfp
				)
};

PrimitiveSceneNode PrimitiveSceneNodes::ground_platform = {
	.name = "ground_plane"
	,.vertex_array_name = "cube"
	,.transform = {
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(14.0f, 0.2f, 14.0f)
		}
	,.shader_name = "multiplelights"
	,.texture_name = "linegrid_darkgray_2k"
	,.element_bools = ElementBools(
					false,		// wireframe_mode
					false,		// depth testing
					false,		// stencil testing
					false,		// blending
					false,		// partial render
					false		// is indexed
				)
};

PrimitiveSceneNode PrimitiveSceneNodes::axis_x = {
	.name = "axis"
	,.vertex_array_name = "cube"
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

PrimitiveSceneNode PrimitiveSceneNodes::axis_z = {
	.name = "axis"
	,.vertex_array_name = "cube"
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

PrimitiveSceneNode PrimitiveSceneNodes::light_placeholder = {
	.name = "light_placeholder"
	,.vertex_array_name = "icosphere02"
	,.transform = {
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.05f, 0.05f, 0.05f)
		}
	,.shader_name = "3d"
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

PrimitiveSceneNode PrimitiveSceneNodes::nobg_grass = {
	.name = "grass"
	,.vertex_array_name = "plane2"
	,.transform = {
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.5f, 0.5f, 0.5f)
		}
	,.shader_name = "blending"
	,.texture_name = "out_grass"
	,.element_bools = ElementBools(
					false,		// wireframe_mode
					false,		// depth testing
					false,		// stencil testing
					false,		// blending
					false,		// partial render
					false		// is indexed
				)
};

PrimitiveSceneNode PrimitiveSceneNodes::transparent_window = {
	.name = "window"
	,.vertex_array_name = "plane2"
	,.transform = {
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.5f, 0.5f, 0.5f)
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





