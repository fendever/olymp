#pragma once
#include <algorithm>
#include <iosfwd>
#include <stdexcept>
#include <type_traits>
#include <vector>

class Chessboard {
public:
    Chessboard(int N)
        : N(N)
        , chessboard(N * N)
    {
    }

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

    const char* to_char(Chessboard::Piece piece) {
        switch (piece) {
        case WhiteKing:
            return "♔";
        case WhiteQueen:
            return "♕";
        case WhiteRook:
            return "♖";
        case WhiteBishop:
            return "♗";
        case WhiteKnight:
            return "♘";
        case WhitePawn:
            return "♙";
        case BlackKing:
            return "♚";
        case BlackQueen:
            return "♛";
        case BlackRook:
            return "♜";
        case BlackBishop:
            return "♝";
        case BlackKnight:
            return "♞";
        case BlackPawn:
            return "♟";
        }
    }


    Piece &get(int r, int c)
    {
        return chessboard[r * N + c];
    }

    Piece get(int r, int c) const
    {
        return chessboard[r * N + c];
    }

    Piece &get(const Point &p)
    {
        return get(p.r, p.c);
    }

    Piece get(const Point &p) const
    {
        return get(p.r, p.c);
    }

    void print(std::ostream &s) const
    {
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                s << get(r, c);
            }
            s << '\n';
        }
    }

    template <int Piece>
    bool move_available(const Point &from, const Point &to) const
    {
        if (not is_point_inside(from) || not is_point_inside(to)) {
            throw std::out_of_range("");
        }
        return move_available_impl<Piece>(from, to);
    }

private:
    template <int Piece, std::enable_if_t<std::abs(Piece) == Knight> * = nullptr>
    bool move_available_impl(const Point &from, const Point &to) const
    {
        if (std::abs(from.r - to.r) == 1) {
            return std::abs(from.c - to.c) == 2;
        }
        if (std::abs(from.r - to.r) == 2) {
            return std::abs(from.c - to.c) == 1;
        }
        return false;
    }

    template <int Piece, std::enable_if_t<std::abs(Piece) == Rook> * = nullptr>
    bool move_available_impl(const Point &from, const Point &to) const
    {
        return is_vert_reachable(from, to) || is_hor_reachabe(from, to);
    }

    template <int Piece, std::enable_if_t<std::abs(Piece) == Bishop> * = nullptr>
    bool move_available_impl(const Point &from, const Point &to) const
    {
        return is_subdiag_reachable(from, to) || is_diag_reachable(from, to);
    }

    template <int Piece, std::enable_if_t<std::abs(Piece) == Queen> * = nullptr>
    bool move_available_impl(const Point &from, const Point &to) const
    {
        return move_available_impl<Rook>(from, to) || move_available_impl<Bishop>(from, to);
    }

    bool is_in_range(int x) const
    {
        return x >= 0 && x < N;
    }

    bool is_point_inside(const Point &p) const
    {
        return is_in_range(p.r) && is_in_range(p.c);
    }

    bool is_subdiag_reachable(const Point &from, const Point &to) const
    {
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

    bool is_diag_reachable(const Point &from, const Point &to) const
    {
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

    bool is_hor_reachabe(const Point &from, const Point &to) const
    {
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

    bool is_vert_reachable(const Point &from, const Point &to) const
    {
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

    const int N;
    std::vector<Piece> chessboard;
};

