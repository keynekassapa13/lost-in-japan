#include <core/scalar.h>
#include <core/image.h>
#include <rt/renderer.h>
#include <rt/ray.h>
#include <rt/integrators/integrator.h>
#include <iostream>
#include <core/random.h>
#include <math.h>
#include <rt/cameras/camera.h>

namespace rt {

	Renderer::Renderer(Camera* cam, Integrator* integrator)
	{
		this->cam = cam;
		this->integrator = integrator;
	}

	void Renderer::rec(Image& img, uint w_start, uint w_end) {
		for (uint i = w_start; i < w_end; i++) {
			std::cout << "i = " << i << std::endl;
			for (uint j = 0; j < img.height(); j++) {
				RGBColor clr = RGBColor::rep(0.0f);
				for (uint k = 0; k < samples; k++) {

					float ii = (i + random()) * 2.0f / img.width() - 1.0f;
					float jj = (j + random()) * 2.0f / img.height() - 1.0f;

					Ray primary_ray = this->cam->getPrimaryRay(ii, -jj);
					clr = clr + integrator->getRadiance(primary_ray);
				}
				img(i, j) = clr / samples;
				img(i, j) = img(i, j).gamma(1.0f/2.2f);
			}
		}
	}

void Renderer::render(Image& img) {
	if (samples > 1) {
		int num_threads = floor(std::thread::hardware_concurrency() / 4 * 3);
		// int num_threads = 6;
  	std::vector<std::thread> threads;
		std::cout << "Using " << num_threads << " threads" << std::endl;

		uint start_w = 1;
		uint gap = img.width();
		if (img.width() > num_threads) {start_w = img.width() / num_threads; gap = num_threads;}

		for (uint i = 0; i < gap - 1; ++i) {
			threads.emplace_back(std::thread(&Renderer::rec, this, std::ref(img), i * start_w, (i + 1) * start_w));
		}
		threads.emplace_back(std::thread(&Renderer::rec, this, std::ref(img), (num_threads - 1) * start_w, img.width()));

		for (auto& th : threads) {
        	th.join();
		}

		// for (uint i = 0; i < img.width(); i++) {
		// 	std::cout << "i = " << i << std::endl;
		// 	for (uint j = 0; j < img.height(); j++) {
		// 		RGBColor clr = RGBColor::rep(0.0f);
		// 		for (uint k = 0; k < samples; k++) {

		// 			float ii = (i + random()) * 2.0f / img.width() - 1.0f;
		// 			float jj = (j + random()) * 2.0f / img.height() - 1.0f;

		// 			Ray primary_ray = this->cam->getPrimaryRay(ii, -jj);
		// 			clr = clr + integrator->getRadiance(primary_ray);
		// 		}
		// 		img(i, j) = clr / samples;
		// 	}
		// }

	} else {
		for (uint i = 0; i < img.width(); i++) {
			for (uint j = 0; j < img.height(); j++) {

				// Normalized coordinates
				// Camera Space Coordinates

				float ii = (i + 0.5f) * 2.0f / img.width() - 1.0f;
				float jj = (j + 0.5f) * 2.0f / img.height() - 1.0f;

				Ray primary_ray = this->cam->getPrimaryRay(ii, -jj);
				RGBColor clr = integrator->getRadiance(primary_ray);
				img(i, j) = clr;
			}
		}
	}
}

}

rt::RGBColor a1computeColor(rt::uint x, rt::uint y, rt::uint width, rt::uint height);

namespace rt {

	void Renderer::test_render1(Image& img) {
		for (uint i = 0; i < img.width(); i++) {
			for (uint j = 0; j < img.height(); j++) {
				RGBColor clr = a1computeColor(i, j, img.width(), img.height());
				img(i, j) = clr;
			}
		}
	}
}

rt::RGBColor a2computeColor(const rt::Ray& r);

namespace rt {

void Renderer::test_render2(Image& img) {

	for (uint i = 0; i < img.width(); i++) {
		for (uint j = 0; j < img.height(); j++) {

			// Normalized coordinates
			// Camera Space Coordinates

			float ii = (i + 0.5f) * 2.0f / img.width() - 1.0f;
			float jj = (j + 0.5f) * 2.0f / img.height() - 1.0f;

			Ray primary_ray = this->cam->getPrimaryRay(ii, -jj);
			img(i, j) = a2computeColor(primary_ray);
		}
	}
}

}
