//
//  main.cpp
//  Extended2.0
//
//  Created by Chuyue Zhang on 12/23/15.
//  Copyright © 2015 Camille Zhang. All rights reserved.
//

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
using namespace std;

const int MAXROWS = 20;
const int MAXCOLS = 30;
const int MAXROBOTS = 100;
const int MAXSUPERBOTS = 10;

const int UP    = 0;
const int DOWN  = 1;
const int LEFT  = 2;
const int RIGHT = 3;

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
int randInt(int min, int max);
void clearScreen();

class Arena;

class Robot
{
public:
    Robot(Arena *ap, int r, int c);
    int row() const;
    int col() const;
    void move();
    bool getAttacked(int dir);
    int getHealth() const;
    
private:
    Arena* m_arena;
    int m_row;
    int m_col;
    int m_health;
};

class Superbot
{
public:
    Superbot(Arena *ap, int r, int c);
    int row() const;
    int col() const;
    void move();
    bool getAttacked(int dir);
    int getHealth() const;
    
private:
    Arena* m_arena;
    int m_row;
    int m_col;
    int m_health;
};

class Player
{
public:
    Player(Arena *ap, int r, int c);
    int row() const;
    int col() const;
    int age() const;
    bool isDead() const;
    
    void stand();
    void moveOrAttack(int dir);
    void setDead();
    
private:
    Arena* m_arena;
    int m_row;
    int m_col;
    int m_age;
    bool m_dead;
};

class Arena
{
public:
    // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     robotCount() const;
    int     superbotCount() const;
    int     nRobotsAt(int r, int c) const;
    int     nSuperbotsAt(int r, int c) const;
    bool    determineNewPosition(int& r, int& c, int dir) const;
    void    display() const;
    int     numRobot(int r, int c) const;
    int     numSuperbot(int r, int c) const;
    
    // Mutators
    bool   addRobot(int r, int c);
    bool   addSuperbot(int r, int c);
    bool   addPlayer(int r, int c);
    bool   attackBotAt(int r, int c, int dir);
    bool   moveRobots();
    bool   moveSuperbots();
    
private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Robot*  m_robots[MAXROBOTS];
    Superbot*  m_superbots[MAXSUPERBOTS];
    int     m_nRobots;
    int     m_nSuperbots;
};

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nRobots, int nSuperbots);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
};

///////////////////////////////////////////////////////////////////////////
//  Robot implementation
///////////////////////////////////////////////////////////////////////////


Robot::Robot(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** A robot must be in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "***** Robot created with invalid coordinates (" << r << ","
        << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_health = 5;
}

int Robot::row() const
{
    return m_row;
}

int Robot::col() const
{
    return m_col;
}

int Robot:: getHealth() const
{
    return m_health;
}

void Robot::move()
{
    // Attempt to move in a random direction; if we can't move, don't move
    int dir = randInt(0, 3);  // dir is now UP, DOWN, LEFT, or RIGHT
    m_arena -> determineNewPosition(m_row, m_col, dir);
}

bool Robot::getAttacked (int dir)
{
    switch (dir)
    {
        case UP:
            if (m_row +3 == m_arena -> player() -> row())
            {
                if (m_arena -> determineNewPosition(m_row, m_col, dir))
                    m_health -= 1;
                else
                    m_health -= 2;
            }
            else if (m_row +2 == m_arena -> player() -> row())
            {
                if (m_arena -> determineNewPosition(m_row, m_col, dir))
                    m_health -= 2;
                else
                    m_health -= 4;
            }
            else if (m_row +1 == m_arena -> player() -> row())
            {
                if (m_arena -> determineNewPosition(m_row, m_col, dir))
                    m_health -= 3;
                else
                    m_health -= 6;
            }
            break;
        case DOWN:
            if (m_row -3 == m_arena -> player() -> row())
            {
                if (m_arena -> determineNewPosition(m_row, m_col, dir))
                    m_health -= 1;
                else
                    m_health -= 2;
            }
            else if (m_row -2 == m_arena -> player() -> row())
            {
                if (m_arena -> determineNewPosition(m_row, m_col, dir))
                    m_health -= 2;
                else
                    m_health -= 4;
            }
            else if (m_row -1 == m_arena -> player() -> row())
            {
                if (m_arena -> determineNewPosition(m_row, m_col, dir))
                    m_health -= 3;
                else
                    m_health -= 6;
            }
            break;
        case LEFT:
            if (m_col + 3 == m_arena -> player() -> col())
            {
                if (m_arena -> determineNewPosition(m_row, m_col, dir))
                    m_health -= 1;
                else
                    m_health -= 2;
            }
            else if (m_col + 2 == m_arena -> player() -> col())
            {
                if (m_arena -> determineNewPosition(m_row, m_col, dir))
                    m_health -= 2;
                else
                    m_health -= 4;
            }
            else if (m_col + 1 == m_arena -> player() -> col())
            {
                if (m_arena -> determineNewPosition(m_row, m_col, dir))
                    m_health -= 3;
                else
                    m_health -= 6;
            }
            break;
        case RIGHT:
            if (m_col - 3 == m_arena -> player() -> col())
            {
                if (m_arena -> determineNewPosition(m_row, m_col, dir))
                    m_health -= 1;
                else
                    m_health -= 2;
            }
            else if (m_col - 2 == m_arena -> player() -> col())
            {
                if (m_arena -> determineNewPosition(m_row, m_col, dir))
                    m_health -= 2;
                else
                    m_health -= 4;
            }
            else if (m_col - 1 == m_arena -> player() -> col())
            {
                if (m_arena -> determineNewPosition(m_row, m_col, dir))
                    m_health -= 3;
                else
                    m_health -= 6;
            }
            break;
    }
    if (m_health <= 0)
        return true;
    return false;
}

///////////////////////////////////////////////////////////////////////////
//  Superbot implementation
///////////////////////////////////////////////////////////////////////////

Superbot::Superbot(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** A superbot must be in some Arena!" << endl;
        exit(1);
    }
    if ( r < 1|| r > ap -> rows() || c < 1 || c> ap-> cols())
    {
        cout<< "***** Superbot created with invalid coordinates (" << r <<"," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_health = 5;
}

int Superbot::row() const
{
    return m_row;
}

int Superbot::col() const
{
    return m_col;
}

int Superbot::getHealth() const
{
    return m_health;
}

void Superbot::move()
{
    if (m_row < m_arena -> player() -> row())
    {
        m_arena -> determineNewPosition(m_row, m_col, DOWN);
    }
    else if (m_row > m_arena -> player() -> row())
    {
        m_arena -> determineNewPosition(m_row, m_col, UP);
    }
    else if (m_col > m_arena -> player() -> col())
    {
        m_arena -> determineNewPosition(m_row, m_col, LEFT);
    }
    else if (m_col < m_arena -> player() -> col())
    {
        m_arena -> determineNewPosition(m_row, m_col, RIGHT);
    }

}

bool Superbot::getAttacked (int dir)
{
    switch (dir)
    {
        case UP:
            if (m_row +3 == m_arena -> player() -> row())
            {
                if (m_arena -> determineNewPosition(m_row, m_col, dir))
                    m_health -= 1;
                else
                    m_health -= 2;
            }
            else if (m_row +2 == m_arena -> player() -> row())
            {
                if (m_arena -> determineNewPosition(m_row, m_col, dir))
                    m_health -= 2;
                else
                    m_health -= 4;
            }
            else if (m_row +1 == m_arena -> player() -> row())
            {
                if (m_arena -> determineNewPosition(m_row, m_col, dir))
                    m_health -= 3;
                else
                    m_health -= 6;
            }
            break;
        case DOWN:
            if (m_row -3 == m_arena -> player() -> row())
            {
                if (m_arena -> determineNewPosition(m_row, m_col, dir))
                    m_health -= 1;
                else
                    m_health -= 2;
            }
            else if (m_row -2 == m_arena -> player() -> row())
            {
                if (m_arena -> determineNewPosition(m_row, m_col, dir))
                    m_health -= 2;
                else
                    m_health -= 4;
            }
            else if (m_row -1 == m_arena -> player() -> row())
            {
                if (m_arena -> determineNewPosition(m_row, m_col, dir))
                    m_health -= 3;
                else
                    m_health -= 6;
            }
            break;
        case LEFT:
            if (m_col + 3 == m_arena -> player() -> col())
            {
                if (m_arena -> determineNewPosition(m_row, m_col, dir))
                    m_health -= 1;
                else
                    m_health -= 2;
            }
            else if (m_col + 2 == m_arena -> player() -> col())
            {
                if (m_arena -> determineNewPosition(m_row, m_col, dir))
                    m_health -= 2;
                else
                    m_health -= 4;
            }
            else if (m_col + 1 == m_arena -> player() -> col())
            {
                if (m_arena -> determineNewPosition(m_row, m_col, dir))
                    m_health -= 3;
                else
                    m_health -= 6;
            }
            break;
        case RIGHT:
            if (m_col - 3 == m_arena -> player() -> col())
            {
                if (m_arena -> determineNewPosition(m_row, m_col, dir))
                    m_health -= 1;
                else
                    m_health -= 2;
            }
            else if (m_col - 2 == m_arena -> player() -> col())
            {
                if (m_arena -> determineNewPosition(m_row, m_col, dir))
                    m_health -= 2;
                else
                    m_health -= 4;
            }
            else if (m_col - 1 == m_arena -> player() -> col())
            {
                if (m_arena -> determineNewPosition(m_row, m_col, dir))
                    m_health -= 3;
                else
                    m_health -= 6;
            }
            break;
    }
    if (m_health <= 0)
        return true;
    return false;
}

///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
        << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}

int Player::row() const
{
    return m_row;
}

int Player::col() const
{
    return m_col;
}

int Player::age() const
{
    return m_age;
}

void Player::stand()
{
    m_age++;
}

void Player::moveOrAttack(int dir)
{
    switch (dir)
    {
        case UP:
            if (m_arena -> nRobotsAt(m_row-1, m_col) > 0 || m_arena -> nSuperbotsAt(m_row-1, m_col) > 0)
            {
                m_arena -> attackBotAt(m_row-1, m_col, dir);
            }
            else if (m_arena -> nRobotsAt(m_row-2, m_col) > 0 || m_arena -> nSuperbotsAt(m_row-2, m_col) > 0)
            {
                m_arena -> attackBotAt(m_row-2, m_col, dir);
            }
            else if (m_arena -> nRobotsAt(m_row-3, m_col) > 0 || m_arena -> nSuperbotsAt(m_row-3, m_col) > 0)
            {
                m_arena -> attackBotAt(m_row-3, m_col, dir);
            }
            else
            {
                 m_arena -> determineNewPosition(m_row, m_col, dir);
            }
            break;
        case DOWN:
            if (m_arena -> nRobotsAt(m_row+1, m_col) > 0 || m_arena -> nSuperbotsAt(m_row+1, m_col) > 0)
            {
                m_arena -> attackBotAt(m_row+1, m_col, dir);
            }
            else if (m_arena -> nRobotsAt(m_row+2, m_col) > 0 || m_arena -> nSuperbotsAt(m_row+2, m_col) > 0)
            {
                m_arena -> attackBotAt(m_row+2, m_col, dir);
            }
            else if (m_arena -> nRobotsAt(m_row+3, m_col) > 0 || m_arena -> nSuperbotsAt(m_row+3, m_col) > 0)
            {
                m_arena -> attackBotAt(m_row+3, m_col, dir);
            }
            else
            {
                m_arena -> determineNewPosition(m_row, m_col, dir);
            }
            break;
        case LEFT:
            if (m_arena -> nRobotsAt (m_row, m_col -1 ) > 0 || m_arena -> nSuperbotsAt(m_row, m_col -1) > 0)
            {
                m_arena -> attackBotAt (m_row, m_col-1, dir);
            }
            else if (m_arena -> nRobotsAt(m_row,m_col - 2) > 0 || m_arena -> nSuperbotsAt(m_row, m_col -2) > 0)
            {
                m_arena -> attackBotAt (m_row, m_col -2, dir);
            }
            else if (m_arena -> nRobotsAt(m_row, m_col-3) > 0 || m_arena -> nSuperbotsAt(m_row, m_col -3) > 0)
            {
                m_arena -> attackBotAt (m_row, m_col - 3, dir);
            }
            else
            {
                m_arena -> determineNewPosition(m_row, m_col, dir);
            }
            break;
        case RIGHT:
            if (m_arena -> nRobotsAt (m_row, m_col +1 ) > 0 || m_arena -> nSuperbotsAt(m_row, m_col +1) > 0)
            {
                m_arena -> attackBotAt (m_row, m_col+1, dir);
            }
            else if (m_arena -> nRobotsAt(m_row,m_col + 2) > 0 || m_arena -> nSuperbotsAt(m_row, m_col +2) > 0)
            {
                m_arena -> attackBotAt (m_row, m_col +2, dir);
            }
            else if (m_arena -> nRobotsAt(m_row, m_col+3) > 0 || m_arena -> nSuperbotsAt(m_row, m_col +3) > 0)
            {
                m_arena -> attackBotAt (m_row, m_col + 3, dir);
            }
            else
            {
                m_arena -> determineNewPosition(m_row, m_col, dir);
            }
            break;

    }
    m_age++;
}

bool Player::isDead() const
{
    if (!m_dead)
        return false;
    return true;
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Arena implementations
///////////////////////////////////////////////////////////////////////////

Arena::Arena(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
        << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nRobots = 0;
    m_nSuperbots = 0;
}

Arena::~Arena()
{
    delete m_player;
    for (int i = 0 ; i < m_nRobots; i ++)
        delete m_robots[i];
    for (int k = 0; k < m_nSuperbots; k++)
        delete m_superbots[k];
}

int Arena::rows() const
{
    return m_rows;
}

int Arena::cols() const
{
    return m_cols;
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::robotCount() const
{
    return m_nRobots;
}

int Arena::superbotCount() const
{
    return m_nSuperbots;
}

int Arena::nRobotsAt(int r, int c) const
{
    int count = 0;
    for (int i = 0; i < m_nRobots; i ++ )
    {
        if ( r == m_robots[i] -> row() && c == m_robots[i] -> col())
            count ++;
    }
    return count;
}

int Arena::nSuperbotsAt(int r, int c) const
{
    int count = 0;
    for (int k = 0 ; k < m_nSuperbots; k ++)
    {
        if (r == m_superbots[k] -> row() && c == m_superbots[k] -> col())
            count ++;
    }
    return count;
}

int Arena::numRobot(int r, int c) const
{
    for (int i = 0; i < m_nRobots; i ++ )
    {
        if ( r == m_robots[i] -> row() && c == m_robots[i] -> col())
            return i;
    }
    return -1;

}

int Arena::numSuperbot(int r, int c) const
{
    for (int k = 0 ; k < m_nSuperbots; k++)
    {
        if ( r == m_superbots[k] -> row() && c == m_superbots[k] -> col())
            return k;
    }
    return -1;
}

bool Arena::determineNewPosition(int& r, int& c, int dir) const
{
    switch (dir)
    {
        case UP:
            if (r-1 >= 1)
            {
                r--;
                break;
            }
            return false;
        case DOWN:
            if (r+1 <= m_rows)
            {
                r++;
                break;
            }
            return false;
        case LEFT:
            if (c-1 >= 1)
            {
                c--;
                break;
            }
            return false;
        case RIGHT:
            if (c+1 <= m_cols)
            {
                c++;
                break;
            }
            return false;
    }
    return true;
}


void Arena::display() const
{
    // Position (row,col) in the arena coordinate system is represented in
    // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';
    
    for (r = 0; r < rows(); r++)
        for (c = 0 ; c < cols(); c++)
        {
            if (nRobotsAt(r+1, c+1) > 0)
            {
                if (nRobotsAt(r+1, c+1) == 1 && m_robots[numRobot(r+1,c+1)]->getHealth()>2)
                    grid[r][c] = 'R';
                else if (nRobotsAt(r+1, c+1) == 1 && m_robots[numRobot(r+1,c+1)]->getHealth()<=2)
                    grid[r][c] = 'r';
                else
                {
                    char n = '0' + nRobotsAt(r+1,c+1);
                    grid[r][c] = n;
                }
            }
            if (nSuperbotsAt(r+1, c+1) > 0)
            {
                if (nSuperbotsAt(r+1, c+1) == 1 && m_superbots[numSuperbot(r+1, c+1)] -> getHealth() > 2)
                    grid[r][c] = 'S';
                else if (nSuperbotsAt(r+1, c+1) == 1 && m_superbots[numSuperbot(r+1, c+1)] -> getHealth() <= 2)
                    grid[r][c] = 's';
                else
                {
                    char n = '0' + nSuperbotsAt(r+1, c+1);
                    grid[r][c] = n;
                }
            }
        }
    
    // Indicate player's position
    if (m_player != nullptr)
    {
        char& gridChar = grid[m_player->row()-1][m_player->col()-1];
        if (gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
    }
    
    // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;
    
    // Write message, robot, and player info
    cout << endl;
    cout << "There are " << robotCount() << " robots and " << superbotCount() << " superbots remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isDead())
            cout << "The player is dead." << endl;
    }
}

bool Arena::addRobot(int r, int c)
{
    // If MAXROBOTS have already been added, return false.  Otherwise,
    // dynamically allocate a new robot at coordinates (r,c).  Save the
    // pointer to the newly allocated robot and return true.
    
    if (m_nRobots < MAXROBOTS)
    {
        m_robots[m_nRobots] = new Robot(this, r, c);
        m_nRobots++;
        return true;
    }
    return false;
}

bool Arena::addSuperbot(int r, int c)
{
    if (m_nSuperbots < MAXSUPERBOTS)
    {
        m_superbots[m_nSuperbots] = new Superbot(this, r, c);
        m_nSuperbots ++;
        return true;
    }
    return false;
}

bool Arena::addPlayer(int r, int c)
{
    // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;
    
    // Dynamically allocate a new Player and add it to the arena
    m_player = new Player(this, r, c);
    return true;
}

bool Arena::attackBotAt(int r, int c, int dir)
{
    for (int k = 0 ; k < m_nRobots; k ++ )
    {
        if ( m_robots[k] -> row() == r && m_robots[k] -> col() == c)
        {
            if ( m_robots[k] -> getAttacked(dir))
            {
                delete m_robots[k];
                for (int i = k ; i < m_nRobots-1; i ++)
                {
                    m_robots[i] = m_robots[i+1];
                }
                m_nRobots--;
                return true;
            }
            
        }
    }
    for (int m = 0 ; m < m_nSuperbots; m++ )
    {
        if (m_superbots[m] -> row() == r && m_superbots[m] -> col() == c)
        {
            if (m_superbots[m] -> getAttacked(dir))
            {
                delete m_superbots[m];
                for (int n=m; n< m_nSuperbots -1; n++)
                {
                    m_superbots[n] = m_superbots[n+1];
                }
                m_nSuperbots--;
                return true;
            }
        }
    }
    return false;
}


bool Arena::moveRobots()
{
    for (int k = 0; k < m_nRobots; k++)
    {
        m_robots[k] -> move();
        if ( m_robots[k] -> row() == m_player -> row() && m_robots[k] -> col()== m_player -> col())
        {
            m_player -> setDead();
            return false;
        }
    }
    // return true if the player is still alive, false otherwise
    return true;
}

bool Arena::moveSuperbots()
{
    for (int i = 0 ; i < m_nSuperbots; i++)
    {
        m_superbots[i] -> move();
        if (m_superbots[i] -> row() == m_player -> row() && m_superbots[i] -> col() == m_player -> col())
        {
            m_player -> setDead();
            return false;
        }
    }
    return true;
}
    
///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nRobots, int nSuperbots)
{
    if (nRobots < 0)
    {
        cout << "***** Cannot create Game with negative number of robots!" << endl;
        exit(1);
    }
    if (nRobots > MAXROBOTS)
    {
        cout << "***** Trying to create Game with " << nRobots
        << " robots; only " << MAXROBOTS << " are allowed!" << endl;
        exit(1);
    }
    if (nSuperbots < 0)
    {
        cout << "***** Cannot create Game with negative number of superbots!" << endl;
        exit(1);
    }
    if (nSuperbots > MAXSUPERBOTS)
    {
        cout << "***** Trying to create Game with " << nSuperbots
        << " superbots; only " << MAXSUPERBOTS << " are allowed!" << endl;
        exit(1);

    }
    if (rows == 1  &&  cols == 1  &&  (nRobots > 0 || nSuperbots > 0))
    {
        cout << "***** Cannot create Game with nowhere to place the robots and superbots!" << endl;
        exit(1);
    }
    
    // Create arena
    m_arena = new Arena(rows, cols);
    
    // Add player
    int rPlayer = randInt(1, rows);
    int cPlayer = randInt(1, cols);
    m_arena->addPlayer(rPlayer, cPlayer);
    
    int rRobot = 0;
    int cRobot = 0; // CHECK!
    // Populate with robots
    while (nRobots > 0)
    {
        int rRobot = randInt(1, rows);
        int cRobot = randInt(1, cols);
        // Don't put a robot where the player is
        if (rRobot == rPlayer  &&  cRobot == cPlayer)
            continue;
        m_arena->addRobot(rRobot, cRobot);
        nRobots--;
    }
    
    while (nSuperbots > 0)
    {
        int rSuperbot = randInt(1, rows);
        int cSuperbot = randInt(1, cols);
        if ( (rSuperbot == rPlayer && cSuperbot == cPlayer )|| (rSuperbot == rRobot && cSuperbot == cRobot))
            continue;
        m_arena -> addSuperbot(rSuperbot, cSuperbot);
        nSuperbots --;
    }
}

Game::~Game()
{
    delete m_arena;
}

void Game::play()
{
    Player* p = m_arena->player();
    if (p == nullptr)
    {
        m_arena->display();
        return;
    }
    do
    {
        m_arena->display();
        cout << endl;
        cout << "Move (u/d/l/r//q): ";
        string action;
        getline(cin,action);
        if (action.size() == 0)  // player stands
            p->stand();
        else
        {
            switch (action[0])
            {
                default:   // if bad move, nobody moves
                    cout << '\a' << endl;  // beep
                    continue;
                case 'q':
                    return;
                case 'u':
                case 'd':
                case 'l':
                case 'r':
                    p->moveOrAttack(decodeDirection(action[0]));
                    break;
            }
        }
        m_arena->moveSuperbots();
        m_arena ->moveRobots();
        
        
        
    } while ( ! m_arena->player()->isDead()  && ( m_arena->robotCount() > 0 || m_arena -> superbotCount() > 0));
    m_arena->display();
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir)
{
    switch (dir)
    {
        case 'u':  return UP;
        case 'd':  return DOWN;
        case 'l':  return LEFT;
        case 'r':  return RIGHT;
    }
    return -1;  // bad argument passed in!
}

// Return a random int from min to max, inclusive
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rd;
    static mt19937 generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(10, 15, 4, 2);
    
    // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANY CODE BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++ UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                               &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif


