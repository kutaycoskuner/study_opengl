// ---------------------------------------------------------------------------------------
// libraries
// ---------------------------------------------------------------------------------------
#include "data.h"     

// ---------------------------------------------------------------------------------------
// data
// ---------------------------------------------------------------------------------------

// ! const olamiyor
std::map<std::string, std::vector<std::string>> PathAfterDirectory::cubemap_texture_paths =
{
	{"skybox01",
		{
		std::string("textures_cubemap/out_skybox1_right.jpg"),
		std::string("textures_cubemap/out_skybox1_left.jpg"),
		std::string("textures_cubemap/out_skybox1_top.jpg"),
		std::string("textures_cubemap/out_skybox1_bottom.jpg"),
		std::string("textures_cubemap/out_skybox1_front.jpg"),
		std::string("textures_cubemap/out_skybox1_back.jpg")
		}
	}
	,{"skybox02",
		{
		std::string("textures_cubemap/out_artistworkshop_2k_right.png"),
		std::string("textures_cubemap/out_artistworkshop_2k_left.png"),
		std::string("textures_cubemap/out_artistworkshop_2k_top.png"),
		std::string("textures_cubemap/out_artistworkshop_2k_bottom.png"),
		std::string("textures_cubemap/out_artistworkshop_2k_front.png"),
		std::string("textures_cubemap/out_artistworkshop_2k_back.png")
		}
	}
	,{"skybox03",
		{
		std::string("yurt/assets/textures_skybox-cubemaps/nebula_2k_xp.jpg"),
		std::string("yurt/assets/textures_skybox-cubemaps/nebula_2k_xn.jpg"),
		std::string("yurt/assets/textures_skybox-cubemaps/nebula_2k_yp.jpg"),
		std::string("yurt/assets/textures_skybox-cubemaps/nebula_2k_yn.jpg"),
		std::string("yurt/assets/textures_skybox-cubemaps/nebula_2k_zp.jpg"),
		std::string("yurt/assets/textures_skybox-cubemaps/nebula_2k_zn.jpg")
		}
	}
	,{"skybox04",
		{
		std::string("yurt/assets/textures_skybox-cubemaps/nebula-blue/nebula-blue_2k_xp.jpg"),
		std::string("yurt/assets/textures_skybox-cubemaps/nebula-blue/nebula-blue_2k_xn.jpg"),
		std::string("yurt/assets/textures_skybox-cubemaps/nebula-blue/nebula-blue_2k_yp.jpg"),
		std::string("yurt/assets/textures_skybox-cubemaps/nebula-blue/nebula-blue_2k_yn.jpg"),
		std::string("yurt/assets/textures_skybox-cubemaps/nebula-blue/nebula-blue_2k_zp.jpg"),
		std::string("yurt/assets/textures_skybox-cubemaps/nebula-blue/nebula-blue_2k_zn.jpg")
		}		
	}
};


std::map<std::string, TexturePaths> PathAfterDirectory::texture_paths =
{
	{"test_2k",
		{
		.color = std::string("textures/test_2k_mid_color.jpg")
		,.specular = std::string("textures/test_2k_specular.jpg")
		,.emission = std::string("textures/test_2k_emission.jpg")
		}
	},
	{"grid_2k_white",
		{
		.color = std::string("textures/grid_2k_16d_white_color.png")
		,.specular = std::string("textures/test_2k_specular.jpg")
	//,.emission = std::string("textures/grid02_16d_emission_2k.png")
	}
},
{"grid_darkgray_2k",
	{
		.color = std::string("yurt/assets/textures_simple/grid-16_darkgray_2k_color.png")
	,.emission = std::string("yurt/assets/textures_simple/color-emission_2k.jpg")
	}
},
{"linegrid01_darkgray_2k",
	{
	    .color = std::string("yurt/assets/textures_simple/linegrid-16_darkgray_2k_color.png")
	,.emission = std::string("yurt/assets/textures_simple/color-emission_2k.jpg")
	}
},
{"linegrid01_white_2k",
	{
		.color = std::string("yurt/assets/textures_simple/linegrid-16_white_2k_color.png")
	//,.normal = std::string("textures/self/normal.png")
	,.specular = std::string("textures/kraftpaper01_2k_roughness.jpg")
	,.emission = std::string("yurt/assets/textures_simple/color-emission_2k.jpg")
	}
},
{"linegrid_2k_darkgray",
	{
	.color = std::string("textures/linegrid_2k_16d_darkgray_color.png")
	,.specular = std::string("textures/kraftpaper01_2k_roughness.jpg")
	,.emission = std::string("textures/test_2k_emission.jpg")
	}
},
{"linegrid_2k_white",
	{
	.color = std::string("textures/linegrid_2k_16d_white_color.png")
	,.specular = std::string("textures/kraftpaper01_2k_roughness.jpg")
	,.emission = std::string("textures/test_2k_emission.jpg")
	}
},
{"out_container2",
	{
	.color = std::string("textures/out_container2_diffuse.png")
	,.specular = std::string("textures/out_container2_specular.png")
	,.emission = std::string("textures/out_container2_emission.jpg")
	}
},
{"out_planks023b",
	{
	.color = std::string("textures/ambientcg/planks023b_2k/Planks023B_2K-JPG_Color.jpg")
	//,.roughness = std::string("textures/ambientcg/planks023b_2k/Planks023B_2K-JPG_Roughness.jpg")
	,.specular = std::string("textures/ambientcg/planks023b_2k/Planks023B_2K-JPG_Roughness.jpg")
	//,.normal 	= std::string("textures/ambientcg/planks023b_2k/Planks023B_2K-JPG_NormalGL.jpg")
	}
},
{"out_planks023a",
	{
	.color = std::string("textures/ambientcg/planks023a_2k/Planks023a_2K-JPG_Color.jpg")
	//,.roughness = std::string("textures/ambientcg/planks023b_2k/Planks023B_2K-JPG_Roughness.jpg")
	,.specular = std::string("textures/ambientcg/planks023a_2k/Planks023a_2K-JPG_Roughness.jpg")
	//,.normal 	= std::string("textures/ambientcg/planks023b_2k/Planks023B_2K-JPG_NormalGL.jpg")
	}
},
{"out_planks023a",
	{
	.color = std::string("textures/ambientcg/planks023a_2k/Planks023A_2K-JPG_Color.jpg")
	//,.roughness = std::string("textures/ambientcg/planks023b_2k/Planks023B_2K-JPG_Roughness.jpg")
	,.specular = std::string("textures/ambientcg/planks023a_2k/Planks023A_2K-JPG_Roughness.jpg")
	//,.normal 	= std::string("textures/ambientcg/planks023b_2k/Planks023B_2K-JPG_NormalGL.jpg")
	}
},
{"out_pavingstones080_2k",
	{
	.color = std::string("textures/ambientcg/pavingstones080_2k/PavingStones080_2K-JPG_Color.jpg")
	//,.roughness = std::string("textures/ambientcg/planks023b_2k/Planks023B_2K-JPG_Roughness.jpg")
	,.specular = std::string("textures/ambientcg/pavingstones080_2k/PavingStones080_2K-JPG_Roughness.jpg")
	//,.normal 	= std::string("textures/ambientcg/planks023b_2k/Planks023B_2K-JPG_NormalGL.jpg")
	}
},
{"out_grass",
	{
	.color = std::string("textures/out_blending_grass.png")
	}
},
{"out_blending_window_blue",
	{
	.color = std::string("textures/out_blending_transparent_window_blue_256.png")
	}
},
{"out_brickwall",
	{
	.color = std::string("textures/learnopengl/out_brickwall_color_1k.jpg")
	,.normal = std::string("textures/learnopengl/out_brickwall_normal_1k.jpg")
	//,.specular = std::string("textures/linegrid_2k_16d_white_color.png")
	//,.emission = std::string("textures/linegrid_2k_16d_white_color.png")
	}
}
,{
"out_bricks",
   {
   .color = std::string("textures/learnopengl/out_bricks2_color_512.jpg")
   ,.normal = std::string("textures/learnopengl/out_bricks2_normal_512.jpg")
   ,.displacement = std::string("textures/learnopengl/out_bricks2_displacement_512.jpg")
	//,.specular = std::string("textures/linegrid_2k_16d_white_color.png")
	//,.emission = std::string("textures/linegrid_2k_16d_white_color.png")
   }
}
,{
"out_wood",
   {
   .color = std::string("textures/learnopengl/out_wood_color_1k.png")
   ,.normal = std::string("textures/learnopengl/out_toy_box_normal_256.png")
   ,.displacement = std::string("textures/learnopengl/out_toy_box_displacement_256.png")
	//,.specular = std::string("textures/linegrid_2k_16d_white_color.png")
	//,.emission = std::string("textures/linegrid_2k_16d_white_color.png")
   }
}
,{
"parallax-test",
{
.color = std::string("textures/learnopengl/out_wood_color_1k.png")
,.normal = std::string("textures/self/parallax-test_normal_512.png")
,.displacement = std::string("textures/self/parallax-test_displacement_512.png")
//,.specular = std::string("textures/linegrid_2k_16d_white_color.png")
//,.emission = std::string("textures/linegrid_2k_16d_white_color.png")
   }
},
{
"gamma-test-rgb",
	{
	.color = std::string("textures/self/gamma_test_rgb_256.png")
    }
},
{
"gamma-test-srgb",
	{
	.color = std::string("textures/self/gamma_test_srgb_256.png")
	}
}


};