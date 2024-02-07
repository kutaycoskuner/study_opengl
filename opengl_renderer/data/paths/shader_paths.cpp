// libraries
// ---------------------------------------------------------------------------------------
#include "../headers/data/data.h"     
// 

const std::vector<ShaderPaths> RelativePaths::shader_paths =
{
	{
		"source/shaders/2.0.phong_lit_vrtx_shader.glsl",
		"source/shaders/2.0.phong_lit_frag_shader.glsl",
	}
	,{
		"source/shaders/1.0.3d_vrtx_shader.glsl",
		"source/shaders/1.0.3d_frag_shader.glsl"
	}
	,{
		"source/shaders/1.1.axis-x_vrtx_shader.glsl",
		"source/shaders/1.1.axis-x_frag_shader.glsl"
	}
	,{
		"source/shaders/1.1.axis-z_vrtx_shader.glsl",
		"source/shaders/1.1.axis-z_frag_shader.glsl"
	}
	,{
		"source/shaders/2.1.lightmap_lit_vrtx_shader.glsl",
		"source/shaders/2.1.lightmap_lit_frag_shader.glsl"
	}
	,{
		"source/shaders/2.2.lightcaster-directional_lit_vrtx_shader.glsl",
		"source/shaders/2.2.lightcaster-directional_lit_frag_shader.glsl"
	}
	,{
		"source/shaders/2.2.lightcaster-point_lit_vrtx_shader.glsl",
		"source/shaders/2.2.lightcaster-point_lit_frag_shader.glsl"
	}
	,{
		"source/shaders/2.2.lightcaster-spot_lit_vrtx_shader.glsl",
		"source/shaders/2.2.lightcaster-spot_lit_frag_shader.glsl"
	}
	,{
		"source/shaders/2.3.multiplelights_lit_vrtx_shader.glsl",
		"source/shaders/2.3.multiplelights_lit_frag_shader.glsl"
	}
	,{
		"source/shaders/3.0.depthtesting_lit_vrtx_shader.glsl",
		"source/shaders/3.0.depthtesting_lit_frag_shader.glsl"
	}
	,{
		"source/shaders/3.1.stenciltesting_vrtx_shader.glsl",
		"source/shaders/3.1.stenciltesting_frag_shader.glsl"
	}
	,{
		"source/shaders/3.1.stenciltesting02_vrtx_shader.glsl",
		"source/shaders/3.1.stenciltesting02_frag_shader.glsl"
	}
	,{
		"source/shaders/3.2.blending_vrtx_shader.glsl",
		"source/shaders/3.2.blending_frag_shader.glsl"
	}
};

// another model try with keys. this approach is abstracting the identifier from file names.
// however abondoned because file name already providing necessary info

//const std::map<std::string, std::vector<std::string>> test =
//{
//	{ "test",
//		{
//			"",
//			""
//		}
//	}
//	,{ "3d",
//		{
//			"shaders/3d_vrtx_shader.glsl",
//			"shaders/3d_frag_shader.glsl"
//		}
//	}
//	,{ "phong",
//		{
//			"shaders/phong_lit_vrtx_shader.glsl",
//			"shaders/phong_lit_frag_shader.glsl"
//		}
//	}
//	,{ "phong",
//		{
//			"shaders/phong_lit_vrtx_shader.glsl",
//			"shaders/phong_lit_frag_shader.glsl"
//		}
//	}
//	,{ "phong",
//		{
//			"shaders/phong_lit_vrtx_shader.glsl",
//			"shaders/phong_lit_frag_shader.glsl"
//		}
//	}
//	,{ "phong",
//		{
//			"shaders/phong_lit_vrtx_shader.glsl",
//			"shaders/phong_lit_frag_shader.glsl"
//		}
//	}
//	,{ "phong",
//		{
//			"shaders/phong_lit_vrtx_shader.glsl",
//			"shaders/phong_lit_frag_shader.glsl"
//		}
//	}
//};