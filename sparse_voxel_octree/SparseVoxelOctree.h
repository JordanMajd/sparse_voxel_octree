#pragma once

#include <iostream>

class Point
{
public:
	float x;
	float y;
	float z;

	Point(float x, float y, float z) : x(x), y(y), z(z){};
	bool Point::operator==(Point *o)
	{
		return (x == o->x) && (y == o->y) && (z == o->z);
	}
};


typedef struct Voxel
{
	unsigned int data;
	Voxel(unsigned int data): data(data){};
} Voxel;


class OctreeNode
{
	private:
		Point* center;
		float radius;
		Voxel* voxel = nullptr;
		Point* point = nullptr;
		OctreeNode* children[2][2][2] = { 
			{ {nullptr, nullptr}, {nullptr, nullptr} },
			{ {nullptr, nullptr}, {nullptr, nullptr} },
		};

	public:
		OctreeNode(float x, float y, float z, float size, Point* pt = nullptr, Voxel* vox = nullptr);
		void insert(Point* pt, Voxel* vox);
		Voxel* find(Point vec);
		Point* coords();
		// traverse octree and call function
		// bool traverse(callback cb, void *data);
		// delete node
		// void deleteNode ();
		// get voxel at location
		// Voxel get(Vector vec);
		// erase voxel at location
		// void erase(int x, int y, int z);
		// recursively get number of nodes in an octree
		// int size();
		// get child
		// OctreeNode child(int x, int y, int z);

		// I/O
		void writeBinary();
		void readBinary();
};
