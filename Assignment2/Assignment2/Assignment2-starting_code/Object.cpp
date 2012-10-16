#include "Object.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <glm.hpp>

using namespace std;

//slices = number of subdivisions around the axis
Object::Object() :
    mIsInitialised(false)
{
}

Object::~Object()
{
    if(mIsInitialised) {
        //Delete any initialised stuff
    }
}

bool Object::loadTxtFile(const string &filename)
{
    //Put your loading code here ...
	//Read from file...
	ifstream in(filename);
    if(!in.good()) { return NULL; }

	//Vectors and triangles
	int vectors,triangles;
	in>>vectors>>triangles;

	cout<< "vectors= "<<vectors;
	cout<< "triangles= "<<triangles<<endl;

	vector<glm::vec3> vertices;
	float x,y,z;

	for (int i=0;i<vectors;i++) {
		 in>>x>>y>>z;
  		 vertices.push_back(glm::vec3(x, y, z));
		  			
	cout << vertices[i].x << " " << vertices[i].y << " " << vertices[i].z <<endl;
	}

	cout<< " TRIANGLE"<<endl;
	vector<glm::vec3> index;
	float tx,ty,tz;

	for (int i=0;i<triangles;i++) {
		 in>>tx>>ty>>tz;
 		 index.push_back(glm::vec3(tx, ty, tz));
		  			
	cout << index[i].x << " " << index[i].y << " " << index[i].z <<endl;
	}


    mIsInitialised = true;
    return true;  //Return true if succusfuly loaded
}


void Object::draw()
{
    if(!mIsInitialised) { return; }

    //Put your drawing code here ...


}
