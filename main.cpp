#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>

class CheckerBoard
{
public:

    enum boardPieces
    {
        BLANK =0,
        WHITE = 1,
        WHITE_KING = 2,
        BLACK = 3,
        BLACK_KING = 4,
        EMPTY = 5
    };
    int inputParser(char k)
    {
        switch (k)
        {
            case ('a' | 'A'):
                return 0;
                break;
            case ('b' | 'B'):
                return 1;
                break;
            case ('c' | 'C'):
                return 2;
                break;
            case ('d' | 'D'):
                return 3;
                break;
            case ('e' | 'E'):
                return 4;
                break;
            case ('f' | 'F'):
                return 5;
                break;
            case ('g' | 'G'):
                return 6;
                break;
            case ('h' | 'H'):
                return 7;
                break;
            case ('r' | 'R'):
                pickChecker();
                break;
            default:
                std::cin.sync();
                 std::cin.clear();
                std::cin.ignore(999,'\n');
                return 8;
                break;
        }
            
    }
    void initBoard()
    {
        for(int i = 0; i<8; i++)
        {
            for(int j = 0; j<8; j++)
            {
                if((i+j)%2==0)
                {
                    board[i][j]=BLANK;
                }
                else
                {
                    board[i][j]=EMPTY;
                }
            }
        }
    }
    void printBoard()
    {
        std::cout<<" ";
          for(int i = 0; i<8; i++)
        {
            printf(" %c ",i+97);
        }
        std::cout<<std::endl;
        for(int i = 0; i<8; i++)
        {
            std::cout<<i;
            for(int j = 0; j<8; j++)
            {
                std::cout<<" ";
                switch(board[i][j])
                {
                case BLANK:
                    std::cout<<"*";
                    break;
                case BLACK:
                    std::cout<<"B";
                    break;
                case WHITE:
                    std::cout<<"W";
                    break;
                case EMPTY:
                    std::cout<<" ";
                    break;
                case WHITE_KING:
                    std::cout<<"H";
                    break;
                case BLACK_KING:
                    std::cout<<"G";
                    break;
                }
                std::cout<<" ";
            }
            std::cout<<std::endl;
        }
        std::cout<<" ";
      
        std::cout<<std::endl;
        std::cout<<std::endl;
        std::cout<<std::endl;
    }
    void placeCheckers()
    {
        for(int i = 0; i<3; i++)
        {
            for(int j = 0; j<8; j++)
            {
                if((i+j)%2==0)
                {
                    board[i][j]=BLACK;
                }
                else
                {
                    board[i][j]=EMPTY;
                }
            }
        }
        for(int i = 5; i<8; i++)
        {
            for(int j = 0; j<8; j++)
            {
                if((i+j)%2==0)
                {
                    board[i][j]=WHITE;
                }
                else
                {
                    board[i][j]=EMPTY;
                }
            }
        }
    }
    void pickChecker()
    {
        correct_checker=false;
        while(!correct_checker)
        {
            correct_input = false;
            if(bot==true)
            {
            while(!correct_input)
            {
            std::cout<<"Pick a checker"<<std::endl;
            std::cin>>y_proto;
            y_pos = inputParser(y_proto);
            std::cin>>x_pos;
                if(std::cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(999,'\n');
                    correct_input=false;
                    std::cout<<"WRONG INPUT!!"<<std::endl;
                }
                else if(x_pos<0 && x_pos>=8 && y_pos<0 && y_pos>=8)
                {
                    correct_input=false;
                    std::cout<<"WRONG INPUT!!"<<std::endl;
                }
                else
                {
                    correct_input=true;
                }
            }
                
            }
            else
            {
            x_pos=(std::rand()%8)+0;
            y_pos=(std::rand()%8)+0;
            }
            if(player==BLACK || player==BLACK_KING)
            {
                if(board[x_pos][y_pos]==BLACK || board[x_pos][y_pos]==BLACK_KING)
                {
                    correct_checker = true;
                    player=board[x_pos][y_pos];
                }
                else
                {
                    correct_checker = false;
                }
            }
            else if(player==WHITE || player == WHITE_KING)
            {
            if(board[x_pos][y_pos]==WHITE || board[x_pos][y_pos]==WHITE_KING)
                {
                    correct_checker = true;
                    player=board[x_pos][y_pos];
                }
                else
                {
                    correct_checker = false;
                }
        }
        }
    }
    void moveChecker()
    {
        correct_move=false;
        attempt=0;
        while(!correct_move)
        {
            correct_input=false;
            if(bot==true)
            {
            while(!correct_input)
            {
            std::cout<<"Choose destination"<<std::endl;
            std::cin>>y_proto;
            y_dest = inputParser(y_proto);
            std::cin>>x_dest;
                if(std::cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(999,'\n');
                    correct_input=false;
                    std::cout<<"WRONG INPUT!!"<<std::endl;
                }
                else if(x_dest<0 && x_dest>=8 && y_dest<0 && y_dest>=8)
                {
                    correct_input=false;
                    std::cout<<"WRONG INPUT!!"<<std::endl;
                }
                else
                {
                    correct_input=true;
                }
            }
            }
            else
            {
                x_dest=(std::rand()%8)+0;
                y_dest=(std::rand()%8)+0;
                //std::cout<<x_pos<<y_pos<<std::endl;
                //std::cout<<x_dest<<y_dest<<std::endl;
            }
            
            if(board[x_dest][y_dest]==BLANK)
            {
                if(player==BLACK && ( (x_dest-x_pos==1) && (abs(y_dest-y_pos)==1) ) )
                {
                    correct_move = true;
                    
                }
                else if( player==BLACK  &&  (abs(x_dest-x_pos)==2) && (abs(y_dest-y_pos)==2)  )
                {
                    correct_move = hitOn();
                    if(correct_move==true)
                    {
                        correct_move = consecutiveJump();
                    }
                }
                else if(player==BLACK_KING && ( (abs(x_dest-x_pos)<=8) && (abs(y_dest-y_pos)<=8) ) && (abs(x_dest-x_pos)) == (abs(y_dest-y_pos)) )
                {
                        correct_move = kingRush();
                        if(correct_move==true)
                        {
                            correct_move=consecutiveRush();
                        }
                }
                else if(player==WHITE && ( (x_dest-x_pos==-1) && (abs(y_dest-y_pos)==1) ) )
                {
                    correct_move = true;
                }
                else if(player==WHITE && ( (abs(x_dest-x_pos)==2) && (abs(y_dest-y_pos)==2) ) )
                {
                    correct_move = hitOn();
                    if(correct_move==true)
                    {
                        correct_move = consecutiveJump();
                    }
                }
                else if(player==WHITE_KING && ( (abs(x_dest-x_pos)<=8) && (abs(y_dest-y_pos)<=8) ) && (abs(x_dest-x_pos)) == (abs(y_dest-y_pos)) )
                {
                        correct_move = kingRush();
                        if(correct_move==true)
                        {
                            correct_move=consecutiveRush();
                        }
                }
            }
            else
            {
                attempt++;
                if(attempt>=13)
                {
                    pickChecker();
                }
            }
        }
        board[x_dest][y_dest]=board[x_pos][y_pos];
        board[x_pos][y_pos]=BLANK;
    }
    bool consecutiveRush()
    {
        if(king_correction!=0)
        {
           
            if(player==BLACK_KING)
            {
                for(int i =x_dest,j=y_dest;i>=0 && i<8 && j>=0 && j<8;i--,j--)
                {
                    if(board[i][j]==WHITE || board[i][j]==WHITE_KING)
                        {
                            if(board[i-1][j-1]!=BLANK)
                            {
                                return true;
                            }
                            if(board[i-1][j-1]==BLANK)
                            {
                                        board[x_dest][y_dest]=board[x_pos][y_pos];
                                        board[x_pos][y_pos]=BLANK;
                                        x_pos=x_dest;
                                        y_pos=y_dest;
                                        printBoard();
                                        return false;
                            }
                        }
                }
                for(int i =x_dest,j=y_dest;i>=0 && i<8 && j>=0 && j<8;i++,j++)
                {
                    if(board[i][j]==WHITE || board[i][j]==WHITE_KING)
                        {
                            if(board[i+1][j+1]!=BLANK)
                            {
                                return true;
                            }
                            if(board[i+1][j+1]==BLANK)
                            {
                                        board[x_dest][y_dest]=board[x_pos][y_pos];
                                        board[x_pos][y_pos]=BLANK;
                                        x_pos=x_dest;
                                        y_pos=y_dest;
                                        printBoard();
                                        return false;
                            }
                        }
                }
                for(int i =x_dest,j=y_dest;i>=0 && i<8 && j>=0 && j<8;i--,j++)
                {
                    if(board[i][j]==WHITE || board[i][j]==WHITE_KING)
                        {
                            if(board[i-1][j+1]!=BLANK)
                            {
                                return true;
                            }
                            if(board[i-1][j+1]==BLANK)
                            {
                                        board[x_dest][y_dest]=board[x_pos][y_pos];
                                        board[x_pos][y_pos]=BLANK;
                                        x_pos=x_dest;
                                        y_pos=y_dest;
                                        printBoard();
                                        return false;
                            }
                        }
                }
                for(int i =x_dest,j=y_dest;i>=0 && i<8 && j>=0 && j<8;i++,j--)
                {
                    if(board[i][j]==WHITE || board[i][j]==WHITE_KING)
                        {
                            if(board[i+1][j-1]!=BLANK)
                            {
                                return true;
                            }
                            if(board[i+1][j-1]==BLANK)
                            {
                                        board[x_dest][y_dest]=board[x_pos][y_pos];
                                        board[x_pos][y_pos]=BLANK;
                                        x_pos=x_dest;
                                        y_pos=y_dest;
                                        printBoard();
                                        return false;
                            }
                        }
                }
            }
            else if(player==WHITE_KING)
            {
                for(int i =x_dest,j=y_dest;i>=0 && i<8 && j>=0 && j<8;i--,j--)
                {
                    if(board[i][j]==BLACK || board[i][j]==BLACK_KING)
                        {
                            if(board[i-1][j-1]!=BLANK)
                            {
                                return true;
                            }
                            if(board[i-1][j-1]==BLANK)
                            {
                                        board[x_dest][y_dest]=board[x_pos][y_pos];
                                        board[x_pos][y_pos]=BLANK;
                                        x_pos=x_dest;
                                        y_pos=y_dest;
                                        printBoard();
                                        return false;
                            }
                        }
                }
                for(int i =x_dest,j=y_dest;i>=0 && i<8 && j>=0 && j<8;i++,j++)
                {
                    if(board[i][j]==BLACK || board[i][j]==BLACK_KING)
                        {
                            if(board[i+1][j+1]!=BLANK)
                            {
                                return true;
                            }
                            if(board[i+1][j+1]==BLANK)
                            {
                                        board[x_dest][y_dest]=board[x_pos][y_pos];
                                        board[x_pos][y_pos]=BLANK;
                                        x_pos=x_dest;
                                        y_pos=y_dest;
                                        printBoard();
                                        return false;
                            }
                        }
                }
                for(int i =x_dest,j=y_dest;i>=0 && i<8 && j>=0 && j<8;i--,j++)
                {
                    if(board[i][j]==BLACK || board[i][j]==BLACK_KING)
                        {
                            if(board[i-1][j+1]!=BLANK)
                            {
                                return true;
                            }
                            if(board[i-1][j+1]==BLANK)
                            {
                                        board[x_dest][y_dest]=board[x_pos][y_pos];
                                        board[x_pos][y_pos]=BLANK;
                                        x_pos=x_dest;
                                        y_pos=y_dest;
                                        printBoard();
                                        return false;
                            }
                        }
                }
                for(int i =x_dest,j=y_dest;i>=0 && i<8 && j>=0 && j<8;i++,j--)
                {
                    if(board[i][j]==BLACK || board[i][j]==BLACK_KING)
                        {
                            if(board[i+1][j-1]!=BLANK)
                            {
                                return true;
                            }
                            if(board[i+1][j-1]==BLANK)
                            {
                                        board[x_dest][y_dest]=board[x_pos][y_pos];
                                        board[x_pos][y_pos]=BLANK;
                                        x_pos=x_dest;
                                        y_pos=y_dest;
                                        printBoard();
                                        return false;
                            }
                        }
                }
            }
        
        }
        return true;
    }
    bool kingRush()
    {
        king_correction=0;
        if(player==BLACK_KING)
        {
            if(x_pos+y_pos>x_dest+y_dest)
            {
                for(int i = x_pos,j=y_pos;i>=0 && i<8 && j>=0 && j<8;i--,j--)
                {
                    if(board[i][j]==WHITE || board[i][j]==WHITE_KING)
                    {
                        if(board[i-1][j-1]!=BLANK)
                        {
                            return false;
                        }
                        else if(board[i-1][j-1]==BLANK)
                        {
                            board[i][j]=BLANK;
                            i=x_pos;
                            j=y_pos;
                            king_correction++;
                        }
                    }
                }
                return true;
            }
            else if(x_pos+y_pos<x_dest+y_dest)
            {
                for(int i = x_pos,j=y_pos;i>=0 && i<8 && j>=0 && j<8;i++,j++)
                {
                    if(board[i][j]==WHITE || board[i][j]==WHITE_KING)
                    {
                        if(board[i+1][j+1]!=BLANK)
                        {
                            return false;
                        }
                        else if(board[i+1][j+1]==BLANK)
                        {
                            board[i][j]=BLANK;
                            i=x_pos;
                            j=y_pos;
                            king_correction++;
                        }
                    }
                }
                return true;
            }
            else if(x_pos+y_pos==x_dest+y_dest && (y_pos<y_dest))
            {
                for(int i = x_pos,j=y_pos;i>=0 && i<8 && j>=0 && j<8;i--,j++)
                {
                    if(board[i][j]==WHITE || board[i][j]==WHITE_KING)
                    {
                        if(board[i-1][j+1]!=BLANK)
                        {
                            return false;
                        }
                        else if(board[i-1][j+1]==BLANK)
                        {
                            board[i][j]=BLANK;
                            i=x_pos;
                            j=y_pos;
                            king_correction++;
                        }
                    }
                }
                return true;
            }
            else if(x_pos+y_pos==x_dest+y_dest && (y_pos>y_dest))
            {
                for(int i = x_pos,j=y_pos;i>=0 && i<8 && j>=0 && j<8;i++,j--)
                {
                    if(board[i][j]==WHITE || board[i][j]==WHITE_KING)
                    {
                        if(board[i+1][j-1]!=BLANK)
                        {
                            return false;
                        }
                        else if(board[i+1][j-1]==BLANK)
                        {
                            board[i][j]=BLANK;
                            i=x_pos;
                            j=y_pos;
                            king_correction++;
                        }
                    }
                }
                return true;
            }
        }
        else if(player==WHITE_KING)
        {
            if(x_pos+y_pos>x_dest+y_dest)
            {
                for(int i = x_pos,j=y_pos;i>=0 && i<8 && j>=0 && j<8;i--,j--)
                {
                    if(board[i][j]==BLACK || board[i][j]==BLACK_KING)
                    {
                        if(board[i-1][j-1]!=BLANK)
                        {
                            return false;
                        }
                        else if(board[i-1][j-1]==BLANK)
                        {
                            board[i][j]=BLANK;
                            i=x_pos;
                            j=y_pos;
                            king_correction++;
                        }
                    }
                }
                return true;
            }
            else if(x_pos+y_pos<x_dest+y_dest)
            {
                for(int i = x_pos,j=y_pos;i>=0 && i<8 && j>=0 && j<8;i++,j++)
                {
                    if(board[i][j]==BLACK || board[i][j]==BLACK_KING)
                    {
                        if(board[i+1][j+1]!=BLANK)
                        {
                            return false;
                        }
                        else if(board[i+1][j+1]==BLANK)
                        {
                            board[i][j]=BLANK;
                            i=x_pos;
                            j=y_pos;
                            king_correction++;
                        }
                    }
                }
                return true;
            }
            else if(x_pos+y_pos==x_dest+y_dest && (y_pos<y_dest))
            {
                for(int i = x_pos,j=y_pos;i>=0 && i<8 && j>=0 && j<8;i--,j++)
                {
                    if(board[i][j]==BLACK || board[i][j]==BLACK_KING)
                    {
                        if(board[i-1][j+1]!=BLANK)
                        {
                            return false;
                        }
                        else if(board[i-1][j+1]==BLANK)
                        {
                            board[i][j]=BLANK;
                            i=x_pos;
                            j=y_pos;
                            king_correction++;
                        }
                    }
                }
                return true;
            }
            else if(x_pos+y_pos==x_dest+y_dest && (y_pos>y_dest))
            {
                for(int i = x_pos,j=y_pos;i>=0 && i<8 && j>=0 && j<8;i++,j--)
                {
                    if(board[i][j]==BLACK || board[i][j]==BLACK_KING)
                    {
                        if(board[i+1][j-1]!=BLANK)
                        {
                            return false;
                        }
                        else if(board[i+1][j-1]==BLANK)
                        {
                            board[i][j]=BLANK;
                            i=x_pos;
                            j=y_pos;
                            king_correction++;
                        }
                    }
                }
                return true;
            }
        }
        return false;
    }

   bool consecutiveJump()
    {
       
       if(player==BLACK)
       {
           for(int i = x_dest-1;i<=x_dest+1 && i>=0 && i<8;i++)
           {
               for(int j = y_dest-1;j<=y_dest+1 && j>=0 && j<8;j++)
               {
                   if(board[i][j]==WHITE|| board[i][j]==WHITE_KING)
                   {
                       for(int a = i-1;a<=i+1 && a>=0 && a<8;a++)
                       {
                           for(int b = j-1;b<=j+1 && b>=0 && b<8;b++)
                           {
                               if(board[a][b]==(BLANK) && (abs(y_dest-b)+abs(x_dest-a)==4))
                               {
                                    board[x_dest][y_dest]=board[x_pos][y_pos];
                                    board[x_pos][y_pos]=BLANK;
                                    x_pos=x_dest;
                                    y_pos=y_dest;
                                    upgradeChecker();
                                    printBoard();
                                    return false;
                                }
                                
                           }
                       }
                   }
               }
           }
            
       }
       else if(player==WHITE)
       {
           for(int i = x_dest-1;i<=x_dest+1 && i>=0 && i<8;i++)
           {
               for(int j = y_dest-1;j<=y_dest+1 && j>=0 && j<8;j++)
               {
                   if(board[i][j]==BLACK|| board[i][j]==BLACK_KING)
                   {
                       for(int a = i-1;a<=i+1 && a>=0 && a<8;a++)
                       {
                           for(int b = j-1;b<=j+1 && b>=0 && b<8;b++)
                           {
                               if(board[a][b]==(BLANK) && (abs(y_dest-b)+abs(x_dest-a)==4))
                               {
                                    board[x_dest][y_dest]=board[x_pos][y_pos];
                                    board[x_pos][y_pos]=BLANK;
                                    x_pos=x_dest;
                                    y_pos=y_dest;
                                    upgradeChecker();
                                    printBoard();
                                    return false;
                                }
                                
                           }
                       }
                   }
               }
           }
            
       }
       return true;
   }
   
    bool hitOn()
    {
        if(player==BLACK)
        {
            for (int i = x_pos-1; i<=x_pos+1; i++)
            {
                for(int j = y_pos-1; j<=y_pos+1; j++)
                {
                    if(board[i][j]==WHITE || board[i][j]== WHITE_KING)
                    {
                        for(int a = x_dest-1;a<=x_dest+1;a++)
                        {
                            for(int b = y_dest-1;b<=y_dest+1;b++)
                            {
                                if(i==a && j==b)
                                {
                                 board[i][j]=BLANK;
                                return true;   
                                }
                            }
                        }                        
                    }
                }
            }
            return false;
        }
        else if(player==WHITE)
        {
            for (int i = x_pos-1; i<=x_pos+1; i++)
            {
                for(int j = y_pos-1; j<=y_pos+1; j++)
                {
                    if( board[i][j]==BLACK || board[i][j]==BLACK_KING)
                    {
                        for(int a = x_dest-1;a<=x_dest+1;a++)
                        {
                            for(int b = y_dest-1;b<=y_dest+1;b++)
                            {
                                if( (a==i) && (b==j))
                                { 
                                 board[i][j]=BLANK;
                                return true;   
                                }
                            }
                        }                        
                    }
                }
            }
            return false;
        }
        return false;
    }
    void switchPlayers()
    {
        int temp;
        temp = player;
        player = enemy;
        enemy = temp;
        temp = 0;
        bot=!bot;
    }

    void pickColor()
    {
        bot = true;
        char color;
        std::cout<<"Pick your color, type 'B' or 'W'"<<std::endl;
        std::cin>>color;
        switch(color)
        {
        case ('W' | 'w'):
            player=WHITE;
            enemy=BLACK;
            break;
        case ('B' | 'b'):
            player=BLACK;
            enemy=WHITE;
            break;
        default:
            std::cout<<"Unknown input, selecting by default 'B'"<<std::endl;
            player=BLACK;
            enemy=WHITE;
            break;
        }
    }
    void upgradeChecker()
    {
        for(int i=0;i<8;i++)
        {
            if(board[7][i]==BLACK)
            {
                board[7][i]=BLACK_KING;
                player=BLACK_KING;
            }
        }
        for(int i = 0;i<8;i++)
        {
            if(board[0][i]==WHITE)
            {
                board[0][i]=WHITE_KING;
                player=WHITE_KING;
            }
        }
    }
void spawnBlack(int a, int b, bool c)
   {
       if(c==0)
       {
       board[a][b]=BLACK;
       }
       else
       {
        board[a][b]=BLACK_KING;
       }
   }
void spawnWhite(int a, int b, bool c)
   {
       if(c==0)
       {
           board[a][b]=WHITE;
       }
       else
       {
           board[a][b]=WHITE_KING;
       }
   }
bool winCondition()
{
    int whites=0;
    int blacks=0;
    for(int i=0;i<8;i++)
    {
        for(int j = 0;j<8;j++)
        {
            if(board[i][j]==WHITE || board[i][j]==WHITE_KING)
            {
                whites++;
            }
            else if(board[i][j]==BLACK || board[i][j]==BLACK_KING)
            {
                blacks++;
            }
        }
    }
    
    if(whites==0)
    {
        std::cout<<"Black wins!"<<std::endl;
        return true;
    }
    else if(blacks==0)
    {
        std::cout<<"White wins!"<<std::endl;
        return true;
    }
    else
    {
        return false;
    }
    
}
private:
    int board[8][8];
    int player,enemy;
    int attempt,king_correction;
    int x_pos,y_pos,x_dest,y_dest;
    char y_proto;
    bool correct_move, correct_checker,correct_input;
    bool bot;
};

int main()
{
    srand (time(NULL));
    CheckerBoard test;
    test.initBoard();
    test.placeCheckers();
    test.printBoard();
    test.pickColor();
    while(!test.winCondition())
    {
        test.pickChecker();
        test.moveChecker();
        test.upgradeChecker();
        test.printBoard();
        test.switchPlayers();
    }
    
    return 0;

}

