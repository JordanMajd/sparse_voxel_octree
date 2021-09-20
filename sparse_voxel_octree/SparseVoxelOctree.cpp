#include "SparseVoxelOctree.h"
#include <cassert>

using namespace std;

OctreeNode::OctreeNode(float x, float y, float z, float size, Point* pt, Voxel* vox)
{
	this->center = new Point(x, y, z);
	radius = size / 2;
	point = pt;
	voxel = vox;
	// cout << "Radius: " << this->radius << " ";
	// cout << " Center: " << this->center->x << "," << this->center->y << "," << this->center->z;
	// if(this->point){
		// cout << " Point: " << this->point->x << "," << this->point->y << "," << this->point->z;
	// }
	// cout << endl;
}

void OctreeNode::insert(Point *pt, Voxel *vox)
{
	// TODO exit if outside bounds

	// make this node a leaf if minimum granularity reached
	if(radius < 1){
		this->voxel = vox;
		this->point = pt;
		return;
	}

	// if leaf node
	if(this->point != nullptr) {
		Voxel* leafVox = this->voxel;
		Point* leafPoint = this->point;
		this->voxel = nullptr;
		this->point = nullptr;
		this->insert(leafPoint, leafVox);
	}

	int xGT = pt->x > center->x;
	int yGT = pt->y > center->y;
	int zGT = pt->z > center->z;

	OctreeNode *child = children[xGT][yGT][zGT];
	if(child){
		child->insert(pt, vox);
	} else {
		// get center of new bounds
		float midX, midY, midZ;
		float rad = radius / 2;
		if (xGT)
		{
			midX = center->x + rad;
		}
		else
		{
			midX = center->x - rad;
		}

		if (yGT)
		{
			midY = center->y + rad;
		}
		else
		{
			midY = center->y - rad;
		}

		if (zGT)
		{
			midZ = center->z + rad;
		}
		else
		{
			midZ = center->z - rad;
		}
		// create leaf node
		children[xGT][yGT][zGT] = new OctreeNode(midX, midY, midZ, radius, pt, vox);
	}

}

Voxel* OctreeNode::find(Point pt)
{
	int xGT = pt.x > center->x;
	int yGT = pt.y > center->y;
	int zGT = pt.z > center->z;

	OctreeNode *child = children[xGT][yGT][zGT];

	// if leaf return voxel
	if(!child){
		// cout << "Center: " << this->center->x << "," << this->center->y << "," << this->center->z << endl;
		return this->voxel;
	}
	return child->find(pt);
}

int main()
{
	cout << "Sparseish Voxel Octree" << endl;

	OctreeNode *tree = new OctreeNode(0, 0, 0, 32);
	Point *pt = new Point(3, 3, 3);
	Voxel *vox = new Voxel(1);

	tree->insert(pt, vox);

	Point *pt2 = new Point(-3, -2, -1);
	Voxel *vox2 = new Voxel(2);
	tree->insert(pt2, vox2);

	Point *pt3 = new Point(-3, -1, -1);
	Voxel *vox3 = new Voxel(3);
	tree->insert(pt3, vox3);


	Voxel *returned = tree->find(*pt);
	if(returned != nullptr){
		cout << "Found pt 1: " << returned->data << endl;
	}

	returned = tree->find(*pt2);
	if(returned != nullptr){
		cout << "Found pt 2: " << returned->data << endl;
	}

	returned = tree->find(*pt3);
	if(returned != nullptr){
		cout << "Found pt 3: " << returned->data << endl;
	}

	cout << sizeof(OctreeNode) << endl; // 48
	cout << sizeof(Point) << endl; // 12
	cout << sizeof(Voxel) << endl; // 4
	return 0;
}
