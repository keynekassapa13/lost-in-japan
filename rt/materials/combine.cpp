#include <rt/materials/combine.h>
#include <core/color.h>
#include <rt/materials/material.h>

namespace rt {

CombineMaterial::CombineMaterial()
{
}

void CombineMaterial::add(Material* m, float w) {
    if (m->useSampling() == SAMPLING_ALL) {
      sample_materials.push_back(std::make_pair(m, w));
	} else {
		  no_sample_materials.push_back(std::make_pair(m, w));
	}
}

RGBColor CombineMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    RGBColor clr = RGBColor::rep(0.0f);
    for (auto& m: no_sample_materials) {
      if (m.first->useSampling() == Material::Sampling::SAMPLING_NOT_NEEDED) {
        clr = clr + m.second 
          * m.first->getReflectance(texPoint, normal, -outDir, inDir);
      }
    }
    return clr;
}

RGBColor CombineMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    RGBColor clr = RGBColor::rep(0.0f);
    for (auto& m: sample_materials) {
      clr = clr + m.second 
        * m.first->getEmission(texPoint, normal, outDir);
    }
    for (auto& m: no_sample_materials) {
      clr = clr + m.second 
        * m.first->getEmission(texPoint, normal, outDir);
    }
    return clr;
}

Material::SampleReflectance CombineMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    SampleReflectance sample;

    if (sample_materials.size() != 0) {
      int random = rand() % sample_materials.size();
      sample = sample_materials[random].first->getSampleReflectance(texPoint, normal, outDir);
      sample.reflectance = sample.reflectance * sample_materials[random].second;
    } else {
      sample.direction = normal;
      sample.reflectance = RGBColor::rep(0.0f);
    }
    return sample;
}

Material::Sampling CombineMaterial::useSampling() const {
    if(no_sample_materials.size() == 0 && sample_materials.size() == 0) 
      {return Material::Sampling::SAMPLING_NOT_NEEDED;}
    return Material::Sampling::SAMPLING_SECONDARY;
}

}