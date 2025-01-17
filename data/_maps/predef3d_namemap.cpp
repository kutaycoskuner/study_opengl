// libraries
// ---------------------------------------------------------------------------------------
#include "data.h"     
// 

//std::vector<Predef3DNode> PredefNameMaps::predef3d_namemap = {
//	//{"frame",	VertexData::quad_vrts__pos_tex,		2, std::vector<unsigned int>(2, 2)}
//	Predef3DNode("frame",	VertexData::quad_vrts__pos_tex,		24,		4, { 2,2 })
//	,Predef3DNode("skybox",	VertexData::skybox_vrts__pos,			108,	3, { 3 })
//	,Predef3DNode("cube",	VertexData::cube_vrts__pos_norm_uv,	288,	8, { 3,3,2 })
//	,Predef3DNode("rect",	VertexData::rectangle__vrts,			8,		2, { 2 })
//};

std::map<std::string, Predef3DNode> PredefNameMaps::predef3d_namemap = {
	{
		"origin"
		,Predef3DNode(VertexData::origin,					3,		3, { 3 })
	}
	,{
		"frame",
		Predef3DNode(VertexData::quad_vrts__pos_tex,		24,		4, { 2,2 })
	}
	,{
		"skybox"
		,Predef3DNode(VertexData::skybox_vrts__pos,			108,	3, { 3 })
	}
	,{
		"cube"
		,Predef3DNode(VertexData::cube_vrts__pos_norm_uv,	288,	8, { 3, 3, 2 })
	}
	,{
		"icosphere02"
		,Predef3DNode(VertexData::icosphere02__pos,			720,	3, { 3 })
	}
	,{
		"icosahedron"
		,Predef3DNode(VertexData::icosahedron__pos,			180,	3, { 3 })
	}
	,{
		"plane01"
		,Predef3DNode(VertexData::plane_vrts__pos_norm_uv,	 48,		8, { 3, 3, 2 })
	}
	,{
		"plane"
		,Predef3DNode(VertexData::rectangle__vrts,			8,		2, { 2 })
	}
	,{
		"plane2"
		,Predef3DNode(VertexData::quad_vrts__pos_norm_tex,	 42,	7, { 2,3,2 })
	}
	,{
		"small_plane"
		,Predef3DNode(VertexData::quad_vrts__pos_col,		30,		5, { 2, 3 })
	}
};