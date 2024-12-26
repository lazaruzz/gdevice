#pragma once

#include <unordered_map>
#include <vector>
#include <assert.h>

// TODO gd::Entity and gd::Node (which is ECS Entity with Inheritance).
// TODO rename Component as DataPart, Attribute, Property ?
// TODO Apply logic to components of a node (update function).
namespace gd
{
    typedef unsigned long Node2;

    template <typename T>
    std::tr1::unordered_map<Node2, std::vector<T>>& GetComponentsMap()
    {
        static std::tr1::unordered_map<Node2, std::vector<T>> componentsMap;
        return componentsMap;
    }

    template <typename T>
    std::vector<T>& GetComponents(Node2 node)
    {
        std::tr1::unordered_map<Node2, std::vector<T>>& componentsMap = GetComponentsMap<T>();
        std::vector<T>& components = componentsMap[node];
        return components;
    }

    Node2 CreateNode()
    {
        static Node2 nextID = 0;
        return ++nextID;
    }

    template <typename T>
    T& AddComponent(Node2 node)
    {
        std::vector<T>& components = GetComponents<T>(node);
        T component;
        components.push_back(component);
        return components.back();
    }

	struct Hierarchy
	{
		gd::Node2 parent;
		std::vector<gd::Node2> children;
	};
/*
    Node2 AddChild(Node2 node)
    {
    std::vector<gd::Hierarchy>& components = GetComponents<gd::Hierarchy>(node);
        gd::Hierarchy& nodeHierarchy = (components.size() == 0) ? AddComponent<gd::Hierarchy>(node) : components[0];

        Node2 child = gd::CreateNode();
        gd::Hierarchy& childHierarchy = AddComponent<gd::Hierarchy>(child);

        nodeHierarchy.children.push_back(child);
        childHierarchy.parent = node;

        return child;
    }
    */
};



/*
typedef float vec3[3];

struct Transform
{
    vec3 position;
    vec3 rotation;
    vec3 scale;
};

void main_ECS()
{



    gd::Node2 node = gd::CreateNode();

    //
    // Assert AddComponent creates a component for the node and can be later on retrieved.
    //

    std::vector<Transform>& components0 = gd::GetComponents<Transform>(node);
    assert(components0.size() == 0);

    Transform& t0 = gd::AddComponent<Transform>(node);
    assert(components0.size() == 1);

    t0.position[0] = 123;

    std::vector<Transform>& components1 = gd::GetComponents<Transform>(node);
    assert(components1.size() == 1);
    assert(&components0 == &components1);

    Transform& t1 = components1.back();

    assert(t1.position[0] = 123);
    assert(&t0 == &t1);

    //
    // Scene example with hierarchy
    //

    gd::Node2 scene = gd::CreateNode();
    Transform& camera = gd::AddComponent<Transform>(scene);

    assert(gd::GetComponents<Transform>(scene).size() == 1);

    gd::Node2 heightmap = gd::AddChild(scene);
    Transform& heightmapTransform = gd::AddComponent<Transform>(heightmap);

	std::vector<gd::Hierarchy>& sceneHierarchyPool = gd::GetComponents<gd::Hierarchy>(scene);
    assert(sceneHierarchyPool.size() == 1);
    assert(sceneHierarchyPool[0].children.size() == 1);
    assert(sceneHierarchyPool[0].children[0] == heightmap);

    std::vector<gd::Hierarchy>& heightmapHierarchyPool = gd::GetComponents<gd::Hierarchy>(heightmap);
    assert(heightmapHierarchyPool.size() == 1);
    assert(heightmapHierarchyPool[0].parent = scene);

    
}
*/
