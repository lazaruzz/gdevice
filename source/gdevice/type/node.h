#pragma once


#include "type/gpu.h"
#include "type/array.h"

#include "__temp/texture.h"
#include "gpu/program.h"
#include "__temp/vertexbuffer.h"
#include "gpu/indexbuffer.h"

struct Node;
struct Child;

struct Parent 
{
	Array<Node*> children; // TODO use Child* instead of Node*
};

struct Child 
{
// TODO Parent* parent;
    Node* parent; // TODO use Parent* instead of Node*
};
/*
struct Hierarchy 
{
    Node* parent;
	Array<Node*> children;
};
*/
struct Transform 
{
    mat3 transform;
};

struct Cullable
{
    vec4 AABB;
};

struct Geometry 
{
	// TODO Material*		material; // TerrainMaterial by default
    // TODO Abstract vertex attribute => so to allow other configurations.
    // TODO VAO => stores the state of vertex attributes for performance.
	VertexBuffer*	vbo;
	IndexBuffer*	ibo;
};

struct Impostor 
{
    vec2			impostorDirection;
	float			impostorDistance;
	Texture<rgba>	impostorTexture;	
};

struct TileData
{
    vec4 tileID;
};


////////////////
//

struct _NodeBase
{
virtual ~_NodeBase() {};
};

typedef Cacheable Invalidable;

struct _Heightmap : _NodeBase, Invalidable, Parent, Child, Transform, Cullable, Impostor
{

};

struct _Clipmap : _NodeBase, Invalidable, Parent, Child, Transform, Cullable, Impostor
{
    
};

struct _Tile : _NodeBase, Invalidable, Child, Transform,  TileData, Geometry, Cullable, Impostor
{

};

struct Node : _NodeBase, Invalidable, Parent, Child, Transform, TileData, Geometry, Cullable, Impostor
{
	Node()
	{
		transform.position	= vec3(0);
		transform.rotation	= vec3(0);
		transform.scale		= vec3(1);

		this->vbo		= NULL;
		this->ibo		= NULL;
		this->parent	= NULL;
	}

};