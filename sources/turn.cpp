#include "chess.h"

int     c_board::retrive_data(int coor[2], int turn)
{
    std::string command;

    while (1)
    {
        std::getline(std::cin, command);
        if (command[0] && command[1] && !command[2])
            if (command[0] >= 'a' && command[0] <= 'h' && command[1] >= '1' && command[1] < '9')
            {
                coor[0] = command[0] - 97;
                coor[1] = command[1] - 49;
                if (board[coor[1]][coor[0]]->player == turn)
                    break;
            }
        if (!stop_game(command, turn))
            return (0);
        std::cout << "i don't understand, can you repeat please?" << endl;
    }
    return (1);
}

int c_board::end_move(int coor[2], int dest[2], int cas)
{
    int ret;

    ret = 1;
    if (board[dest[1]][dest[0]]->name == 'K')
        ret = 2;
    if (cas != 1)
    {
        board[dest[1]][dest[0]] = board[coor[1]][coor[0]];
        board[coor[1]][coor[0]] = &(pieces.empty);
        if (board[dest[1]][dest[0]]->name == 'p' &&
            (dest[1] == 0 || dest[1] == 7) && ret != 2)
            transform(dest);
    }
    print_board();
    check(board[dest[1]][dest[0]]->player);
    return (ret);
}

int c_board::move(int coor[2], int turn)
{
    int dest[2];
    int cas;
    std::string command;

    while (1)
    {
        std::getline(std::cin, command);
        if (command[0] && command[1] && !command[2])
            if (command[0] >= 'a' && command[0] <= 'h' &&
            command[1] >= '1' && command[1] < '9')
            {
                dest[0] = command[0] - 97;
                dest[1] = command[1] - 49;
                if ((board[dest[1]][dest[0]]->player != turn &&
                    move(board[coor[1]][coor[0]], coor, dest))
                    || (cas = cast(coor, dest, turn)))
                    break;
            }
        if (!command.compare("back"))
        {
            print_board();
            return (0);
        }
        std::cout << "i don't understand, can you repeat please?" << endl;
    }
    return (end_move(coor, dest, cas));
}

int c_board::turn(int turn, std::string player[2])
{
    int i;
    int coor[2];

    i = 0;
    while (i == 0)
    {
        std::cout << "Player " << player[turn - 1] << " choose a piece: " << endl;
        if (!retrive_data(coor, turn))
            return (0);
        std::cout << "where do you want to move?" << endl;
        if ((i = move(coor, turn)) == 2)
        {
            std::cout << "player " << ((turn == 1) ? 2 : 1) << " wins!" << endl; 
            return (0);
        }
        if (en_p[2] > 0)
            en_p[2]--;
    }
    return ((turn == 1) ? 2 : 1);
}