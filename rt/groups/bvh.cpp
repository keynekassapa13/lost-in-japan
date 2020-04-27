#include <rt/groups/bvh.h>
#include <tuple>
#include <numeric>
// #include <time.h>

namespace rt {

	int num_per_leaf = 3;

	BVH::BVH() {
	}

	BVH::~BVH() {
	}

	void BVH::rebuildIndex() {
		root->p = primitives;
		std::tie(root->area, root->box) = root->getBounds();
		// const clock_t begin_time = clock();
		buildRecursive(root);
		// std::cout << "reconstruction time: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << std::endl;
	}

	void BVH::buildRecursive(BVHNode* parent) {
		if (parent->p.size() > num_per_leaf) {
			float lenx = parent->box.max.x - parent->box.min.x;
			float leny = parent->box.max.y - parent->box.min.y;
			float lenz = parent->box.max.z - parent->box.min.z;
			// Get the longest axis length
			float len_axis = std::max(std::max(lenx, leny), lenz);
			int bool_axis = len_axis == lenx ? 0 : 2;
			bool_axis = len_axis == leny ? 1 : bool_axis;

			float split;
			
			if (_sah) {split = findSAHSplit(bool_axis, len_axis, parent);}
			else {split = findMiddleSplit(bool_axis, parent);}

			std::vector<Primitive *> primitives_list;
			primitives_list = parent->p;

			while (primitives_list.size() > 0) {
				Primitive* temp_p = primitives_list.back();
				primitives_list.pop_back();
				
				BBox pbox = temp_p->getBounds();
				// Get middle point of the primitive
				float pmiddle;
				if (bool_axis == 0) {pmiddle = (pbox.max.x + pbox.min.x) / 2;}
				else if (bool_axis == 1) {pmiddle = (pbox.max.y + pbox.min.y) / 2;}
				else if (bool_axis == 2) {pmiddle = (pbox.max.z + pbox.min.z) / 2;}

				if (
					pmiddle < split || 
					(pmiddle == split && parent->left != nullptr && parent->right != nullptr && parent->left->p.size() < parent->right->p.size())
				) {
					// Add to left child
					if (parent->left == nullptr) {parent->left = new BVHNode();}
					parent->left->add(temp_p);
				} else {
					// Add to right child
					if (parent->right == nullptr) {parent->right = new BVHNode();}
					parent->right->add(temp_p);
				}
			}

			if (parent->left != nullptr) {
				std::tie(parent->left->area, parent->left->box) = parent->left->getBounds();
				if (parent->left->p.size() != parent->p.size()) buildRecursive(parent->left);
			}
			if (parent->right != nullptr) {
				std::tie(parent->right->area, parent->right->box) = parent->right->getBounds();
				if (parent->right->p.size() != parent->p.size()) buildRecursive(parent->right);
			}
		}
	}

	float BVH::findMiddleSplit(int bool_axis, BVHNode* parent) {
		// Search for middle point of the longest axis
		float split;
		if (bool_axis == 0) {split = (parent->box.min.x + parent->box.max.x) / 2;}
		else if (bool_axis == 1) {split = (parent->box.min.y + parent->box.max.y) / 2;}
		else if (bool_axis == 2) {split = (parent->box.min.z + parent->box.max.z) / 2;}
		return split;
	}

	float BVH::findSAHSplit(int bool_axis, float len_axis, BVHNode* parent) {
		for (int i = 0; i < _bin; i++) {
			bins[i] = 0; bins_n[i] = 0;
		}
		float mid; int num;
		// Implement Binning SAH
		for (int i = 0; i < parent->p.size(); i++) {
			BBox pbox = parent->p[i]->getBounds();
			if (bool_axis == 0) {
				mid = (pbox.min.x + pbox.max.x) / 2;
				num = roundf((mid - parent->box.min.x) / len_axis * (_bin - 1));
			} else if (bool_axis == 1) {
				mid = (pbox.min.y + pbox.max.y) / 2;
				num = roundf((mid - parent->box.min.y) / len_axis * (_bin - 1));
			} else if (bool_axis == 2) {
				mid = (pbox.min.z + pbox.max.z) / 2;
				num = roundf((mid - parent->box.min.z) / len_axis * (_bin - 1));
			}
			bins[num] += parent->p[i]->getArea();
			bins_n[num] ++;
		}
		// Compute cost
		float SA_L = 0, N_L = 0, cbest = FLT_MAX, cleft, cright, sah_split;
		for (int i = 1; i <= _bin; i++) {
			SA_L = 0;
			N_L = 0;
			for (int j = 0; j < i; j++) {SA_L = SA_L + bins[j]; N_L = N_L + bins_n[j];};
			cleft = SA_L / parent->area * N_L;
			cright = (parent->area - SA_L) / parent->area * (parent->p.size() - N_L);
			if ((cleft + cright) < cbest) {sah_split = i; cbest = cleft + cright;}
		}
		
		if (bool_axis == 0) return parent->box.min.x + ((sah_split/_bin) * len_axis);
		if (bool_axis == 1) return parent->box.min.y + ((sah_split/_bin) * len_axis);
		if (bool_axis == 2) return parent->box.min.z + ((sah_split/_bin) * len_axis);
	}

	Intersection BVH::intersect(const Ray& ray, float previousBestDistance) const {
		Intersection prim_hit_temp, prim_hit = Intersection::failure();
		BBox b = BBox();
		float d = previousBestDistance;

		std::vector<BVHNode*> nodes;
		nodes.push_back(this->root);
		BVHNode* n = new BVHNode();

		while (nodes.size() > 0) {
			n = nodes.back();
			nodes.pop_back();

			if (n->left == nullptr && n->right == nullptr) {
				// Leaf
				for (auto primitive: n->p) {
					prim_hit_temp = primitive->intersect(ray, d);
					if (prim_hit_temp && prim_hit_temp.distance < d) {
						d = prim_hit_temp.distance;
						prim_hit = prim_hit_temp;
					}
				}
			} else {
				// Non-Leaf
				float bmin, bmax;
				if (n->left != nullptr) {
					b = n->left->box;
					std::tie(bmin, bmax) = b.intersect(ray);
					if (bmin < FLT_MAX && bmax > FLT_MIN) {nodes.push_back(n->left);};
				}
				if (n->right != nullptr) {
					b = n->right->box;
					std::tie(bmin, bmax) = b.intersect(ray);
					if (bmin < FLT_MAX && bmax > FLT_MIN) {nodes.push_back(n->right);};
				}
			}
		}

		return prim_hit;
	}

	BBox BVH::getBounds() const {
		BBox b = BBox::empty();
		for (uint i = 0; i < primitives.size(); i++) {
			b.extend(primitives[i]->getBounds());
		};
		return b;
	}

	void BVH::add(Primitive* p) {
		primitives.push_back(p);
	}

	void BVH::setMaterial(Material* m) {
		for (uint i = 0; i < primitives.size(); i++) {
			primitives[i]->setMaterial(m);
		}
	}

	void BVH::setCoordMapper(CoordMapper* cm) {
		for (uint i = 0; i < primitives.size(); i++) {
			primitives[i]->setCoordMapper(cm);
		}
	}

	float BVH::getArea() const {
		return 0;
	}

}
