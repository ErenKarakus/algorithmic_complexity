#include "rseaOptimalTest.h"

struct brickNamesStruct {
	std::unordered_map<std::string, std::string>order;
	std::unordered_map<std::string, std::string>revereseOrder;
};

struct testData {
	std::string label;
	std::string path;
};

brickNamesStruct getBricks(std::string path) {
	path.erase(std::remove_if(path.begin(), path.end(), ::isspace), path.end());
	brickNamesStruct brickNames;
	std::ifstream infile(path);
	if (!infile.good())throw std::invalid_argument("File not found");
	std::string line;
	while (std::getline(infile, line)) {
		const size_t pos = line.find(",");
		const std::string side1 = line.substr(0, pos);
		const std::string side2 = line.substr(pos + 1);
		brickNames.order.insert({ side1,side2 });
		brickNames.revereseOrder.insert({ side2,side1 });

	}
	infile.close();
	return brickNames;
}

void westWall(const std::unordered_map<std::string, std::string> brickNames, std::list<std::string>& result) {
	while (brickNames.find(result.front()) != brickNames.end())
	{
		const std::unordered_map<std::string, std::string>::const_iterator foundAt = brickNames.find(result.front());
		result.push_front(foundAt->second);
	}
}

void eastWall(const std::unordered_map<std::string, std::string> brickNames, std::list<std::string>& result) {
	while (brickNames.find(result.front()) != brickNames.end())
	{
		const std::unordered_map<std::string, std::string>::const_iterator foundAt = brickNames.find(result.front());
		result.push_front(foundAt->second);
	}
}

std::list<std::string> output(std::string path) {
	const brickNamesStruct brickNames = getBricks(path);
	const std::unordered_map<std::string, std::string>::const_iterator startPoint = brickNames.order.begin();
	std::list<std::string> result = { startPoint->first, startPoint->second };

	westWall(brickNames.revereseOrder, result);
	eastWall(brickNames.order, result);
	return result;
}

void viewOutput(std::list<std::string>& result) {
	for (std::string const& answers : result) {
		std::cout << answers << std::endl;
	}
}

std::list<testData> getTestData() {
	std::ifstream infile("Great_Wall_Problem-test_data\\paths.txt");
	if (!infile.good()) throw std::invalid_argument("File not found");
	std::list<testData> paths = {};
	std::string line;
	while (std::getline(infile, line)) {
		const size_t pos = line.find(",");
		const std::string label = line.substr(0, pos);
		const std::string pathFound = line.substr(pos + 1);
		testData testCase = { label,pathFound };
		paths.push_back(testCase);
	}
	infile.close();
	return paths;
}

int main() {
	std::list<testData> paths = getTestData();
	for (testData x : paths) {
		auto start = std::chrono::high_resolution_clock::now();
		std::list<std::string>result = output(x.path);
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
		std::cout << x.label << "\t" << duration.count() << std::endl;
	}
}
