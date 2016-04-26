#include "import.h"

/*
 * #Data(struct DataFile)
 * Constructor for a Data object
 *
 * @Parameters:		struct DataFile that holds input information about a text file
 * @Functionality:	Creates a Data Object from the DataFile struct
 * @Return:		Data object
 */
Data::Data(struct DataFile df) {
	this->file = df.path;
	this->matrix_dim = df.dim;
	this->allocMatrix();
	this->readData();
	this->createGraph();
}

/*
 * #~Data() 
 * Destructor for a Data object
 *
 * @Parameters:
 * @Functionality:	Calls deallocMatrix() to destroy the matrix
 * @Return: 
 */
Data::~Data() {
	this->deallocMatrix();
}

/*
 * #allocMatrix() 
 *
 * @Parameters:
 * @Functionality:	Allocates space for the matrix in the Data object
 * @Return: 
 */
void Data::allocMatrix() {
	this->matrix = new float *[this->matrix_dim];
	for (unsigned int i = 0; i < this->matrix_dim; ++i)
		this->matrix[i] = new float [this->matrix_dim];
}

/*
 * #deallocMatrix() 
 *
 * @Parameters:
 * @Functionality:	Deallocates space for the matrix in the Data object
 * @Return: 
 */
void Data::deallocMatrix() {
	for (unsigned int i = 0; i < this->matrix_dim; ++i)
		delete [] this->matrix[i];
	delete [] this->matrix;
}

/*
 * #readData() 
 *
 * @Parameters:		
 * @Functionality:	Reads data in from the file and inputs the values read in 
 * 			into the matrix
 * @Return:		
 */
void Data::readData() {
	std::ifstream ifs(this->file);
	if (!ifs) {
		std::cerr << "Invalid data file path";
		throw;
	}
	std::string line;
	unsigned int line_num = 0, val_count = 0, 
		exp_count = this->matrix_dim * this->matrix_dim;
	while (std::getline(ifs, line)) {
		std::stringstream ss(line);
		float val;
		for (unsigned int i = 0; i < this->matrix_dim; ++i) {
			ss >> val;
			this->matrix[line_num][i] = val;
			++val_count;
		}
		++line_num;
	}
	
	if (val_count != exp_count) {
		std::cerr << "Bad data file.\nExpected " << exp_count << " values.\n"
			<< "Found " << val_count << ".\n";
		throw;
	}
}

/*
 * #showData() 
 *
 * @Parameters:		
 * @Functionality:	Prints out all of the numbers in the matrix
 * @Return:		
 */
void Data::showData() {
	for (unsigned int i = 0; i < this->matrix_dim; ++i) {
		for (unsigned int j = 0; j < this->matrix_dim; ++j) {
			std:: cout << this->matrix[i][j] << " ";
		}
		std:: cout << std::endl;
	}
}


/*
 * createGraph() 
 *
 * @Parameters:		
 * @Functionality:	Creates a graph based on the adjacency list. The graph is bidirectional,
 * 			or undirected
 * @Return:		
 */
void Data::createGraph() {
	srand(0);
	// populate the adjaency list with random count of nearest neighbors
	for (unsigned int i = 0; i < this->matrix_dim; ++i) {
		Vertex V(i);
		for (unsigned int j = 0; j < this->matrix_dim; ++j) {
			if (i != j) {
				std::pair<float, int> e = std::make_pair(this->matrix[i][j], j);
				V.addEdge(e);
			}
		}
		this->adjacency.push_back(V);
	}
}

/*
 * outputGraph(string) 
 *
 * @Parameters:		string with the name of the outfile
 * @Functionality:	Outputs the graph to a file
 * @Return:		
 */
void Data::outputGraph(std::string ofile) {
	std::ofstream ofs(ofile);
	for (auto v : this->adjacency) {
		ofs << v.id << " : ";
		for (auto e : v.edges)
			ofs << e.first << "," << e.second << " ";
		ofs << std::endl;
	}
	ofs.close();
}


