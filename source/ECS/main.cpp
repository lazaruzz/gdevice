#pragma once

#include <map>
#include <vector>
#include <assert.h>

// TODO Instead of map, use unordered_map or hashtable.
// TODO namespace gd or gd::scene ?
// TODO rename Component as DataPart, Attribute, Property ?
// TODO Apply logic to components of a node (update function).
namespace gd
{
    typedef unsigned long Node;

    template <typename T>
    std::map<Node, std::vector<T>>& GetComponentsMap()
    {
        static std::map<Node, std::vector<T>> componentsMap;
        return componentsMap;
    }

    template <typename T>
    std::vector<T>& GetComponents(Node node)
    {
        std::map<Node, std::vector<T>>& componentsMap = GetComponentsMap<T>();
        std::vector<T>& components = componentsMap[node];
        return components;
    }

    Node CreateNode()
    {
        static Node nextID = 0;
        return ++nextID;
    }

    template <typename T>
    T& AddComponent(Node node)
    {
        std::vector<T>& components = GetComponents<T>(node);
        T component;
        components.push_back(component);
        return components.back();
    }

	struct Hierarchy
	{
		gd::Node parent;
		std::vector<gd::Node> children;
	};

    Node AddChild(Node node)
    {
        std::vector<Hierarchy>& components = GetComponents<Hierarchy>(node);
        Hierarchy& nodeHierarchy = (components.size() == 0) ? AddComponent<Hierarchy>(node) : components[0];

        Node child = gd::CreateNode();
        Hierarchy& childHierarchy = AddComponent<Hierarchy>(child);

        nodeHierarchy.children.push_back(child);
        childHierarchy.parent = node;

        return child;
    }
};



typedef float vec3[3];

struct Transform
{
    vec3 position;
    vec3 rotation;
    vec3 scale;
};





void main_ECS()
{

    gd::Node node = gd::CreateNode();

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

    gd::Node scene = gd::CreateNode();
    Transform& camera = gd::AddComponent<Transform>(scene);

    assert(gd::GetComponents<Transform>(scene).size() == 1);

    gd::Node heightmap = gd::AddChild(scene);
    Transform& heightmapTransform = gd::AddComponent<Transform>(heightmap);

	std::vector<gd::Hierarchy>& sceneHierarchyPool = gd::GetComponents<gd::Hierarchy>(scene);
    assert(sceneHierarchyPool.size() == 1);
    assert(sceneHierarchyPool[0].children.size() == 1);
    assert(sceneHierarchyPool[0].children[0] == heightmap);

    std::vector<gd::Hierarchy>& heightmapHierarchyPool = gd::GetComponents<gd::Hierarchy>(heightmap);
    assert(heightmapHierarchyPool.size() == 1);
    assert(heightmapHierarchyPool[0].parent = scene);

    
}



void main()
{
	main_ECS();
	printf("hello");
}