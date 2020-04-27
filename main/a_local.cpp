
#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>
#include <rt/world.h>
#include <rt/renderer.h>

#include <rt/cameras/perspective.h>
#include <rt/solids/quad.h>
#include <rt/solids/triangle.h>
#include <rt/solids/sphere.h>
#include <rt/groups/simplegroup.h>

#include <rt/integrators/integrator.h>
#include <rt/intersection.h>

using namespace rt;


void makeBox(Group& scene, const Point& aaa, const Vector& forward, const Vector& left, const Vector& up, CoordMapper* texMapper, Material* material) {
	scene.add(new Quad(aaa, forward, left, texMapper, material));
	scene.add(new Quad(aaa, forward, up, texMapper, material));
	scene.add(new Quad(aaa, left, up, texMapper, material));
	Point bbb = aaa + forward + left + up;
	scene.add(new Quad(bbb, -forward, -left, texMapper, material));
	scene.add(new Quad(bbb, -forward, -up, texMapper, material));
	scene.add(new Quad(bbb, -left, -up, texMapper, material));
}

class DummyIntegrator : public rt::Integrator {
public:
	DummyIntegrator(World* world, bool global = false) : Integrator(world), _global(global) {}
	virtual RGBColor getRadiance(const Ray& ray) const {
		Intersection hit = world->scene->intersect(ray);
		if (hit) {
			Point uv = this->_global ? hit.hitPoint() : hit.local();
			return RGBColor(uv.x, uv.y, uv.z);
		}
		else
			return RGBColor::rep(0.0f);

	}
private:
	bool _global;
};

void a_local() {
	Image img(400, 400);
	World world;
	SimpleGroup scene;
	world.scene = &scene;
	float scale = 0.002f;

	PerspectiveCamera cam(Point(278.f*scale, 273.f*scale, -800.f*scale), Vector(0, 0, 1), Vector(0, 1, 0), 0.686f, 0.686f);

	scene.add(new Quad(Point(000.f, 000.f, 000.f)*scale, Vector(550.f, 000.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, nullptr, nullptr)); //floor
	scene.add(new Quad(Point(550.f, 550.f, 000.f)*scale, Vector(-550.f, 000.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, nullptr, nullptr)); //ceiling
	//scene->add(new Quad(Point(000.f,000.f,560.f)*scale, Vector(550.f,000.f,000.f)*scale, Vector(000.f,550.f,000.f)*scale, nullptr, nullptr)); //back wall
	scene.add(new Triangle(Point(000.f, 000.f, 560.f)*scale, Point(550.f, 000.f, 560.f)*scale, Point(000.f, 550.f, 560.f)*scale, nullptr, nullptr));
	scene.add(new Triangle(Point(550.f, 550.f, 560.f)*scale, Point(550.f, 000.f, 560.f)*scale, Point(000.f, 550.f, 560.f)*scale, nullptr, nullptr));

	scene.add(new Quad(Point(000.f, 000.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, Vector(000.f, 550.f, 000.f)*scale, nullptr, nullptr)); //right wall
	scene.add(new Quad(Point(550.f, 550.f, 000.f)*scale, Vector(000.f, 000.f, 560.f)*scale, Vector(000.f, -550.f, 000.f)*scale, nullptr, nullptr)); //left wall

	scene.add(new Sphere(Point(150.0f, 100.0f, 150.0f)*scale, 99.0f*scale, nullptr, nullptr));

	//tall box
	makeBox(scene, Point(265.f, 000.1f, 296.f)*scale, Vector(158.f, 000.f, -049.f)*scale, Vector(049.f, 000.f, 160.f)*scale, Vector(000.f, 330.f, 000.f)*scale, nullptr, nullptr);

	DummyIntegrator integrator(&world);

	Renderer engine(&cam, &integrator);
	engine.render(img);
	img.writePNG("a6-3a.png");

	DummyIntegrator integratorB(&world, true);

	Renderer engineB(&cam, &integratorB);
	engineB.render(img);
	img.writePNG("a6-3b.png");
}