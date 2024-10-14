// libraries
// ---------------------------------------------------------------------------------------
#include "data.h"     
// 

const std::vector<ShaderPaths> PathAfterDirectory::shader_paths =
{
	{
		std::string("1.0.3d_vrtx_shader.glsl"),
		std::string("1.0.3d_frag_shader.glsl")
	}
	,{
		std::string("1.1.axis-x_vrtx_shader.glsl"),
		std::string("1.1.axis-x_frag_shader.glsl")
	}
	,{
		std::string("1.1.axis-z_vrtx_shader.glsl"),
		std::string("1.1.axis-z_frag_shader.glsl")
	}
	,{
		std::string("1.2.diffuse_vrtx_shader.glsl"),
		std::string("1.2.diffuse_frag_shader.glsl")
	}
	,{
		std::string("1.3.green_vrtx_shader.glsl"),
		std::string("1.3.green_frag_shader.glsl")
	}
	,{
		std::string("1.4.pink_vrtx_shader.glsl"),
		std::string("1.4.pink_frag_shader.glsl")
	}
	,{
		std::string("2.0.phong_lit_vrtx_shader.glsl"),
		std::string("2.0.phong_lit_frag_shader.glsl")
	}
	,{
		std::string("2.1.lightmap_lit_vrtx_shader.glsl"),
		std::string("2.1.lightmap_lit_frag_shader.glsl")
	}
	,{
		std::string("2.2.lightcaster-directional_lit_vrtx_shader.glsl"),
		std::string("2.2.lightcaster-directional_lit_frag_shader.glsl")
	}
	,{
		std::string("2.2.lightcaster-point_lit_vrtx_shader.glsl"),
		std::string("2.2.lightcaster-point_lit_frag_shader.glsl")
	}
	,{
		std::string("2.2.lightcaster-spot_lit_vrtx_shader.glsl"),
		std::string("2.2.lightcaster-spot_lit_frag_shader.glsl")
	}
	,{
		std::string("2.3.multiplelights_lit_vrtx_shader.glsl"),
		std::string("2.3.multiplelights_lit_frag_shader.glsl")
	}
	,{
		std::string("3.0.depthtesting_lit_vrtx_shader.glsl"),
		std::string("3.0.depthtesting_lit_frag_shader.glsl")
	}
	,{
		std::string("3.1.stenciltesting_vrtx_shader.glsl"),
		std::string("3.1.stenciltesting_frag_shader.glsl")
	}
	,{
		std::string("3.1.stenciltesting02_vrtx_shader.glsl"),
		std::string("3.1.stenciltesting02_frag_shader.glsl")
	}
	,{
		std::string("3.2.blending_vrtx_shader.glsl"),
		std::string("3.2.blending_frag_shader.glsl")
	}
	,{
		std::string("3.4.framebuffer_vrtx_shader.glsl"),
		std::string("3.4.framebuffer_frag_shader.glsl")
	}
	,{
		std::string("3.5.cubemap_vrtx_shader.glsl"),
		std::string("3.5.cubemap_frag_shader.glsl")
	}
	,{
		std::string("3.6.cubemaplit_vrtx_shader.glsl"),
		std::string("3.6.cubemaplit_frag_shader.glsl")
	}
	,{
		std::string("3.8.advglsl-red_vrtx_shader.glsl"),
		std::string("3.8.advglsl-red_frag_shader.glsl")
	}
	,{
		std::string("3.8.advglsl-green_vrtx_shader.glsl"),
		std::string("3.8.advglsl-green_frag_shader.glsl")
	}
	,{
		std::string("3.8.advglsl-blue_vrtx_shader.glsl"),
		std::string("3.8.advglsl-blue_frag_shader.glsl")
	}
	,{
		std::string("3.8.advglsl-yellow_vrtx_shader.glsl"),
		std::string("3.8.advglsl-yellow_frag_shader.glsl")
	}
	,{
		std::string("3.9.axes_vrtx_shader.glsl")
		, std::string("3.9.axes_frag_shader.glsl")
		, std::string("3.9.axes_geo_shader.glsl")
	}
	,{
		std::string("3.9.explode_vrtx_shader.glsl")
		, std::string("3.9.explode_frag_shader.glsl")
		, std::string("3.9.explode_geo_shader.glsl")
	}
	,{
		std::string("3.9.geo_vrtx_shader.glsl")
		, std::string("3.9.geo_frag_shader.glsl")
		, std::string("3.9.geo_geo_shader.glsl")
	}
	,{
		std::string("3.9.normal_vrtx_shader.glsl")
		, std::string("3.9.normal_frag_shader.glsl")
		, std::string("3.9.normal_geo_shader.glsl")
	}
	,{
		std::string("3.10.instance_vrtx_shader.glsl")
		, std::string("3.10.instance_frag_shader.glsl")
	}
	,{
		std::string("3.10.instance02_vrtx_shader.glsl")
		, std::string("3.10.instance02_frag_shader.glsl")
	}
	,{
		std::string("4.1.blinnphong_vrtx_shader.glsl")
		, std::string("4.1.blinnphong_frag_shader.glsl")
	}
	,{
		std::string("4.1.blinnphong2_vrtx_shader.glsl")
		, std::string("4.1.blinnphong2_frag_shader.glsl")
	}
	,{
		std::string("4.2.gamma_vrtx_shader.glsl")
		, std::string("4.2.gamma_frag_shader.glsl")
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