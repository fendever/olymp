#pragma once
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace olymp {
class Chessboard {
public:
    explicit Chessboard(int N = 8) : N(N), chessboard(N * N) {}

    struct Point {
        int r;
        int c;
    };

    enum ColorlessPiece { Pawn = 1, Bishop = 2, Rook = 3, Knight = 4, Queen = 5, King = 6 };

    enum Piece {
        BlackKing = -King,
        BlackQueen = -Queen,
        BlackKnight = -Knight,
        BlackRook = -Rook,
        BlackBishop = -Bishop,
        BlackPawn = -Pawn,
        Nothing = 0,
        WhitePawn = Pawn,
        WhiteBishop = Bishop,
        WhiteRook = Rook,
        WhiteKnight = Knight,
        WhiteQueen = Queen,
        WhiteKing = King,
    };

    Piece& get(int r, int c);
    Piece& get(const Point& p);

    Piece get(int r, int c) const;
    Piece get(const Point& p) const;
    void print(std::ostream& s) const;


    template <int Piece>
    bool move_available(const Point& from, const Point& to) const {
        if (not is_point_inside(from)) {
            throw std::out_of_range("");
        }
        if (not is_point_inside(to)) {
            return false;
        }
        return move_available_impl<Piece>(from, to);
    }

private:
    template <int Piece, std::enable_if_t<std::abs(Piece) == Knight>* = nullptr>
    bool move_available_impl(const Point& from, const Point& to) const {
        if (std::abs(from.r - to.r) == 1) {
            return std::abs(from.c - to.c) == 2;
        }
        if (std::abs(from.r - to.r) == 2) {
            return std::abs(from.c - to.c) == 1;
        }
        return false;
    }
    template <int Piece, std::enable_if_t<std::abs(Piece) == Rook>* = nullptr>
    bool move_available_impl(const Point& from, const Point& to) const {
        return is_vert_reachable(from, to) || is_hor_reachabe(from, to);
    }

    template <int Piece, std::enable_if_t<std::abs(Piece) == Bishop>* = nullptr>
    bool move_available_impl(const Point& from, const Point& to) const {
        return is_subdiag_reachable(from, to) || is_diag_reachable(from, to);
    }

    template <int Piece, std::enable_if_t<std::abs(Piece) == Queen>* = nullptr>
    bool move_available_impl(const Point& from, const Point& to) const {
        return move_available_impl<Rook>(from, to) || move_available_impl<Bishop>(from, to);
    }


    bool is_in_range(int x) const;
    bool is_point_inside(const Point& p) const;

    bool is_subdiag_reachable(const Point& from, const Point& to) const;
    bool is_diag_reachable(const Point& from, const Point& to) const;
    bool is_hor_reachabe(const Point& from, const Point& to) const;
    bool is_vert_reachable(const Point& from, const Point& to) const;

    const int N;
    std::vector<Piece> chessboard;
};

void Chessboard::print(std::ostream& s) const {
    int r;
    for (r = 0; r < N - 1; ++r) {
        for (int c = 0; c < N; ++c) {
            switch (get(r, c)) {
            case WhiteKing:
                s << "♔";
                break;
            case WhiteQueen:
                s << "♕";
                break;
            case WhiteRook:
                s << "♖";
                break;
            case WhiteBishop:
                s << "♗";
                break;
            case WhiteKnight:
                s << "♘";
                break;
            case WhitePawn:
                s << "♙";
                break;
            case BlackKing:
                s << "♚";
                break;
            case BlackQueen:
                s << "♛";
                break;
            case BlackRook:
                s << "♜";
                break;
            case BlackBishop:
                s << "♝";
                break;
            case BlackKnight:
                s << "♞";
                break;
            case BlackPawn:
                s << "♟";
                break;
            case Nothing:
                s << ((r + c) % 2 == 0 ? "□" : "■");
                break;
            }
        }
        s << '\n';
    }
    for (int c = 0; c < N; ++c) {
        switch (get(r, c)) {
        case WhiteKing:
            s << "♔";
            break;
        case WhiteQueen:
            s << "♕";
            break;
        case WhiteRook:
            s << "♖";
            break;
        case WhiteBishop:
            s << "♗";
            break;
        case WhiteKnight:
            s << "♘";
            break;
        case WhitePawn:
            s << "♙";
            break;
        case BlackKing:
            s << "♚";
            break;
        case BlackQueen:
            s << "♛";
            break;
        case BlackRook:
            s << "♜";
            break;
        case BlackBishop:
            s << "♝";
            break;
        case BlackKnight:
            s << "♞";
            break;
        case BlackPawn:
            s << "♟";
            break;
        case Nothing:
            s << ((r + c) % 2 == 0 ? "□" : "■");
            break;
        }
    }
}

std::ostream& operator<<(std::ostream& s, const Chessboard& chessboard) {
    chessboard.print(s);
    return s;
}

Chessboard::Piece& Chessboard::get(int r, int c) { return chessboard[r * N + c]; }

Chessboard::Piece Chessboard::get(int r, int c) const { return chessboard[r * N + c]; }

Chessboard::Piece& Chessboard::get(const Point& p) { return get(p.r, p.c); }

Chessboard::Piece Chessboard::get(const Point& p) const { return get(p.r, p.c); }

bool Chessboard::is_in_range(int x) const { return x >= 0 && x < N; }

bool Chessboard::is_point_inside(const Point& p) const {
    return is_in_range(p.r) && is_in_range(p.c);
}

bool Chessboard::is_subdiag_reachable(const Point& from, const Point& to) const {
    if (from.r + from.c != to.r + to.c) {
        return false;
    }
    if (to.c > from.c) {
        for (int c = from.c + 1; c < to.c; ++c) {
            if (get(from.r + to.c - c, c) != Chessboard::Nothing) {
                return false;
            }
        }
    } else {
        for (int c = from.c - 1; c > to.c; --c) {
            if (get(from.r + c - to.c, c) != Chessboard::Nothing) {
                return false;
            }
        }
    }
    return true;
}

bool Chessboard::is_diag_reachable(const Point& from, const Point& to) const {
    if (from.r - from.c != to.r - to.c) {
        return false;
    }
    if (to.c > from.c) {
        for (int c = from.c + 1; c < to.c; ++c) {
            if (get(from.r + c - from.c, c) != Chessboard::Nothing) {
                return false;
            }
        }
    } else {
        for (int c = from.c - 1; c > to.c; --c) {
            if (get(from.r + c - from.c, c) != Chessboard::Nothing) {
                return false;
            }
        }
    }
    return true;
}

bool Chessboard::is_hor_reachabe(const Point& from, const Point& to) const {
    if (to.r != from.r) {
        return false;
    }
    if (to.c > from.c) {
        for (int c = from.c + 1; c < to.c; ++c) {
            if (get(to.r, c) != Chessboard::Nothing) {
                return false;
            }
        }
    } else {
        for (int c = from.c - 1; c > to.c; --c) {
            if (get(to.r, c) != Chessboard::Nothing) {
                return false;
            }
        }
    }
    return true;
}

bool Chessboard::is_vert_reachable(const Point& from, const Point& to) const {
    if (to.c != from.c) {
        return false;
    }
    if (to.r > from.r) {
        for (int r = from.r + 1; r < to.r; ++r) {
            if (get(r, to.c) != Chessboard::Nothing) {
                return false;
            }
        }
    } else {
        for (int r = from.r - 1; r > to.r; --r) {
            if (get(r, to.c) != Chessboard::Nothing) {
                return false;
            }
        }
    }
    return true;
}

} // namespace olymp
