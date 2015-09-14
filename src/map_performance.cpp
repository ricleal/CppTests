// map::insert (C++98)
#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <algorithm> //std::find_if

class Xpto2000 {
	std::vector<int> myints;
	int id;
public:
	Xpto2000(int i) :
			id(0) {
		myints.resize(i);
	}

	void setId(int id_) {
		id = id_;
	}
	int getId() const {
		return id;
	}
	void fill_vector_random() {
		int vec_size = myints.size();
		for (int i = 0; i < vec_size; ++i) {
			myints[i] = rand() % 20 + 1;
		}
	}
};

void init(std::vector<Xpto2000*> &objects_vector,
		std::map<void*, Xpto2000*> &objects_map,
		const unsigned int maxloop) {
	// initialisations
	for (unsigned int i = 0; i < maxloop; ++i) {
		Xpto2000 *m = new Xpto2000(100);
		m->fill_vector_random();
		m->setId(i);
		objects_vector.push_back(m);

		auto to_insert = std::pair<void*, Xpto2000*>(static_cast<void*>(m), m);
		objects_map.insert(to_insert);
	}
}




int main_map_performance(int argc, char **argv) {
	unsigned int maxloop = 100;
	if (argc > 1)
		maxloop = atoi(argv[1]);

	std::vector<Xpto2000*> objects_vector(maxloop);
	std::map<void*, Xpto2000*> objects_map; // Map indexed by memory address

	init(objects_vector,objects_map,maxloop);

	while (objects_map.size() > 0) {
		int id = std::rand() % maxloop;

		auto it_xpto = std::find_if(objects_vector.begin(),
				objects_vector.end(), [&id](const Xpto2000 *obj) {
					return obj !=NULL && obj->getId() == id;
				});

		auto it = objects_map.find(static_cast<void*>(*it_xpto));
		if (it != objects_map.end())
			objects_map.erase(it);

	}

	// free memory
	for (auto it = objects_vector.begin(); it != objects_vector.end(); ++it) {
		if (*it) {
			//std::cout << "Deleting: " << (*it)->getId() << std::endl;
			delete *it;
		}
	}

	return 0;
}
