#include "Entity.h"
void Entity::Set_W(int W) {
	this->brect.w = W;
}
void Entity::Set_H(int H) {
	this->brect.h = H;
}
void Entity::Set_X(int X) {
	this->brect.x = X;
}
void Entity::Set_Y(int Y) {
	this->brect.y = Y;
}
void Entity::Set_Surface(SDL_Surface* Sur) {
	this->Sur = Sur;
}
void Entity::Set_Render(SDL_Renderer* Ren) {
	this->Ren = Ren;
}
void Entity::Set_Texture(SDL_Texture* Tex) {
	this->Tex = Tex;
}
void Entity::Set_pbrect() {
	this->pbrect=&(this->brect);
}
int Entity::Get_W() {
	return this->brect.w;
}
int Entity::Get_H() {
	return this->brect.h;
}
int Entity::Get_X() {
	return this->brect.x;
}
int Entity::Get_Y() {
	return this->brect.y;
}
SDL_Surface* Entity::Get_Surface() {
	return this->Sur;
}
SDL_Renderer* Entity::Get_Render() {
	return this->Ren;
}
SDL_Texture* Entity::Get_Tex() {
	return this->Tex;
}
SDL_Rect* Entity::Get_pbrect() {
	return this->pbrect;
}
