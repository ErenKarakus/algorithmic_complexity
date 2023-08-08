#include <string>
#include <list>
#include <fstream>
#include <iostream>
#include <chrono>
#include <algorithm>

struct brickNamesStruct {
    std::list<std::pair<std::string, std::string>> a;
    std::list<std::pair<std::string, std::string>> b;
};

struct testData {
    std::string label;
    std::string path;
};

bool sortbysec(const std::pair<std::string, std::string>& a, const std::pair<std::string, std::string>& b) {
    return (a.second < b.second);
}
bool sortbysecInt(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    return (a.second < b.second);
}

brickNamesStruct getBricks(std::string path)
{
    path.erase(std::remove_if(path.begin(), path.end(), ::isspace), path.end());
    brickNamesStruct brickNames;
    std::ifstream infile(path);
    if (!infile.good()) throw std::invalid_argument("File not found");
    std::string line;
    while (std::getline(infile, line)) {
        const size_t pos = line.find(",");
        const std::string side1 = line.substr(0, pos);
        const std::string side2 = line.substr(pos + 1);
        brickNames.a.push_back({ side1, side2 });
    }
    infile.close();
    brickNames.b = brickNames.a;
    brickNames.b.sort();
    brickNames.a.sort(sortbysec);
    return brickNames;
}

std::list<std::string> get_results(const std::string path) {
    brickNamesStruct bricks = getBricks(path);
    std::list<std::pair<std::string, std::string>>::iterator aPoint = bricks.a.begin();
    std::list<std::pair<std::string, std::string>>::iterator bPoint = bricks.b.begin();
    std::list<std::pair<std::string, std::string>> c;
    std::list<std::pair<std::string, int>> p;

    const int n = int(bricks.a.size());
    while (aPoint != bricks.a.end()) {
        if (aPoint->second == bPoint->first) {
            c.push_back({ aPoint->first, bPoint->second });
            std::advance(aPoint, 1);
            std::advance(bPoint, 1);
        }
        else if (aPoint->second < bPoint->first) {
            p.push_back({ aPoint->first, n - 1 });
            p.push_back({ aPoint->second, n });
            std::advance(aPoint, 1);
        }
        else if (aPoint->second > bPoint->first) {
            std::advance(bPoint, 1);
        }
    }

    p.sort();
    std::list<std::pair<std::string, int>>::iterator pPoint = p.begin();
    std::list<std::pair<std::string, int>> f;
    std::list<std::pair<std::string, int>>::iterator fPoint = f.begin();

    int d = 2;
    while (d < n) {
        bricks.a = c;
        bricks.b = c;

        c.clear();

        bricks.b.sort();
        bricks.a.sort(sortbysec);

        aPoint = bricks.a.begin();
        bPoint = bricks.b.begin();
        pPoint = p.begin();

        std::list<std::pair<std::string, std::string>>::iterator enda = bricks.a.end();
        std::advance(enda, -1);

        std::list<std::pair<std::string, std::string>>::iterator endb = bricks.b.end();
        std::advance(endb, -1);

        std::list<std::pair<std::string, int>>::iterator endp = p.end();
        std::advance(endp, -1);

        while (aPoint != bricks.a.end()) {
            if (aPoint->second == bPoint->first) {
                c.push_back({ aPoint->first, bPoint->second });
                std::advance(aPoint, 1);
                if (bPoint != endb) std::advance(bPoint, 1);
            }
            else if (aPoint->second == (pPoint->first)) {
                f.push_back({ aPoint->first, pPoint->second - d });
                std::advance(aPoint, 1);
                if (pPoint != endp) std::advance(pPoint, 1);
            }
            else if (aPoint->second > bPoint->first) {
                if (bPoint != endb) std::advance(bPoint, 1);
                else if (aPoint->second > pPoint->first) {
                    if (pPoint != endp) std::advance(pPoint, 1);
                }
            }
            else if (aPoint->second > pPoint->first) {
                if (pPoint != endp) std::advance(pPoint, 1);
            }

        }

        f.sort();

        p.merge(f);
        p.sort();

        f.clear();

        d *= 2;
    }

    p.sort(sortbysecInt);
    std::list<std::string> results;
    pPoint = p.begin();
    while (pPoint != p.end()) {
        results.push_back(pPoint->first);
        std::advance(pPoint, 1);
    }
    std::ofstream myfile("testing.txt");
    if (myfile.is_open()) {
        for (auto x : results) {
            myfile << x << "\n";
        }
        myfile.close();
    }
    return results;
}

std::list<testData> getTestData() {
    std::ifstream infile("Great_Wall_Problem-test_data\\paths.txt");
    if (!infile.good()) throw std::invalid_argument("File not found");
    std::list<testData> paths = {};
    std::string line;
    while (std::getline(infile, line)) {
        const size_t pos = line.find(",");
        const std::string label = line.substr(0, pos);
        const std::string path_found = line.substr(pos + 1);
        testData testCase = { label, path_found };
        paths.push_back(testCase);
    }
    infile.close();
    return paths;
}

int main()
{
    std::list<testData> paths = getTestData();
    for (testData x : paths) {
        auto start = std::chrono::high_resolution_clock::now();
        std::list<std::string> result = get_results(x.path);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        std::cout << x.label << "\t" << duration.count() << std::endl;
    }
}
