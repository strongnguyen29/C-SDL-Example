#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

// Cac hang so thong tin cua so
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
const string WINDOW_TITLE = "Tiêu đề cửa sổ";

// khai bao cac function
void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();

void veDiem(SDL_Renderer* &renderer);
void veDuongThang(SDL_Renderer* &renderer);
void veHinhVuong(SDL_Renderer* &renderer);

int main(int argc, char* argv[])
{
    // Khoi tao bien window, renderer cua thu vien SDL
    SDL_Window* window;
    SDL_Renderer* renderer;

    // Goi ham thiet lap thu vien SDL
    initSDL(window, renderer);

    // Goi ham ve diem
    veDiem(renderer);
    veDuongThang(renderer);
    veHinhVuong(renderer);

    // Gọi ham ket thuc chuong trinh
	waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}

/**
 * Ve 1 diem len man hinh (1 điểm bé, sẽ khó nhìn)
 */
void veDiem(SDL_Renderer* &renderer) {
    // Chon mau ve (xám)
    SDL_SetRenderDrawColor(renderer, 100,100,100,255);
    // Ve 1 diem tai toa do 50,50
    SDL_RenderDrawPoint(renderer, 50, 50);
    // Show ra man hinh
    SDL_RenderPresent(renderer);
}

/**
 * Ve duong thang len man hinh
 */
void veDuongThang(SDL_Renderer* &renderer) {
    // Chon mau ve (đỏ)
    SDL_SetRenderDrawColor(renderer, 255,0,0,255);
    // Ve 1 duong thang tai toa do 50,150 ; 300,150
    SDL_RenderDrawLine(renderer, 50, 150, 300, 150);
    // Show ra man hinh
    SDL_RenderPresent(renderer);
}

/**
 * Ve hinh vuong len man hinh
 */
void veHinhVuong(SDL_Renderer* &renderer) {
    // Chon mau ve (xanh)
    SDL_SetRenderDrawColor(renderer, 0,0,255,255);
    // Khoi tao toa do xy, dai, rong hinh vuong
    SDL_Rect hinhVuong;
    hinhVuong.x = 400;
    hinhVuong.y = 250;
    hinhVuong.w = 200;
    hinhVuong.h = 200;
    // Ve hinh vuong
    SDL_RenderFillRect(renderer, &hinhVuong);
    // Show ra man hinh
    SDL_RenderPresent(renderer);
}

/**
 * Hàm ghi log loi khi chay
 */
void logSDLError(std::ostream& os, const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

/**
 * Ham thiet lap cua so ve SDL
 */
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (window == nullptr)
        logSDLError(std::cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (renderer == nullptr)
        logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

/**
 * Ham giai phong cua so ve SDL
 */
void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    // Giai phong tham chieu (but ve)
	SDL_DestroyRenderer(renderer);
	// Giai phong cua cua so ve
	SDL_DestroyWindow(window);
	// Giai phong thu vien
	SDL_Quit();
}

 /**
 * Ham nhan nut de thoat
 */
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
