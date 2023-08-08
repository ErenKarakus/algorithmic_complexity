#include "rseaWorst.h"

struct brickNamesStruct {
	std::map<std::string, std::string>order;
	std::map<std::string, std::string>revereseOrder;
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

void westWall(const std::map<std::string, std::string> brickNames, std::list<std::string>& result) {
	while (brickNames.find(result.front()) != brickNames.end())
	{
		const std::map<std::string, std::string>::const_iterator foundAt = brickNames.find(result.front());
		result.push_front(foundAt->second);
	}
}

void eastWall(const std::map<std::string, std::string> brickNames, std::list<std::string>& result) {
	while (brickNames.find(result.front()) != brickNames.end())
	{
		const std::map<std::string, std::string>::const_iterator foundAt = brickNames.find(result.front());
		result.push_front(foundAt->second);
	}
}

std::list<std::string> output(std::string path) {
	const brickNamesStruct brickNames = getBricks(path);
	const std::map<std::string, std::string>::const_iterator startPoint = brickNames.order.begin();
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

int main(int argc, char* argv[]) {
	//std::cout << "Start:" << argv[1] << std::endl;
	std::list<std::string>result = output(argv[1]);
	viewOutput(result);
}