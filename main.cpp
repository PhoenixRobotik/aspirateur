#include "board_kiwi.h"


std::unique_ptr<BoardKiwi> kiwi = 0;

int main(int argc, char const *argv[])
{
    kiwi = std::make_unique<BoardKiwi>();
    while(1);
	return 0;
}
