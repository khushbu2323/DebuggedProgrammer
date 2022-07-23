#include <iostream>
#define GRIDHEIGHT 10
#define GRIDWIDTH 40
 
struct Pattern {
public:
    char XGridCord;
    char YGridCord;
    char ptrnheight;
    char ptrnwidth;
    char **figure;
};
 
struct GliderGOL : public Pattern {
    static const char GLIDER_PATTERN_SIZE = 6;
    GliderGOL( char var1 , char var2 );
    ~GliderGOL();
};
 
struct BlinkerGOL : public Pattern {
    static const char BLINKER_PATTERN_HEIGHT = 6;
    static const char BLINKER_PATTERN_WIDTH = 3;
    BlinkerGOL( char var1 , char var2 );
    ~BlinkerGOL();
};
 
class ConwayGameofLife {
public:
    ConwayGameofLife( Pattern sty );
    void WriteFrame();
    void updateFrame();
    char SeedGrid( char currentstate , char XGridCord , char YGridCord , bool switchvar);
    void InitialiseGameOfLife(unsigned int gamerotation);
private:
    char GOLWORLD[GRIDHEIGHT][GRIDWIDTH];
    char GOLOTHERWORLD[GRIDHEIGHT][GRIDWIDTH];
    bool switchvar;
    Pattern style;
};
 
ConwayGameofLife::ConwayGameofLife( Pattern sty ) :
    style(sty) ,
    switchvar(true) 
{
    for ( char i = 0; i < GRIDHEIGHT; i++ ) {
        for ( char j = 0; j < GRIDWIDTH; j++ ) {
            GOLWORLD[i][j] = '.';
        }
    }
    for ( char i = style.YGridCord; i - style.YGridCord < style.ptrnheight; i++ ) {
        for ( char j = style.XGridCord; j - style.XGridCord < style.ptrnwidth; j++ ) {
            if ( i < GRIDHEIGHT && j < GRIDWIDTH ) {
                GOLWORLD[i][j] = 
                    style.figure[ i - style.YGridCord ][j - style.XGridCord ];
            }
        }
    }
}
 
void ConwayGameofLife::WriteFrame() {
    if ( switchvar ) {
        for ( char i = 0; i < GRIDHEIGHT; i++ ) {
            for ( char j = 0; j < GRIDWIDTH; j++ ) {
                std::cout << GOLWORLD[i][j];
            }
            std::cout << std::endl;
        }
    } else {
        for ( char i = 0; i < GRIDHEIGHT; i++ ) {
            for ( char j = 0; j < GRIDWIDTH; j++ ) {
                std::cout << GOLOTHERWORLD[i][j];
            }
            std::cout << std::endl;
        }
    }
    for ( char i = 0; i < GRIDWIDTH; i++ ) {
        std::cout << '=';
    }
    std::cout << std::endl;
}
 
void ConwayGameofLife::updateFrame() {
    if (switchvar) {
        for ( char i = 0; i < GRIDHEIGHT; i++ ) {
            for ( char j = 0; j < GRIDWIDTH; j++ ) {
                GOLOTHERWORLD[i][j] = 
                    ConwayGameofLife::SeedGrid(GOLWORLD[i][j] , i , j , switchvar);
            }
        }
        switchvar = !switchvar;
    } else {
        for ( char i = 0; i < GRIDHEIGHT; i++ ) {
            for ( char j = 0; j < GRIDWIDTH; j++ ) {
                GOLWORLD[i][j] = 
                    ConwayGameofLife::SeedGrid(GOLOTHERWORLD[i][j] , i , j , switchvar);
            }
        }
        switchvar = !switchvar;
    }
}
 
char ConwayGameofLife::SeedGrid( char currentstate, char YGridCord, char XGridCord, bool switchvar ) {
    char countforneighbors = 0;
    if ( switchvar ) {
        for ( char i = YGridCord - 1; i <= YGridCord + 1; i++ ) {
            for ( char j = XGridCord - 1; j <= XGridCord + 1; j++ ) {
                if ( i == YGridCord && j == XGridCord ) {
                    continue;
                }
                if ( i > -1 && i < GRIDHEIGHT && j > -1 && j < GRIDWIDTH ) {
                    if ( GOLWORLD[i][j] == 'X' ) {
                        countforneighbors++;
                    }
                }
            }
        }
    } else {
        for ( char i = YGridCord - 1; i <= YGridCord + 1; i++ ) {
            for ( char j = XGridCord - 1; j <= XGridCord + 1; j++ ) {
                if ( i == YGridCord && j == XGridCord ) {
                    continue;
                }
                if ( i > -1 && i < GRIDHEIGHT && j > -1 && j < GRIDWIDTH ) {
                    if ( GOLOTHERWORLD[i][j] == 'X' ) {
                        countforneighbors++;
                    }
                }
            }
        }
    }
    if (currentstate == 'X') {
        return ( countforneighbors > 1 && countforneighbors < 4 ) ? 'X' : '.';
    }
    else {
        return ( countforneighbors == 3 ) ? 'X' : '.';
    }
}
 
void ConwayGameofLife::InitialiseGameOfLife( unsigned int gamerotation ) {
    for ( int i = 0; i < gamerotation; i++ ) {
        WriteFrame();
        updateFrame();
    }
}
 
GliderGOL::GliderGOL( char var1 , char var2 ) {
    XGridCord = var1;
    YGridCord = var2;
    ptrnheight = GLIDER_PATTERN_SIZE;
    ptrnwidth = GLIDER_PATTERN_SIZE;
    figure = new char*[GLIDER_PATTERN_SIZE];
    for ( char i = 0; i < GLIDER_PATTERN_SIZE; i++ ) {
        figure[i] = new char[GLIDER_PATTERN_SIZE];
    }
    for ( char i = 0; i < GLIDER_PATTERN_SIZE; i++ ) {
        for ( char j = 0; j < GLIDER_PATTERN_SIZE; j++ ) {
            figure[i][j] = '.';
        }
    }
    figure[0][1] = 'X';
    figure[1][2] = 'X';
    figure[2][0] = 'X';
    figure[2][1] = 'X';
    figure[2][2] = 'X';
}
 
GliderGOL::~GliderGOL() {
    for ( char i = 0; i < GLIDER_PATTERN_SIZE; i++ ) {
        delete[] figure[i];
    }
    delete[] figure;
}
 
BlinkerGOL::BlinkerGOL( char var1 , char var2 ) {
    XGridCord = var1;
    YGridCord = var2;
    ptrnheight = BLINKER_PATTERN_HEIGHT;
    ptrnwidth = BLINKER_PATTERN_WIDTH;
    figure = new char*[BLINKER_PATTERN_HEIGHT];
    for ( char i = 0; i < BLINKER_PATTERN_HEIGHT; i++ ) {
        figure[i] = new char[BLINKER_PATTERN_WIDTH];
    }
    for ( char i = 0; i < BLINKER_PATTERN_HEIGHT; i++ ) {
        for ( char j = 0; j < BLINKER_PATTERN_WIDTH; j++ ) {
            figure[i][j] = 'X';
        }
    }
}
 
BlinkerGOL::~BlinkerGOL() {
    for ( char i = 0; i < BLINKER_PATTERN_HEIGHT; i++ ) {
        delete[] figure[i];
    }
    delete[] figure;
}
 
int main() {
    GliderGOL glider(0,0);
    ConwayGameofLife gol(glider);
    gol.InitialiseGameOfLife(5);
    BlinkerGOL blinker(1,0);
    ConwayGameofLife gol2(blinker);
    gol2.InitialiseGameOfLife(4);
}
 