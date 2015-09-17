// map::insert (C++98)
#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <algorithm> //std::find_if
#include <ctime>


class Xpto2000 {
	std::vector<int> myints;
	int id;
public:
	Xpto2000(int i) :
			id(0) {
		myints.reserve(i);
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
		Xpto2000 *m = new Xpto2000(rand() % maxloop + 1);
		m->fill_vector_random();
		m->setId(i);
		objects_vector[i] = m;
		auto to_insert = std::pair<void*, Xpto2000*>(static_cast<void*>(m), m);
		objects_map.insert(to_insert);
	}
}


Xpto2000* find_by_id_in_vector_slow(const std::vector<Xpto2000*> &objects_vector, int id){
	auto it = std::find_if(objects_vector.begin(),
			objects_vector.end(),
			[&id](const Xpto2000 *obj) {
				return obj->getId() == id;
			});
	return *it;
}

Xpto2000* find_by_id_in_vector_fast(const std::vector<Xpto2000*> &objects_vector, int id){

	Xpto2000*  obj = objects_vector[id];
	std::cout << "\nVec:\t" <<  static_cast<void*>(obj) << " : " << obj->getId() << std::endl;
	return obj;
}

void delete_object_in_map_by_memory_address(
	std::map<void*, Xpto2000*> &objects_map,
	void* memory_address)  {
	auto it = objects_map.find(memory_address);
	if (it != objects_map.end())
		std::cout << "Map:\t" << it->first << " : " << it->second->getId() << " size = " << objects_map.size() << std::endl;
		objects_map.erase(it);
		delete  it->second;
}

int main_map_performance(int argc, char **argv) {
	unsigned int maxloop = 100;
	if (argc > 1)
		maxloop = atoi(argv[1]);

	std::vector<Xpto2000*> objects_vector(maxloop);
	std::map<void*, Xpto2000*> objects_map; // Map indexed by memory address

	init(objects_vector,objects_map,maxloop);

	//seed
	std::srand(std::time(0));
	while (objects_map.size() > 0) {
		int id = std::rand() % maxloop;

		auto obj = find_by_id_in_vector_fast(objects_vector,id);
		delete_object_in_map_by_memory_address(objects_map,
			static_cast<void*>(obj));
	}

	// free memory
	for (auto it = objects_vector.begin(); it != objects_vector.end(); ++it)
		if (*it) {
			//std::cout << "Not Null: " << (*it)->getId() << std::endl;
			delete *it;
		}

	return 0;
}
