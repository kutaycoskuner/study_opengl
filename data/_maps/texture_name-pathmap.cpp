// ---------------------------------------------------------------------------------------
// libraries
// ---------------------------------------------------------------------------------------
#include "data.h"     

// ---------------------------------------------------------------------------------------
// data
// ---------------------------------------------------------------------------------------

// ! const olamiyor
std::map<std::string, std::vector<std::string>> FullPaths::cubemap_texture_paths =
{
	{"skybox01",
		{
		DATA_DIR + std::string("textures_cubemap/out_skybox1_right.jpg"),
		DATA_DIR + std::string("textures_cubemap/out_skybox1_left.jpg"),
		DATA_DIR + std::string("textures_cubemap/out_skybox1_top.jpg"),
		DATA_DIR + std::string("textures_cubemap/out_skybox1_bottom.jpg"),
		DATA_DIR + std::string("textures_cubemap/out_skybox1_front.jpg"),
		DATA_DIR + std::string("textures_cubemap/out_skybox1_back.jpg")
		}
	}
	,{"skybox02",
		{
		DATA_DIR + std::string("textures_cubemap/out_artistworkshop_2k_right.png"),
		DATA_DIR + std::string("textures_cubemap/out_artistworkshop_2k_left.png"),
		DATA_DIR + std::string("textures_cubemap/out_artistworkshop_2k_top.png"),
		DATA_DIR + std::string("textures_cubemap/out_artistworkshop_2k_bottom.png"),
		DATA_DIR + std::string("textures_cubemap/out_artistworkshop_2k_front.png"),
		DATA_DIR + std::string("textures_cubemap/out_artistworkshop_2k_back.png")
		}
	}
	,{"skybox03",
		{
		DATA_DIR + std::string("textures_cubemap/nebula_2k.xp.jpg"),
		DATA_DIR + std::string("textures_cubemap/nebula_2k.xn.jpg"),
		DATA_DIR + std::string("textures_cubemap/nebula_2k.yp.jpg"),
		DATA_DIR + std::string("textures_cubemap/nebula_2k.yn.jpg"),
		DATA_DIR + std::string("textures_cubemap/nebula_2k.zp.jpg"),
		DATA_DIR + std::string("textures_cubemap/nebula_2k.zn.jpg")
		}
	}
	,{"skybox04",
		{
		DATA_DIR + std::string("textures_cubemap/nebula01_2k.xp.jpg"),
		DATA_DIR + std::string("textures_cubemap/nebula01_2k.xn.jpg"),
		DATA_DIR + std::string("textures_cubemap/nebula01_2k.yp.jpg"),
		DATA_DIR + std::string("textures_cubemap/nebula01_2k.yn.jpg"),
		DATA_DIR + std::string("textures_cubemap/nebula01_2k.zp.jpg"),
		DATA_DIR + std::string("textures_cubemap/nebula01_2k.zn.jpg")
		}
	}
};


std::map<std::string, TexturePaths> FullPaths::texture_paths =
{
	{"test_2k",
		{
		.color = DATA_DIR + std::string("textures/test_2k_mid_color.jpg")
		,.specular = DATA_DIR + std::string("textures/test_2k_specular.jpg")
		,.emission = DATA_DIR + std::string("textures/test_2k_emission.jpg")
		}
	},
	{"grid_2k_white",
		{
		.color = DATA_DIR + std::string("textures/grid_2k_16d_white_color.png")
		,.specular = DATA_DIR + std::string("textures/test_2k_specular.jpg")
	//,.emission = DATA_DIR + std::string("textures/grid02_16d_emission_2k.png")
	}
},
{"linegrid_2k_darkgray",
	{
	.color = DATA_DIR + std::string("textures/linegrid_2k_16d_darkgray_color.png")
	,.specular = DATA_DIR + std::string("textures/kraftpaper01_2k_roughness.jpg")
	,.emission = DATA_DIR + std::string("textures/test_2k_emission.jpg")
	}
},
{"out_container2",
	{
	.color = DATA_DIR + std::string("textures/out_container2_diffuse.png")
	,.specular = DATA_DIR + std::string("textures/out_container2_specular.png")
	,.emission = DATA_DIR + std::string("textures/out_container2_emission.jpg")
	}
},
{"out_planks023b",
	{
	.color 		= DATA_DIR + std::string("textures/ambientcg/planks023b_2k/Planks023B_2K-JPG_Color.jpg")
	//,.roughness = DATA_DIR + std::string("textures/ambientcg/planks023b_2k/Planks023B_2K-JPG_Roughness.jpg")
	,.specular  = DATA_DIR + std::string("textures/ambientcg/planks023b_2k/Planks023B_2K-JPG_Specular.jpg")
	//,.normal 	= DATA_DIR + std::string("textures/ambientcg/planks023b_2k/Planks023B_2K-JPG_NormalGL.jpg")
	}
},
{"out_pavingstones080_2k",
	{
	.color = DATA_DIR + std::string("textures/ambientcg/pavingstones080_2k/PavingStones080_2K-JPG_Color.jpg")
	//,.roughness = DATA_DIR + std::string("textures/ambientcg/planks023b_2k/Planks023B_2K-JPG_Roughness.jpg")
	,.specular = DATA_DIR + std::string("textures/ambientcg/pavingstones080_2k/PavingStones080_2K-JPG_Roughness.jpg")
	//,.normal 	= DATA_DIR + std::string("textures/ambientcg/planks023b_2k/Planks023B_2K-JPG_NormalGL.jpg")
	}
},
{"out_grass",
	{
	.color = DATA_DIR + std::string("textures/out_blending_grass.png")
	}
},
{"out_blending_window_blue",
	{
	.color = DATA_DIR + std::string("textures/out_blending_transparent_window_blue_256.png")
	}
}
};