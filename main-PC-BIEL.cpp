#include <iostream>
#include <allegro.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
/* Thread Need */
volatile int ticks;
void ticker()
{
    ticks++;
}
volatile int mikus;
void mikur()
{
    mikus++;
}

volatile int times;
void timer()
{
    times++;
}


class Allegro{

private:
    int heigth,width;
public:
    Allegro(){
        heigth=860;
        width=640;
    }
    Allegro(int a,int b){
        heigth=a;
        width=b;
    }
    void init(){
        allegro_init();
        install_keyboard();
        install_timer();
        install_mouse();
        install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, "A");
        set_color_depth( 32 );
        set_gfx_mode(GFX_AUTODETECT_WINDOWED, heigth,width, 0, 0);
        LOCK_VARIABLE(ticks);
        LOCK_FUNCTION(ticker);
        install_int(ticker,10);
        LOCK_VARIABLE(mikus);
        LOCK_FUNCTION(mikur);
        install_int(mikur,10);
        LOCK_VARIABLE(times);
        LOCK_FUNCTION(timer);
        install_int(timer,10);
    }




};

class Controllers{

private:
    int keySpace,keyEnter,keyEsc,keyUp,keyDown,keyLeft,keyRight;
public:
    Controllers(){
        keyEsc=0;
        keyUp=0;
        keyDown=0;
        keyLeft=0;
        keyRight=0;
        keyEnter=0;
        keySpace=0;
    }
    int getSpace(){
        return keySpace;
    }
    void setSpace(int a)
    {
        keySpace=a;
    }
    int getRight(){
        return keyRight;
    }
    void setRight(int a)
    {
        keyRight=a;
    }
    int getLeft(){
        return keyLeft;
    }
    void setLeft(int a)
    {
        keyLeft=a;
    }
    int getEsc(){
        return keyEsc;
    }
    void setEsc(int a){
        keyEsc=a;
    }
    int getUp(){
        return keyUp;
    }
    void setUp(int a){
        keyUp = a;
    }
    int getDown(){
        return keyDown;
    }
    void setDown(int a){
        keyDown = a;
    }
    int getEnter(){
        return keyEnter;
    }
    void setEnter(int a){
        keyEsc = a;
    }

};

class Menu: public Controllers{

private:
    BITMAP *fundo[3],*charac,*recta,*controller,*buffer;
    FONT *font;
    int x,y;
    int i;
    int control;
public:
    Menu(){
        x=230;
        y=250;
        i=0;
        control=0;
        font = load_font("Font/font.pcx",NULL,NULL);
        fundo[0]=load_bmp("ArtWork/Back/fundo1.bmp",NULL);
        fundo[1]=load_bmp("ArtWork/Back/fundo2.bmp",NULL);
        fundo[2]=load_bmp("ArtWork/Back/fundo3.bmp",NULL);
        controller = load_bmp("cursor.bmp",NULL);
        charac=load_bmp("ArtWork/Loading/load.bmp",NULL);
        buffer = create_bitmap(860,640);

    }
    void printMenu(){

        blit(fundo[0],buffer,0,0,0,0,860,640);
        masked_blit(controller,buffer,0,0,x,y,60,40);
        blit(buffer,screen,0,0,0,0,860,640);
    }
    int menuControl(){
        if(key[KEY_DOWN])
        {
            if(!getDown())
            {
                if(control<2){
                    setDown(1);
                    control+=1;
                    y+=60;
                }
                else
                {
                    y=190;
                    control=-1;
                }

            }
        }
        else
            setDown(0);
        if(key[KEY_UP])
        {
            if(!getUp())
            {
                if(control>0){
                    setUp(1);
                    control-=1;
                    y-=60;
                }
                else
                {
                    y=430;
                    control=3;

                }

            }
        }
        else
            setUp(0);
        if(key[KEY_ENTER])
        {
            if(!getEnter())
            {
                return control;
                setEnter(1);
            }
        }
        else
            setEnter(0);

    }

    void startGame()
    {

    }


};

class Gameplay: public Controllers{
private:
    BITMAP *miku[11],*ball,*arrows[2],*backGround,*howtoplay,*buffer;
    SAMPLE *song;
    FONT *font;
    int h,score,j,x,y,x1,o,cont,i,backMenu;
    int level;
    int notas[5];

public:
    Gameplay(){
        h=0;
        int number=1;
        char bufferr[50];
        char bmpt[50]=".bmp";
        score=0;
        font=load_font("Font/font.pcx",NULL,NULL);
        ball = load_bmp("ball.bmp",NULL);
        arrows[0] = load_bmp("arrows.bmp",NULL);
        arrows[1] = load_bmp("arrowshit.bmp",NULL);
        howtoplay =load_bmp("howto.bmp",NULL);
        backGround = load_bmp("backGround.bmp",NULL);
        song = load_sample("song.wav");
        cont=0;
        o=0;
        x=0;
        y=0;
        x1=300;
        level=0;
        backMenu=0;
        buffer = create_bitmap(860,640);
        for(i=0;i<5;i++)
        {
            notas[i]= -1;
        }
        i=0;
        for(i=0;i<11;i++){
            char fullText[50]=("ArtWork/Char/");
            itoa(number,bufferr,10);
            strcat(fullText,bufferr);
            strcat(fullText,bmpt);
            miku[i]=load_bmp(fullText,NULL);
            number++;
        }
        for(i=0;i<11;i++){
            for (y = 0; y < 600; y++){
                for (x = 0; x < 600; x++){
                    if (getpixel(miku[i], x, y) == makecol(0,255,0))
                        putpixel(miku[i], x, y, makecol(255, 0, 255));
                }
               }}
    }
    void randNotas(){
        srand(time(NULL));
        for(i=0;i<5;i++)
        {
            notas[i]=rand()%4;
        }
    }
    void startGame(){
        backMenu=0;
        ticks=0;
        j=0;
        blit(backGround,buffer,0,0,0,0,860,640);
        blit(buffer,screen,0,0,0,0,860,640);


        while(ticks<150){}
        play_sample( song, 5, 128, 1000, false );
        times = -25300;
        while(!backMenu){
                gamePlayControls();
                if(mikus>5)
                {
                    if(h<10)
                    {
                        h++;
                    }
                    else
                        h=0;
                    mikus=0;
                }
                masked_blit(backGround,buffer,0,0,0,0,860,640);
                masked_blit(ball,buffer,0,0,250+ticks*2,478,27,30);
                masked_blit(miku[h],buffer,0,0,miku[0]->w-miku[h]->w,130+miku[0]->h-miku[h]->h,400,400);
                textprintf_ex(buffer,font,30,8,makecol(0,0,0),-1,"Score : %d",score);
                textprintf_ex(buffer,font,30,580,makecol(0,0,0),-1,"Time : %d",times*-1/100);

                if(ticks>180)
                {
                    cont=0;
                    j=0;
                    randNotas();
                    ticks=0;
                    if(level<9)
                        level++;
                    else
                        level=1;
                }
                for(i=0;i<level;i++)
                {
                    switch(notas[i])
                    {
                    case 0:
                        x=0;
                        break;
                    case 1:
                        x=50;
                        break;
                    case 2:
                        x=50*2;
                        break;
                    case 3:
                        x=50*3;
                        break;
                    }
                    if(cont==i+1)
                    {
                        o=1;
                    }
                    else
                        o=0;

                    masked_blit(arrows[o],buffer,x,0,210+(i*50),510,50,36);

                }
                masked_blit(buffer,screen,0,0,0,0,860,640);

                clear_bitmap(buffer);







        }
    }
    void startScore(){
    }
    void gamePlayControls(){
        if(key[KEY_A])
        {
           if(!getEsc())
           {
               setEsc(1);
               backMenu=1;
               stop_sample( song );
           }
        }
        else
            setEsc(0);
        if(key[KEY_UP])
        {
            if(!getUp())
            {
                if(notas[j]==0 && cont<level)
                {
                    j++;
                    cont++;
                }
                else
                {
                    cont=0;
                    j=0;
                }
                setUp(1);
            }
        }
        else
        {
            setUp(0);
        }
        if(key[KEY_DOWN])
        {
            if(!getDown())
            {
                if(notas[j]==3 && cont<level)
                {
                    j++;
                    cont++;
                }
                else
                {
                    cont=0;
                    j=0;
                }
                setDown(1);
            }
        }
        else
        {
            setDown(0);
        }
        if(key[KEY_LEFT])
        {
            if(!getLeft())
            {
                if(notas[j]==1 && cont<level)
                {
                    j++;
                    cont++;
                }
                else
                {
                    cont=0;
                    j=0;
                }
                setLeft(1);
            }
        }
        else
        {
            setLeft(0);
        }
        if(key[KEY_RIGHT])
        {
            if(!getRight())
            {
                if(notas[j]==2 && cont<level)
                {
                    j++;
                    cont++;
                }
                else
                {
                    cont=0;
                    j=0;
                }
                setRight(1);
            }
        }
        else
        {
            setRight(0);
        }

        if(key[KEY_SPACE])
        {
            if(!getSpace())
            {
                if(cont==level && ticks>165 && ticks<180)
                {

                    score+=50*level;
                    randNotas();
                }
                else
                {
                    cout<<ticks<<endl;
                    cout<<"MISS"<<endl;
                    level=1;
                }

                setSpace(1);
                cont=0;
                j=-1;
            }
        }
        else
        {
            setSpace(0);
        }

    }

};


class Game: public Controllers{

private:
    int exit,quitMenu;
    Gameplay gameplayObject;
    Menu menu;
public:
    Game(){
        exit=0;
        quitMenu=0;
    }
    int exitClose(){
        if(key[KEY_ESC])
        {
            exit=1;
            quitMenu=1;
        }


        return exit;
    }
    void loadMenu(){
       while(!exitClose() || !quitMenu)
       {
            menu.printMenu();

            switch (menu.menuControl())
            {
                case 0:
                    gameplayObject.startGame();
                    break;
                case 1:
                    gameplayObject.startScore();
                    break;
                case 2:
                    exit=1;
                    quitMenu=1;
                    break;

            }
       }

    }




};




int main()
{
    Allegro engine(860,640);
    engine.init();
    Game FSteal;


    while(!FSteal.exitClose()){
            FSteal.loadMenu();



    }

}END_OF_MAIN();
