// ---------------------------------------------------------------------------------------
// libraries
// ---------------------------------------------------------------------------------------
#include "../headers/data/data.h"     

// ---------------------------------------------------------------------------------------
// data
// ---------------------------------------------------------------------------------------

// ! const olamiyor
std::map<std::string, std::vector<std::string>> RelativePaths::cubemap_texture_paths =
{
	{"skybox01",
		{
		"data/textures_cubemap/out_skybox1_right.jpg",
		"data/textures_cubemap/out_skybox1_left.jpg",
		"data/textures_cubemap/out_skybox1_top.jpg",
		"data/textures_cubemap/out_skybox1_bottom.jpg",
		"data/textures_cubemap/out_skybox1_front.jpg",
		"data/textures_cubemap/out_skybox1_back.jpg"
		}
	}
	,{"skybox02",
		{
		"data/textures_cubemap/out_artistworkshop_2k_right.png",
		"data/textures_cubemap/out_artistworkshop_2k_left.png",
		"data/textures_cubemap/out_artistworkshop_2k_top.png",
		"data/textures_cubemap/out_artistworkshop_2k_bottom.png",
		"data/textures_cubemap/out_artistworkshop_2k_front.png",
		"data/textures_cubemap/out_artistworkshop_2k_back.png"
		}
	}
	,{"skybox03",
		{
		"data/textures_cubemap/nebula_2k.xp.jpg",
		"data/textures_cubemap/nebula_2k.xn.jpg",
		"data/textures_cubemap/nebula_2k.yp.jpg",
		"data/textures_cubemap/nebula_2k.yn.jpg",
		"data/textures_cubemap/nebula_2k.zp.jpg",
		"data/textures_cubemap/nebula_2k.zn.jpg"
		}
	}
	,{"skybox04",
		{
		"data/textures_cubemap/nebula01_2k.xp.jpg",
		"data/textures_cubemap/nebula01_2k.xn.jpg",
		"data/textures_cubemap/nebula01_2k.yp.jpg",
		"data/textures_cubemap/nebula01_2k.yn.jpg",
		"data/textures_cubemap/nebula01_2k.zp.jpg",
		"data/textures_cubemap/nebula01_2k.zn.jpg"
		}
	}
};


std::map<std::string, TexturePaths> RelativePaths::texture_paths =
{
	{"test_2k",
		{
		.color = "data/textures/test_2k_mid_color.jpg"
		,.specular = "data/textures/test_2k_specular.jpg"
		,.emission = "data/textures/test_2k_emission.jpg"
		}
	},
	{"grid_2k_white",
		{
		.color = "data/textures/grid_2k_16d_white_color.png"
		,.specular = "data/textures/test_2k_specular.jpg"
	//,.emission = "data/textures/grid02_16d_emission_2k.png"
	}
},
{"linegrid_2k_darkgray",
	{
	.color = "data/textures/linegrid_2k_16d_darkgray_color.png"
	,.specular = "data/textures/kraftpaper01_2k_roughness.jpg"
	,.emission = "data/textures/test_2k_emission.jpg"
	}
},
{"out_container2",
	{
	.color = "data/textures/out_container2_diffuse.png"
	,.specular = "data/textures/out_container2_specular.png"
	,.emission = "data/textures/out_container2_emission.jpg"
	}
},
{"out_planks023b",
	{
	.color 		= "data/textures/ambientcg/planks023b_2k/Planks023B_2K-JPG_Color.jpg"
	//,.roughness = "data/textures/ambientcg/planks023b_2k/Planks023B_2K-JPG_Roughness.jpg"
	,.normal 	= "data/textures/ambientcg/planks023b_2k/Planks023B_2K-JPG_NormalGL.jpg"
	}
},
{"out_grass",
	{
	.color = "data/textures/out_blending_grass.png"
	}
},
{"out_blending_window_blue",
	{
	.color = "data/textures/out_blending_transparent_window_blue_256.png"
	}
}
};