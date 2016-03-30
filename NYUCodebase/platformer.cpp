#ifdef _WINDOWS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#ifdef _WINDOWS
#include <GL/glew.h>
#endif
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "ShaderProgram.h"
#include "Matrix.h"
#include <vector>
#include <string>
#include <SDL_mixer.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>


#ifdef _WINDOWS
#define RESOURCE_FOLDER ""
#else
#define RESOURCE_FOLDER "NYUCodebase.app/Contents/Resources/"
#endif

#define TILE_SIZE 0.5f 
#define SPRITE_COUNT_X 30
#define SPRITE_COUNT_Y 30
#define LEVEL_HEIGHT 32
#define LEVEL_WIDTH 128

SDL_Window* displayWindow;
unsigned char ** levelData;
int mapWidth;
int mapHeight;
Matrix modelMatrixForAlien;
Matrix projectionMatrixForAlien;
Matrix viewMatrixAlien;
ShaderProgram *program;


using namespace std;











class Entity
{
public:
	void Draw();
	float x;
	float y;
	float rotation;
	int textureID;
	float width;
	float height;
	float speed;
	float direction_x;
	float direction_y;
	bool isAlive;
	float shiftedDownBy;



	Entity(float xPos, float yPos, float rotationVal, int textureId, float Width,
		float Height, float Speed, float Direction_x, float Direction_y, bool moveDown = false, float shifteddownBy = 0.0f) : x(xPos), y(yPos), rotation(rotationVal),
		textureID(textureId), width(Width), height(Height), speed(Speed), direction_x(Direction_x), direction_y(Direction_y), isAlive(moveDown), shiftedDownBy(shiftedDownBy)
	{

	}

	void moveEntity(float x, float y)
	{

		this->x += x;
		this->y += y;
	}
	void scaleEntity(float x, float y)
	{
		this->height *= y;
		this->width *= x;

	}
	void setPos(float x, float y)
	{
		this->x = x;
		this->y = y;

	}



private:




};

class Alien
{
public:
private:

};

class Tilemap
{
public:
	int mapHeight;
	int mapWidth;
};









class SheetSprite {
public:
	SheetSprite();
	SheetSprite(unsigned int textureIDD, float U, float V, float Width, float Height, float
		Size) : textureID(textureIDD), u(U), v(V), width(Width), height(Height), size(Size)
	{

	}
	void Draw(ShaderProgram *program);
	float size;
	unsigned int textureID;
	float u;
	float v;
	float width;
	float height;

};




class Tile
{
public:
	vector<float> vecCoords;
	vector<float> textCoords;
	int textureID;
	Tile(int textID, vector<float>& vec, vector<float>& text) : textureID(textID), vecCoords(vec), textCoords(text)
	{

	}
	void Draw(ShaderProgram* program, vector<float>& vec, vector<float>& text)
	{
		program->setModelMatrix(modelMatrixForAlien);
		program->setProjectionMatrix(projectionMatrixForAlien);
		program->setViewMatrix(viewMatrixAlien);
		glUseProgram(program->programID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vec.data());
		glEnableVertexAttribArray(program->positionAttribute);
		glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, text.data());
		glEnableVertexAttribArray(program->texCoordAttribute);
		glDrawArrays(GL_TRIANGLES, 0, vec.size()/2);
		glDisableVertexAttribArray(program->positionAttribute);
		glDisableVertexAttribArray(program->texCoordAttribute);
	}
};


void placeEntity(string type, int placeX, int placeY)
{






}







GLuint LoadTexture(const char *image_path) {
	SDL_Surface *surface = IMG_Load(image_path);
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB,
		GL_UNSIGNED_BYTE, surface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SDL_FreeSurface(surface);
	return textureID;
}



















void SheetSprite::Draw(ShaderProgram* program) {
	glBindTexture(GL_TEXTURE_2D, textureID);
	GLfloat texCoords[] = {
		u, v + height,
		u + width, v,
		u, v,
		u + width, v,
		u, v + height,
		u + width, v + height
	};
	float aspect = width / height;
	float vertices[] = {
		(-0.5f) * size * aspect, -0.5f * size,
		(0.5f) * size * aspect, 0.5f * size,
		(-0.5f) * size * aspect, 0.5f * size,
		(0.5f)* size * aspect, 0.5f * size,
		(-0.5f) * size * aspect, -0.5f * size,
		(0.5f)* size * aspect, -0.5f * size };
	// draw our arrays
	glUseProgram(program->programID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
	glEnableVertexAttribArray(program->positionAttribute);
	glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
	glEnableVertexAttribArray(program->texCoordAttribute);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(program->positionAttribute);
	glDisableVertexAttribArray(program->texCoordAttribute);

}


//void DrawText(ShaderProgram *program, int fontTexture, std::string text, float size, float spacing, float xPosStart, float yPosStart) {
//	program->setModelMatrix(modelMatrixForText);
//	program->setProjectionMatrix(projectionMatrixForText);
//	program->setViewMatrix(viewMatrixForText);
//	float texture_size = 1.0 / 16.0f;
//	std::vector<float> vertexData;
//	std::vector<float> texCoordData;
//	for (int i = 0; i < text.size(); i++) {
//		float texture_x = (float)(((int)text[i]) % 16) / 16.0f;
//		float texture_y = (float)(((int)text[i]) / 16) / 16.0f;
//		vertexData.insert(vertexData.end(), {
//			((size + spacing) * i + xPosStart) + (-0.5f * size), 0.5f * size + yPosStart,
//			((size + spacing) * i + xPosStart) + (-0.5f * size), -0.5f * size + yPosStart,
//			((size + spacing) * i + xPosStart) + (0.5f * size), 0.5f * size + yPosStart,
//			((size + spacing) * i + xPosStart) + (0.5f * size), -0.5f * size + yPosStart,
//			((size + spacing) * i + xPosStart) + (0.5f * size), 0.5f * size + yPosStart,
//			((size + spacing) * i + xPosStart) + (-0.5f * size), -0.5f * size + yPosStart,
//		});
//		texCoordData.insert(texCoordData.end(), {
//			texture_x, texture_y,
//			texture_x, texture_y + texture_size,
//			texture_x + texture_size, texture_y,
//			texture_x + texture_size, texture_y + texture_size,
//			texture_x + texture_size, texture_y,
//			texture_x, texture_y + texture_size,
//		});
//	}
//	glUseProgram(program->programID);
//	glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertexData.data());
//	glEnableVertexAttribArray(program->positionAttribute);
//	glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoordData.data());
//	glEnableVertexAttribArray(program->texCoordAttribute);
//	glBindTexture(GL_TEXTURE_2D, fontTexture);
//	glDrawArrays(GL_TRIANGLES, 0, text.size() * 6);
//	glDisableVertexAttribArray(program->positionAttribute);
//	glDisableVertexAttribArray(program->texCoordAttribute);
//}









bool readHeader(std::ifstream &stream) {
	string line;
	int mapWidth = -1;
	int mapHeight = -1;
	while (getline(stream, line)) {
		if (line == "") { break; }
		istringstream sStream(line);
		string key, value;
		getline(sStream, key, '=');
		getline(sStream, value);
		if (key == "width") {
			mapWidth = atoi(value.c_str());
		}
		else if (key == "height"){
			mapHeight = atoi(value.c_str());
		}
	}
	if (mapWidth == -1 || mapHeight == -1) {
		return false;
	}
	else { // allocate our map data
		levelData = new unsigned char*[mapHeight];
		for (int i = 0; i < mapHeight; ++i) {
			levelData[i] = new unsigned char[mapWidth];
		}
		return true;
	}
}




bool readLayerData(std::ifstream &stream) 
{
	string line;
	while (getline(stream, line)) {
		if (line == "") { break; }
		istringstream sStream(line);
		string key, value;
		getline(sStream, key, '=');
		getline(sStream, value);
		if (key == "data") {
			for (int y = 0; y < mapHeight; y++) {
				getline(stream, line);
				istringstream lineStream(line);
				string tile;
				for (int x = 0; x < mapWidth; x++) {
					getline(lineStream, tile, ',');
					unsigned char val = (unsigned char)atoi(tile.c_str());
					if (val > 0) {
						// be careful, the tiles in this format are indexed from 1 not 0
						levelData[y][x] = val - 1;
					}
					else {
						levelData[y][x] = 0;
					}
				}
			}
		}
	}
	return true;
}

bool readEntityData(std::ifstream &stream) {
	string line;
	string type;
	while (getline(stream, line)) {
		if (line == "") { break; }
		istringstream sStream(line);
		string key, value;
		getline(sStream, key, '=');
		getline(sStream, value);
		if (key == "type") {
			type = value;
		}
		else if (key == "location") {
			istringstream lineStream(value);
			string xPosition, yPosition;
			getline(lineStream, xPosition, ',');
			getline(lineStream, yPosition, ',');
			float placeX = atoi(xPosition.c_str()) /16 * TILE_SIZE;
			float placeY = atoi(yPosition.c_str()) /16 * -TILE_SIZE;
			cout << placeX << endl;
			cout << placeY << endl;
			placeEntity(type, placeX, placeY);
		}
	}
	return true;
}


template<class obj>
void clearTheHeap(std::vector<obj*>* vec)
{
	for (int i = 0; i < vec->size(); i++)
	{
		delete (*vec)[i];
		(*vec)[i] = nullptr;
	}
}






int main(int argc, char *argv[])
{

	//allows me to print to the console. only affects windows users.
#ifdef _WIN32
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
#endif





	float lastFrameTicks = 0.0f;
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("Jet's World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 320, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);
#ifdef _WINDOWS
	glewInit();
#endif

	glViewport(0, 0, 640, 360);
	projectionMatrixForAlien.setOrthoProjection(-5.33f, 5.33f, -3.0f, 3.0f, -1.0f, 1.0f);
	program = new ShaderProgram(RESOURCE_FOLDER"vertex_textured.glsl", RESOURCE_FOLDER"fragment_textured.glsl");
	glUseProgram(program->programID);

	SDL_Event event;
	bool done = false;


	ifstream infile("world.txt");
	string line;
	if (!infile)
	{
		cout << "OH NOOOOOOOOOOOO!" << endl;
	}
	else
	{
		cout << "SUCCESS!!!" << endl;
		while (getline(infile, line))
		{
			if (line == "[header]") 
			{
				if (!readHeader(infile)) 
				{
					break;
				}
			}
			else if (line == "[layer]") 
			{
				readLayerData(infile);
			}
			else if (line == "[Player]") 
			{
				readEntityData(infile);
			}
		}
	}
	std::vector<float> vertexData;
	std::vector<float> texCoordData;
	for (int y = 0; y < LEVEL_HEIGHT; y++) {
		for (int x = 0; x < LEVEL_WIDTH; x++) {
			float u = (float)(((int)levelData[y][x]) % SPRITE_COUNT_X) / (float)SPRITE_COUNT_X;
			float v = (float)(((int)levelData[y][x]) / SPRITE_COUNT_X) / (float)SPRITE_COUNT_Y;
			float spriteWidth = 1.0f / (float)SPRITE_COUNT_X;
			float spriteHeight = 1.0f / (float)SPRITE_COUNT_Y;
			vertexData.insert(vertexData.end(), {
				TILE_SIZE * x, -TILE_SIZE * y,
				TILE_SIZE * x, (-TILE_SIZE * y) - TILE_SIZE,
				(TILE_SIZE * x) + TILE_SIZE, (-TILE_SIZE * y) - TILE_SIZE,
				TILE_SIZE * x, -TILE_SIZE * y,
				(TILE_SIZE * x) + TILE_SIZE, (-TILE_SIZE * y) - TILE_SIZE,
				(TILE_SIZE * x) + TILE_SIZE, -TILE_SIZE * y
			});
			texCoordData.insert(texCoordData.end(), {
				u, v,
				u, v + (spriteHeight),
				u + spriteWidth, v + (spriteHeight),
				u, v,
				u + spriteWidth, v + (spriteHeight),
				u + spriteWidth, v
			});
		}
	}
	
	int textureForWorld = LoadTexture("spritesheet.png");
	Tile theWorld = Tile(textureForWorld, vertexData, texCoordData);
	theWorld.Draw(program, vertexData, texCoordData);






	while (!done) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
				done = true;
			}

		}


		const Uint8 *keys = SDL_GetKeyboardState(NULL);
		float ticks = (float)SDL_GetTicks() / 1000.0f;
		float elapsed = ticks - lastFrameTicks;
		lastFrameTicks = ticks;
		float velocityForShip = 2 * elapsed;
		float velocityForEnemies = 0.05f * elapsed;
		//bulletSound = Mix_LoadWAV("bullet.wav");




		glClear(GL_COLOR_BUFFER_BIT);


		//==============================================================================================================================================================
		





		SDL_GL_SwapWindow(displayWindow);



	}

	
	
	delete program;
#ifdef _WIN32
	std::cin.get();
#endif

	


	SDL_Quit();
	return 0;
}






















































//#ifdef _WIN32
//	std::cin.get();
//#endif
//

//allows me to print to the console. Only affects windows users.
//#ifdef _WINDOWS
//	AllocConsole();
//	freopen("CONIN$", "r", stdin);
//	freopen("CONOUT$", "w", stdout);
//	freopen("CONOUT$", "w", stderr);
//	//===============================================================================================================================================
//#endif
