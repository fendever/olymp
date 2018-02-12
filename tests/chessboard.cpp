#include <chessboard.h>

int main() {
    olymp::Chessboard chb;
    chb.get(1, 1) = olymp::Chessboard::BlackPawn;
    std::cout << chb << std::endl;
}
