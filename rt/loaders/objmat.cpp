#include <rt/loaders/obj.h>
#include <fstream>
#include <rt/materials/phong.h>
#include <rt/materials/lambertian.h>
#include <rt/materials/combine.h>
#include <iostream>
#include <rt/textures/constant.h>
#include <rt/textures/imagetex.h>
#include <core/color.h>
#include <cstring>
#include <core/assert.h>

namespace rt {

namespace {

    class MaterialInfo {
    public:
        std::string name;
        float specularExp;
        MaterialInfo() : diffuse_(nullptr), ambient_(nullptr), specular_(nullptr), specularExp(1.0f) {}
        Texture* diffuse() { return diffuse_; }
        Texture* ambient() { return ambient_; }
        Texture* specular() { return specular_; }
        void diffuse(Texture* newtex) { delete diffuse_; diffuse_ = newtex; }
        void ambient(Texture* newtex) { delete ambient_; ambient_ = newtex; }
        void specular(Texture* newtex) { delete specular_; specular_ = newtex; }
        void drop() { name=""; specularExp=1.0f; diffuse_ = nullptr; ambient_ = nullptr; specular_ = nullptr; }
    private:
        Texture* diffuse_;
        Texture* ambient_;
        Texture* specular_;
    };

    void skipWS(const char * &aStr)
    {
        while(isspace(*aStr))
            aStr++;
    }

    std::string endSpaceTrimmed(const char* _str)
    {
        size_t len = std::strlen(_str);
        const char *firstChar = _str;
        const char *lastChar = firstChar + len - 1;
        while(lastChar >= firstChar && isspace(*lastChar))
            lastChar--;

        return std::string(firstChar, lastChar + 1);
    }

    void matCreate(MatLib* dest, MaterialInfo& matinfo) {
        if (matinfo.name != "") {
            std::cerr << "creating material " << matinfo.name << "\n";
            PhongMaterial* phong = nullptr;
            LambertianMaterial* lambertian = nullptr;
            Material* finalmat;
            if (matinfo.specular())
                finalmat = phong = new PhongMaterial(matinfo.specular(), matinfo.specularExp);
            if (matinfo.diffuse())
                finalmat = lambertian = new LambertianMaterial(matinfo.ambient(), matinfo.diffuse());
            if (phong && lambertian) {
                CombineMaterial* combine = new CombineMaterial();
                combine->add(phong,1.0f);
                combine->add(lambertian,1.0f);
                finalmat = combine;
            }
            dest->insert(make_pair(matinfo.name, finalmat));
        }
        matinfo.drop();
    }
}


void loadOBJMat(MatLib* dest, const std::string& path, const std::string& filename) {
    std::string fullname = path + filename;
    std::ifstream matInput(fullname.c_str(), std::ios_base::in);
    std::string buf;
    MaterialInfo material;


    if(matInput.fail()) {
        std::cerr << "Failed to open file " << fullname << "\n";
        return;
    }

    size_t curLine = 0;

    while(!matInput.eof())
    {
        std::getline(matInput, buf);
        curLine++;
        const char* cmd = buf.c_str();
        skipWS(cmd);

        if(std::strncmp(cmd, "newmtl", 6) == 0)
        {
            matCreate(dest, material); //create the previous material (if it exists) and clear the material info
            cmd += 6;

            skipWS(cmd);
            material.name = endSpaceTrimmed(cmd);
        }
        else if(
            std::strncmp(cmd, "Kd", 2) == 0 || std::strncmp(cmd, "Ks", 2) == 0 
            || std::strncmp(cmd, "Ka", 2) == 0)
        {
            char coeffType = *(cmd + 1);

            RGBColor color;
            cmd += 2;

            char *newCmdString;
            for(int i = 0; i < 3; i++)
            {
                skipWS(cmd);
                ((float*)&color)[i] = (float)strtod(cmd, &newCmdString);
                if(newCmdString == cmd) goto parse_err_found;
                cmd = newCmdString; 
            }


            switch (coeffType)
            {
            case 'd': 
                material.diffuse(new ConstantTexture(color)); break;
            case 'a': 
                material.ambient(new ConstantTexture(color)); break;
            case 's': 
                material.specular(new ConstantTexture(color)); break;
            }
        }
        else if(std::strncmp(cmd,  "Ns", 2) == 0) 
        {
            cmd += 2;

            char *newCmdString;
            skipWS(cmd);
            float coeff = (float)strtod(cmd, &newCmdString);
            if(newCmdString == cmd) goto parse_err_found;
            cmd = newCmdString; 
            material.specularExp = coeff;
        }
        else if(
            std::strncmp(cmd, "map_Kd", 6) == 0 || std::strncmp(cmd, "map_Ks", 6) == 0 
            || std::strncmp(cmd, "map_Ka", 6) == 0) {
                char coeffType = *(cmd + 5);
                cmd += 6;
                skipWS(cmd);
                std::string texname = endSpaceTrimmed(cmd);
                ImageTexture* tex = new ImageTexture(path + texname);
                switch (coeffType)
                {
                case 'd': 
                    material.diffuse(tex); break;
                case 'a': 
                    material.ambient(tex); break;
                case 's': 
                    material.specular(tex); break;
                }
        }

        continue;
parse_err_found:
        std::cerr << "Error at line " << curLine << "in " << fullname <<std::endl;
    }
    matCreate(dest, material);
}

}
