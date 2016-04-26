#ifndef IMPORT_H
#define IMPORT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <sys/stat.h>
#include <algorithm>
#include <thread>
#include <mutex>


struct Vertex {
	int id;
	std::vector< std::pair<float, int> > edges;
	inline Vertex(int i) {
		this->id = i;
	}
	inline void addEdge(std::pair<float, int> weight_id) {
		if (std::find(this->edges.begin(), this->edges.end(), weight_id)
				== this->edges.end())
			this->edges.push_back(weight_id);
	}
	inline bool hasEdge(int id) {
		for (unsigned int e = 0; e < edges.size(); ++e)
			if (edges[e].second == id)
				return true;
		return false;
	}
};


class Graph {
	private:
		std::vector<Vertex> adjacency;
		
	public:
		Graph(std::vector<Vertex>);
		~Graph();
		void showAdjacency();
};



struct DataFile {
	std::string path;
	int dim;
	inline DataFile(std::string s, int d) {
		struct stat buf;
		if (stat(s.c_str(), &buf)) {
			std::cerr << "Invalid data file path.";
			throw;
		}
		this->path = s;
		this->dim = d;
	}
};


class Data {
	private:
		std::string file;
		float **matrix;
		unsigned int matrix_dim;
		
		std::vector<Vertex> adjacency;
		
		void allocMatrix();
		void deallocMatrix();
		void readData();
		void showData();
		
		void addEdgeToVertex(int);
		
		void createGraph();
		void outputGraph(std::string);
		
	public:
		Data(struct DataFile);
		~Data();
		
		inline unsigned int getDim() const { return this->matrix_dim; }
		inline float** getMatrix() const { return this->matrix; }
		inline std::vector<Vertex> getGraph() const { return this->adjacency; }

};	



#endif
