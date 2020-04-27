#ifndef CG1RAYTRACER_LOADERS_OBJ_HEADER
#define CG1RAYTRACER_LOADERS_OBJ_HEADER

#include <string>
#include <map>
namespace rt {
class Group;
class Material;

typedef std::map<std::string, Material*> MatLib;

void loadOBJ(Group* dest, const std::string& path, const std::string& filename, MatLib* inmats=nullptr);
void loadOBJMat(MatLib* dest, const std::string& path, const std::string& filename);

}

#endif