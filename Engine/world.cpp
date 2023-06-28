#include "world.h"

World::World(string name)
{
	this->name = name;
}

void World::addEntity(Entity entity)
{
	this->entityList.push_back(entity);
}

vector<Entity> World::getEntities() {
	return this->entityList;
}

void World::deleteEtity(Entity entity)
{
}

void World::addWall(Wall wall)
{
	this->wallList.push_back(wall);
}

vector<Wall> World::getWalls()
{
	return this->wallList;
}

void World::deleteWall(Wall wall)
{
}

void World::setMeasurements(vector<double> measurements)
{
	this->measurements = measurements;
}

vector<double> World::getMeasurements()
{
	return this->measurements;
}

bool World::importFile()
{
	OPENFILENAME ofn;					// common dialog box structure
	TCHAR szFile[260] = { 0 };			// if using TCHAR macros

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = NULL;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn)) {
		string filePath = ofn.lpstrFile;

		// Read the contents of the file
		ifstream file(filePath);
		if (file) {
			ostringstream oss;
			oss << file.rdbuf();
			string fileContent = oss.str();
			file.close();

			vector<string> splitText = splitString(fileContent, ';');
			for (string s : splitText) {
				vector<string> attributes = splitString(s, '/');
				if (attributes.at(0) == "W") // Wall
				{
					vector<vector<string>> coords;
					coords.push_back(splitString(attributes.at(1), ','));
					coords.push_back(splitString(attributes.at(2), ','));
					coords.push_back(splitString(attributes.at(3), ','));
					coords.push_back(splitString(attributes.at(4), ','));

					addWall(Wall(
						"Wall",
						{
							Point(stod(coords.at(0).at(0)), stod(coords.at(0).at(1)), stod(coords.at(0).at(2))),
							Point(stod(coords.at(1).at(0)), stod(coords.at(1).at(1)), stod(coords.at(1).at(2))),
							Point(stod(coords.at(2).at(0)), stod(coords.at(2).at(1)), stod(coords.at(2).at(2))),
							Point(stod(coords.at(3).at(0)), stod(coords.at(3).at(1)), stod(coords.at(3).at(2)))
						}
					));
				}
				else if (attributes.at(0) == "E") // Entity
				{
					//
				}
			}
		}
	}
	return false;
}

vector<string> World::splitString(const string& input, char delimiter)
{
	vector<string> tokens;
	istringstream iss(input);
	string token;

	while (getline(iss, token, delimiter)) {
		tokens.push_back(token);
	}

	return tokens;
}