#pragma once


#include "type/gpu.h"
#include "type/array.h"

#include "__temp/texture.h"
#include "gpu/program.h"
#include "__temp/vertexbuffer.h"
#include "gpu/indexbuffer.h"

#include "gpu/renderer.h"

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

    Child() : parent(NULL) {};
    virtual ~Child() {};
};

struct Transform 
{
    mat3 transform;

    Transform()
	{
		transform.position	= vec3(0);
		transform.rotation	= vec3(0);
		transform.scale		= vec3(1);
    }
    virtual ~Transform() {};
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

    Geometry() : vbo(NULL), ibo(NULL) {}
    virtual ~Geometry() {};
};

typedef int RenderTarget;
class Renderer;
struct Renderable
{
    virtual void Render(Renderer& renderer, RenderTarget& target) = 0;
};


struct Impostor 
{
    vec2			impostorDirection;
	float			impostorDistance;
	Texture<rgba>	impostorTexture; // TODO Updatable
};


////////////////
//
//typedef Cacheable Updatable;
class Renderer;
struct Updatable : Cacheable
{
    virtual void Update(Renderer& renderer) = 0;
};

struct Node
{
	Node() {}
    virtual ~Node() {};
};

