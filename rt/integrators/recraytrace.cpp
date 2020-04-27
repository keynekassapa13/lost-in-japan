#include <rt/integrators/recraytrace.h>
#include <rt/intersection.h>
#include <rt/world.h>
#include <rt/solids/solid.h>
#include <rt/lights/light.h>
#include <rt/materials/material.h>
#include <core/float4.h>
#include <rt/coordmappers/coordmapper.h>

namespace rt {
	#define MAX_DEPTH 6

	RGBColor RecursiveRayTracingIntegrator::getRadiance(const Ray& ray) const {
		return recRadiance(ray, 0);
	}

	RGBColor RecursiveRayTracingIntegrator::recRadiance(const Ray& ray, int depth) const {
		RGBColor clr = RGBColor(0, 0, 0);
		if (depth >= MAX_DEPTH) {return clr;}

		Intersection hit_intersection = this->world->scene->intersect(ray, FLT_MAX);
		if (hit_intersection) {
			float att;
			Vector hn = hit_intersection.normal().normalize();
			Point hp = hit_intersection.hitPoint();
			Vector out_dir = ray.d.normalize();

			// Texture
			auto tex = hit_intersection.solid->texMapper;
			if (tex == nullptr) {tex = tex_nullptr;}
			Point tex_p = tex->getCoords(hit_intersection);

            clr = clr + hit_intersection.solid->material->getEmission(tex_p, hn, -out_dir);;
			
			if (hit_intersection.solid->material->useSampling() == Material::Sampling::SAMPLING_NOT_NEEDED) {
				// SAMPLING_NOT_NEEDED
				for (auto light: this->world->light) {
					LightHit lh = light->getLightHit(hp);
					Vector in_dir = lh.direction.normalize();
					Intersection sh_intersect = this->world->scene->intersect(
						Ray(hp + epsilon * in_dir, in_dir), 
						lh.distance - 2.0f * epsilon);
					
					// If ray hit shadow
					if (dot(hn, in_dir) < 0 || sh_intersect) {continue;}

					att = 1.0f;
					if (world->fog) {float att = world->fog->getTrans(lh.distance);}

					RGBColor refl_clr = hit_intersection.solid->material->getReflectance(
						tex_p, hn, -out_dir, in_dir);
					clr = clr + (att * refl_clr * light->getIntensity(lh));
				}
			} else if (hit_intersection.solid->material->useSampling() == Material::Sampling::SAMPLING_ALL) {
				// SAMPLING_ALL
				hn = dot(ray.d, hit_intersection.normal()) > 0 ? -hit_intersection.normal() : hit_intersection.normal();
				Material::SampleReflectance sample = hit_intersection.solid->
					material->getSampleReflectance(tex_p, hn, -out_dir);
				Vector in_dir = sample.direction.normalize();

				Ray secondary_ray = Ray(hp + in_dir * epsilon, in_dir);
				clr = clr + sample.reflectance * this->recRadiance(secondary_ray, depth + 1);
			} else if (hit_intersection.solid->material->useSampling() == Material::Sampling::SAMPLING_SECONDARY) {
				// SAMPLING_SECONDARY
				for (auto light: this->world->light) {
					LightHit lh = light->getLightHit(hp);
					Vector in_dir = lh.direction.normalize();
					Intersection sh_intersect = this->world->scene->intersect(
						Ray(hp + epsilon * in_dir, in_dir), 
						lh.distance);
					
					// If ray hit shadow
					if (dot(hn, in_dir) < 0 || sh_intersect) {continue;}

					att = 1.0f;
					if (world->fog) {float att = world->fog->getTrans(lh.distance);}

					RGBColor refl_clr = hit_intersection.solid->material->getReflectance(
						tex_p, hn, -out_dir, in_dir);
					clr = clr + (att * refl_clr * light->getIntensity(lh));
				}
				Material::SampleReflectance sample = hit_intersection.solid->
					material->getSampleReflectance(tex_p, hn, -out_dir);
				Vector in_dir = sample.direction.normalize();
				RGBColor refl_clr = this->recRadiance(
					Ray(hp + epsilon * in_dir, in_dir),
					depth + 1
				);
				clr = clr + refl_clr * sample.reflectance;
			}

			att = 1.0f;
			if (world->fog) {
				float att = world->fog->getTrans(hit_intersection.distance);
				clr = (1 - att) * world->fog->getColor(hit_intersection.hitPoint()) + att * clr;
			}
		}
		
		return clr.clamp();
	}

}