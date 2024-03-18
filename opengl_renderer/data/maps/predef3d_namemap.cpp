// libraries
// ---------------------------------------------------------------------------------------
#include "../headers/data/data.h"     
// 

//std::vector<Predef3DNode> PredefNameMaps::predef3d_namemap = {
//	//{"frame",	Predef3D::quad_vrts__pos_tex,		2, std::vector<unsigned int>(2, 2)}
//	Predef3DNode("frame",	Predef3D::quad_vrts__pos_tex,		24,		4, { 2,2 })
//	,Predef3DNode("skybox",	Predef3D::skybox_vrts__pos,			108,	3, { 3 })
//	,Predef3DNode("cube",	Predef3D::cube_vrts__pos_norm_uv,	288,	8, { 3,3,2 })
//	,Predef3DNode("rect",	Predef3D::rectangle__vrts,			8,		2, { 2 })
//};

std::map<std::string, Predef3DNode> PredefNameMaps::predef3d_namemap = {
	{
		"origin"
		,Predef3DNode(Predef3D::origin,					3,		3, { 3 })
	}
	,{
		"frame",
		Predef3DNode(Predef3D::quad_vrts__pos_tex,		24,		4, { 2,2 })
	}
	,{
		"skybox"
		,Predef3DNode(Predef3D::skybox_vrts__pos,		108,	3, { 3 })
	}
	,{
		"cube"
		,Predef3DNode(Predef3D::cube_vrts__pos_norm_uv,	288,	8, { 3,3,2 })
	}
	,{
		"plane"
		,Predef3DNode(Predef3D::rectangle__vrts,		8,		2, { 2 })
	}
};