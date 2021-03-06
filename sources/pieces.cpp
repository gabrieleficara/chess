#include "chess.h"

int     c_board::move(c_king king, int coor[2], int dest[2])
{
    c_king     &kking = (board[coor[1]][coor[0]]->player == 1) ? pieces.w_kings : pieces.b_kings;

    if (abs(coor[0] - dest[0]) > 1 || abs(coor[1] - dest[1]) > 1)
    {
        if (c_check != 1)
        {
            board[coor[1]][coor[0]]->moved = 1;
            kking.pos[0] = dest[0];
            kking.pos[1] = dest[1];
        }
        return (0);
    }
    return (1);
}

int     c_board::move(c_queen queen, int coor[2], int dest[2])
{
    if (o_move(coor, dest) || v_move(coor, dest) || d_move(coor, dest))
        return (1);
    return (0);
}

int     c_board::move(c_knight knight, int coor[2], int dest[2])
{
    if (k_move(coor, dest))
        return (1);
    return (0);
}

int     c_board::move(c_bishop bishop, int coor[2], int dest[2])
{
    if (d_move(coor, dest))
    {
        if (c_check != 1)
            board[coor[1]][coor[0]]->moved = 1;
        return (1);
    }
    return (0);
}

int     c_board::move(c_rook rook, int coor[2], int dest[2])
{
    if (o_move(coor, dest) || v_move(coor, dest))
    {
        if (rook.moved == 3 && c_check != 1)
        {
            if (coor[0] == 0 &&
                coor[1] == rook.s_pos)
                board[coor[1]][coor[0]]->moved += 1;
            else if (coor[0] == 7 &&
                coor[1] == rook.s_pos)
                board[coor[1]][coor[0]]->moved += 2;
        }
        return (1);
    }
    return (0);
}

int     c_board::move(c_pawn pawn, int coor[2], int dest[2])
{
    if (p_move(pawn, coor, dest))
    {
        if (c_check != 1)
            board[coor[1]][coor[0]]->moved = 1;
        return (1);
    }
    return (0);
}

int     c_board::move(c_piece *ppiece, int coor[2], int dest[2])
{
    if (ppiece->name == 'K')
        return (move((ppiece->player == 1) ? pieces.w_kings : pieces.b_kings, coor, dest));
    if (ppiece->name == 'q')
        return (move((ppiece->player == 1) ? pieces.w_queens : pieces.b_queens, coor, dest));
    if (ppiece->name == 'k')
        return (move((ppiece->player == 1) ? pieces.w_knights : pieces.b_knights, coor, dest));
    if (ppiece->name == 'b')
        return (move((ppiece->player == 1) ? pieces.w_bishops : pieces.b_bishops, coor, dest));
    if (ppiece->name == 'r')
        return (move((ppiece->player == 1) ? pieces.w_rooks : pieces.b_rooks, coor, dest));
    if (ppiece->name == 'p')
        return (move((ppiece->player == 1) ? pieces.w_pawns : pieces.b_pawns, coor, dest));
    return (0);
}