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
	ofn.lpstrFilter = TEXT("Real Division Engine World (*.rdew)\0*.rdew\0All Files (*.*)\0*.*\0");
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

			vector<string> lines;

			string token;
			stringstream ss(fileContent);

			while (std::getline(ss, token, ';')) {
				lines.push_back(token);
			}
			for (string s : lines)
			{
				if(s[0] == 'W') 
				{
					string temp;
					for (char c : s) {
						if (isdigit(c) || c == ',' || c == '.' || c == '-') {
							temp.push_back(c);
						}
					}

					string token;
					stringstream ss(temp);
					vector<double> out;

					while (std::getline(ss, token, ',')) {
						out.push_back(stod(token));
					}

					this->addWall(Wall(
						"Wall",
						{
							Point(out[0] * this->screenWidth, out[1] * this->screenHeight, 0),
							Point(out[2] * this->screenWidth, out[3] * this->screenHeight, 0),
							Point(out[2] * this->screenWidth, out[3] * this->screenHeight, 10),
							Point(out[0] * this->screenWidth, out[1] * this->screenHeight, 10),
						}
					));
				}
				else if (s[0] == 'E') 
				{
					string temp;
					int objMultiplier = 10;
					for (char c : s) {
						if (isdigit(c) || c == ',' || c == '.' || c == '-') {
							temp.push_back(c);
						}
					}
					temp.erase(temp.length() - 1);

					string token;
					stringstream ss(temp);
					vector<double> out;

					while (std::getline(ss, token, ',')) {
						out.push_back(stod(token));
					}


					double xpos = out[0] * this->screenWidth;
					double ypos = out[1] * this->screenHeight;

					vector<Vector3> verteces;
					for (int i = 2; i < out.size(); i += 3) {
						verteces.push_back(
							Vector3(
								out[i] * objMultiplier + xpos, out[i + 1] * objMultiplier + ypos, out[i + 2] * objMultiplier
							));
					}
					this->addEntity(
						Entity(
							"Entity",
							Vector3(xpos, ypos, 0),
							verteces
						));
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