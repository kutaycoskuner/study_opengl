#pragma once
// ---------------------------------------------------------------------------------------
// libraries
// ---------------------------------------------------------------------------------------
#include "../../source/headers/data/path_data.h"

#include <map>
#include <vector>
#include <string>


// ---------------------------------------------------------------------------------------
// data
// ---------------------------------------------------------------------------------------

// this map cannot be const I do not remember exactly why
std::map<std::string, std::vector<std::string>> PathAfterDirectory::cubemap_texture_paths =
{
	{"nebula",
		{
		std::string("yurt/textures_cubemaps/nebula_2k_xp.jpg"),
		std::string("yurt/textures_cubemaps/nebula_2k_xn.jpg"),
		std::string("yurt/textures_cubemaps/nebula_2k_yp.jpg"),
		std::string("yurt/textures_cubemaps/nebula_2k_yn.jpg"),
		std::string("yurt/textures_cubemaps/nebula_2k_zp.jpg"),
		std::string("yurt/textures_cubemaps/nebula_2k_zn.jpg")
		}
	}
	,{"nebula-blue",
		{
		std::string("yurt/textures_cubemaps/nebula-blue/nebula-blue_2k_xp.jpg"),
		std::string("yurt/textures_cubemaps/nebula-blue/nebula-blue_2k_xn.jpg"),
		std::string("yurt/textures_cubemaps/nebula-blue/nebula-blue_2k_yp.jpg"),
		std::string("yurt/textures_cubemaps/nebula-blue/nebula-blue_2k_yn.jpg"),
		std::string("yurt/textures_cubemaps/nebula-blue/nebula-blue_2k_zp.jpg"),
		std::string("yurt/textures_cubemaps/nebula-blue/nebula-blue_2k_zn.jpg")
		}		
	}
};


std::map<std::string, TexturePaths> PathAfterDirectory::texture_paths = {
	{"test_2k",
		{
		.color 			= std::string("textures/blender/test_2k_mid_color.jpg")
		,.specular 		= std::string("textures/blender/test_2k_specular.jpg")
		,.emission 		= std::string("yurt/textures_simple/color-emission_2k.jpg")
		}
	},
	{"parallax-test",
		{
		.color 			= std::string("textures/learnopengl/out_wood_color_1k.png")
		,.normal 		= std::string("yurt/textures_simple/parallax-test_normal_512.png")
		,.displacement 	= std::string("yurt/textures_simple/parallax-test_displacement_512.png")
		}
	},
	{"gamma-test-srgb",
		{
		.color 			= std::string("yurt/textures_simple/gamma-test_srgb_256.png")
		}
	},
	{"grid_white_2k",
		{
		.color = std::string("yurt/textures_simple/grid-16_darkgray_2k_color.png")
		,.emission = std::string("yurt/textures_simple/color-emission_2k.jpg")
		}
	},
	{"grid_darkgray_2k",
		{
		.color = std::string("yurt/textures_simple/grid-16_darkgray_2k_color.png")
		,.emission = std::string("yurt/textures_simple/color-emission_2k.jpg")
		}
	},
	{"linegrid_white_2k",
		{
		.color = std::string("yurt/textures_simple/linegrid-16_white_2k_color.png")
		,.emission = std::string("yurt/textures_simple/color-emission_2k.jpg")
		}
	},
	{"linegrid_darkgray_2k",
		{
		.color = std::string("yurt/textures_simple/linegrid-16_darkgray_2k_color.png")
		,.emission = std::string("yurt/textures_simple/color-emission_2k.jpg")
		}
	},
	{"out_container",
		{
		.color = std::string("textures/learnopengl/out_container_diffuse.png")
		,.specular = std::string("textures/learnopengl/out_container_specular.png")
		,.emission = std::string("yurt/textures_simple/color-emission_2k.jpg")
		}
	},
	{"out_planks023b",
		{
		.color = std::string("textures/ambientcg/planks023b_2k/Planks023B_2K-JPG_Color.jpg")
		,.specular = std::string("textures/ambientcg/planks023b_2k/Planks023B_2K-JPG_Roughness.jpg")
		}
	},
	{"out_planks023a",
		{
		.color = std::string("textures/ambientcg/planks023a_2k/Planks023A_2K-JPG_Color.jpg")
		,.specular = std::string("textures/ambientcg/planks023a_2k/Planks023A_2K-JPG_Roughness.jpg")
		}
	},
	{"out_pavingstones080_2k",
		{
		.color = std::string("textures/ambientcg/pavingstones080_2k/PavingStones080_2K-JPG_Color.jpg")
		,.specular = std::string("textures/ambientcg/pavingstones080_2k/PavingStones080_2K-JPG_Roughness.jpg")
		}
	},
	{"out_grass",
		{
		.color = std::string("textures/learnopengl/out_blending_grass.png")
		}
	},
	{"out_blending_window_blue",
		{
		.color = std::string("textures/learnopengl/out_blending_transparent_window_blue_256.png")
		}
	},
	{"out_brickwall",
		{
		.color = std::string("textures/learnopengl/out_brickwall_color_1k.jpg")
		,.normal = std::string("textures/learnopengl/out_brickwall_normal_1k.jpg")
		//,.specular = std::string("textures/linegrid_2k_16d_white_color.png")
		//,.emission = std::string("textures/linegrid_2k_16d_white_color.png")
		}
	},
	{"out_bricks",
		{
		.color = std::string("textures/learnopengl/out_bricks2_color_512.jpg")
		,.normal = std::string("textures/learnopengl/out_bricks2_normal_512.jpg")
		,.displacement = std::string("textures/learnopengl/out_bricks2_displacement_512.jpg")
		//,.specular = std::string("textures/linegrid_2k_16d_white_color.png")
		//,.emission = std::string("textures/linegrid_2k_16d_white_color.png")
		}
	},
	{"out_wood",
		{
		.color = std::string("textures/learnopengl/out_wood_color_1k.png")
		,.normal = std::string("textures/learnopengl/out_toy_box_normal_256.png")
		,.displacement = std::string("textures/learnopengl/out_toy_box_displacement_256.png")
		//,.specular = std::string("textures/linegrid_2k_16d_white_color.png")
		//,.emission = std::string("textures/linegrid_2k_16d_white_color.png")
		}
	}
};