/* $Id: main.cc 956 2008-10-19 22:24:23Z hsc $ */

/* Hier muesst ihr selbst Code vervollstaendigen */ 
        
#include "machine/cgascr.h"
#include "device/cgastr.h"
#include "machine/keyctrl.h"
#include "machine/pic.h"
#include "machine/cpu.h"
#include "machine/plugbox.h"
#include "syscall/guarded_keyboard.h"
#include "user/appl.h"
#include "user/loop.h"
#include "syscall/guarded_organizer.h"
#include "syscall/guarded_buzzer.h"
#include "syscall/guarded_semaphore.h"
#include "device/watch.h"
#include "guard/guard.h"
#include "library/random.h"

CPU cpu;
Application app;
Loop loop;

class TimerGate : public Gate 
{
	void trigger()
	{
		kout << "ich bin ein timer gate" << endl;
	}
};


#include "guard/secure.h"
class Test: public Thread
{
	char stack[4096];
	public:
	Application *app;
	Test(): Thread(stack+4096)
	{
	}
	void action()
	{
		int i=0;
		while (true)
		{
			i++;
			{ SecureSem section(&screen_lock);
				kout.setpos(5, 11);
				kout << "test "<<i;
				kout.flush();
			}

			{ SecureSem section(&screen_lock);
				kout.setpos(5, 1);
				for(int i=0;i<256;i++)
					kout << (char)i;
				kout.flush();
			}
			
			Guarded_Buzzer buzzer;
			buzzer.set(1000);
			buzzer.sleep();


			//organizer.resume();
		
		}
	}
}test;

class Idle: public Thread
{
	char stack[4096];
	public:
	Idle(): Thread(stack+4096)
	{
	}
	void action()
	{
		while (true)
		{
			organizer.resume();
		}
	}
}idle;


#define FACTOR 1000

class GameField
{
	char stack[4096];
	public:
	
	char screen[25][80];
	char colors[25][80];
	int scrollPos;
	
	GameField(): scrollPos(0)
	{
	}
	
	void clear()
	{
		for(int y=1;y<25;y++)
		for(int x=0;x<80;x++)
		{
			screen[y][x] = ' ';
			colors[y][x] = 0x0f;
		}
	}
	void show()
	{
		for(int y=1;y<25;y++)
		for(int x=0;x<80;x++)
			kout.show(x,y,screen[y][x],colors[y][x]);
	}
	
	void setDirect(int x, int y, char c)
	{
		int x2 = x;
		int y2 = y;
		if(y2<0 || y2>24)
			return;
		if(x2<0 || x2>80)
			return;
		screen[y2][x2]=c;
	}
	void set(int x, int y, char c)
	{
		int x2 = x/FACTOR;
		int y2 = 24-(y-scrollPos)/FACTOR;
		setDirect(x2,y2,c);
	}
	void setColor(int x, int y, char color)
	{
		int x2 = x/FACTOR;
		int y2 = 24-(y-scrollPos)/FACTOR;
		if(y2<0 || y2>24)
			return;
		if(x2<0 || x2>80)
			return;
		colors[y2][x2]=color;
	}
	
	void showBlock(int x, int y, int w, int h, char c, char color)
	{
		x = x/FACTOR;
		y = 24-(y-scrollPos)/FACTOR;
		w = w/FACTOR;
		h = h/FACTOR;
		
		for(int x2=x;x2<x+w;x2++)
		for(int y2=y;y2>y-h;y2--)
		{
			if(y2<0 || y2>24)
				continue;
			if(x2<0 || x2>80)
				continue;
			screen[y2][x2]=c;
			colors[y2][x2]=color;
		}
	}

};

class GameObject
{
	public:
	virtual void draw(GameField &field)
	{
	}
};

class Block: public GameObject
{
	public:
	int x,y,w,h;
	char color;
	Block(int x,int y,int w,int h, char color): x(x),y(y),w(w),h(h),color(color)
	{
		
	}
	Block(): x(0),y(0),w(0),h(0), color(0x60)
	{
		
	}
	virtual void draw(GameField &field)
	{
		field.showBlock(x,y,w,h,' '/*0xDB*/, 0x0f|color);
	}
	
	bool collides(int x, int y)
	{
		return x+3*FACTOR>this->x && x < this->x+w && y>=this->y && y<this->y+h;
	}
};

#define NUM_BLOCKS 20

#define abs(a) (((a)>0)?(a):-(a))

class Player: public GameObject
{
	public:
	int x,y;
	int deltax, deltay;
	
	Player()
	{
		x=0;
		y=0;
		deltax = 0;
		deltay = 40 * FACTOR;
	}
	virtual void draw(GameField &field)
	{
		field.set(x,y,'/');
		field.set(x+2*FACTOR,y,'\\');
		field.set(x+1*FACTOR,y+1*FACTOR,'|');
		field.set(x+1*FACTOR,y+3*FACTOR,0x01);
		if(deltay<= 0 && deltay > -10*FACTOR)
		{
			field.set(x,y+2*FACTOR,'-');
			field.set(x+2*FACTOR,y+2*FACTOR,'-');
		}
		else if(deltay < 0)
		{
			field.set(x,y+2*FACTOR,'\\');
			field.set(x+2*FACTOR,y+2*FACTOR,'/');
		}
		else
		{
			field.set(x,y+2*FACTOR,'/');
			field.set(x+2*FACTOR,y+2*FACTOR,'\\');
		}
		
	}
	
	
	void update(Block *blocks)
	{
		if(deltay>0 && deltay<1*FACTOR)
			deltay -= 64*FACTOR/100;
		
		int speed = 35*  FACTOR;
		int targetDeltaX = 0;
		if(keyboard.isPressed(30))
			targetDeltaX -= speed;
		if(keyboard.isPressed(32))
			targetDeltaX += speed;
		
		deltax = targetDeltaX;
		x += deltax / 100;
		
		for(int i=0;i<NUM_BLOCKS;i++)
		{
			if(deltay < 0 && blocks[i].collides(x,y))
			{
				deltay = 40 * FACTOR;
			}
		}
		if(y < 0)
		{
			y=0;
			deltay = 40 * FACTOR;
		}
		if(x < 0)
		{
			x=0;
		}
		if(x > (80-3)*FACTOR)
		{
			x=(80-3)*FACTOR;
		}
		
		y += deltay / 100;
		deltay -= 64*FACTOR/100;
	}
};

char *gameoverText[] = {
	" ________  ________  _____ ______   _______      ",
	"|\\   ____\\|\\   __  \\|\\   _ \\  _   \\|\\  ___ \\     ",
	"\\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\ \\   __/|    ",
	" \\ \\  \\  __\\ \\   __  \\ \\  \\\\|__| \\  \\ \\  \\_|/__  ",
	"  \\ \\  \\|\\  \\ \\  \\ \\  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\ ",
	"   \\ \\_______\\ \\__\\ \\__\\ \\__\\    \\ \\__\\ \\_______\\",
	"    \\|_______|\\|__|\\|__|\\|__|     \\|__|\\|_______|",
	"                                                 ",
	"                                                 ",
	"                                                 ",
	" ________  ___      ___ _______   ________       ",
	"|\\   __  \\|\\  \\    /  /|\\  ___ \\ |\\   __  \\      ",
	"\\ \\  \\|\\  \\ \\  \\  /  / | \\   __/|\\ \\  \\|\\  \\     ",
	" \\ \\  \\\\\\  \\ \\  \\/  / / \\ \\  \\_|/_\\ \\   _  _\\    ",
	"  \\ \\  \\\\\\  \\ \\    / /   \\ \\  \\_|\\ \\ \\  \\\\  \\|   ",
	"   \\ \\_______\\ \\__/ /     \\ \\_______\\ \\__\\\\ _\\   ",
	"    \\|_______|\\|__|/       \\|_______|\\|__|\\|__|  ",
	"                                                 ",
	"                                                 ",
	"                                                 ",
};

Guarded_Semaphore gameStartSem(0);
Guarded_Semaphore gameEndSem(0);

class Game: public Thread
{
	char stack[4096];
	public:
	
	Player player;
	Block blocks[NUM_BLOCKS];
	GameField field;
	Random random;
	int lastBlockY;
	int nextBlock;
	int points;
	
	int lastBlockX, lastBlockW;
	
	Game(): Thread(stack+4096), random(watch.getTime())
	{
	}
	
	void addBlocks()
	{
		while(blocks[nextBlock].y < player.y-100*FACTOR)
		{
			char color = 0;
			while(color == 0 || color == 0x7)
			{
				color = (random.number()%(8)) << 4;
			}
			
			int w = random.number()%10+10;
			int h = random.number()%(3)+2;
			
			
			int x;
			do
			{
				x = random.number()%(80-w);
			}while((x+w+35)*FACTOR < lastBlockX || (x-35)*FACTOR > lastBlockX+lastBlockW);
			
			lastBlockY += (5+random.number()%5)*FACTOR;
			lastBlockX = x * FACTOR;
			lastBlockW = w * FACTOR;
			blocks[nextBlock] = Block(lastBlockX,lastBlockY,w * FACTOR,h * FACTOR, color);
			nextBlock = (nextBlock+1)%NUM_BLOCKS;
		}
	}
	
	void gameover()
	{
		for(int i=0;i<sizeof(gameoverText)/sizeof(gameoverText[0]);i++)
		{
			char *text = gameoverText[i];
			int col = 0;
			while(*text)
			{
				field.setDirect(col+15, i+3, *text);
				text++;
				col++;
			}
		}
	}
	
	void init()
	{
		points = 0;
		lastBlockY = 0;
		lastBlockX = 35;
		lastBlockW = 10;
		nextBlock = 0;
		player = Player();
		field.scrollPos = 0;
		for(int i=0;i<NUM_BLOCKS;i++)
			blocks[i] = Block(0,-500*FACTOR,0,0, 0);
		
		random = Random(watch.getTime());
	}
	
	void runGame()
	{
		init();
		while (true)
		{
			int start = watch.getTime();
			player.update(blocks);
			
			addBlocks();
			
			/*if(player.y - field.scrollPos >= 20*FACTOR)
				field.scrollPos+=5*FACTOR/100;
			if(player.y - field.scrollPos <= -10*FACTOR)
				field.scrollPos-=5*FACTOR/100;*/
			
			if(player.y - field.scrollPos >= 20*FACTOR)
				field.scrollPos=player.y-20*FACTOR;
			if(player.y - field.scrollPos <= -2*FACTOR)
			{
				gameover();
				field.show();
				return;
			}
			
			field.clear();
			
			for(int i=0;i<NUM_BLOCKS;i++)
				blocks[i].draw(field);
			
			player.draw(field);
			//	gameover();
			
			field.show();
			
			int p = player.y / FACTOR / 10;
			if(p > points)
				points = p;
			{
				kout.setpos(5, 0);
				kout << "Points: " << points;
				kout.flush();
				int x,y;
				kout.getpos(x, y);
				for(int i=x;i<80;i++)
					kout.show(i,0, ' ',0x0f);
			}
			
			
			int end = watch.getTime();
			
			int s = 10-(end-start);
			if(s>0)
			{
				Guarded_Buzzer buzzer;
				buzzer.set(s);
				buzzer.sleep();
			}
		}
	}

	
	void action()
	{
		gameStartSem.wait();
		
		
		while (true)
		{
			runGame();
			gameEndSem.signal();
			gameStartSem.wait();
		}
	}
}game;

class Starter: public Thread
{
	char stack[4096];
	public:
	
	Starter(): Thread(stack+4096)
	{
	}

	void action()
	{
		for(int i=0;i<25;i++)
			kout << "\n";
		/*kout << "press any key";
		for(int i=0;i<15;i++)
			kout << "\n";*/
		while(true)
		{
			gameStartSem.signal();
			gameEndSem.wait();
			
			Guarded_Buzzer buzzer;
			buzzer.set(1000);
			buzzer.sleep();
			
			kout.setpos(28, 22);
			kout << "press any key to restart";
			kout.flush();
			
			keyboard.clearBuffer();
			keyboard.getkey();
		}
	}
}starter;


int main()
{
	keyboard.plugin();
	//plugbox.assign(Plugbox::timer, timer);	
	
	cpu.enable_int();
	
	guard.enter();
	watch.windup();
	
	//for(int i=0;i<10000;i++){}
	
	
	organizer.Scheduler::ready(idle);
	//organizer.Scheduler::ready(app);
	//organizer.Scheduler::ready(loop);
	//organizer.Scheduler::ready(test);
	//organizer.Scheduler::ready(input);
	organizer.Scheduler::ready(game);
	organizer.Scheduler::ready(starter);
	
	organizer.schedule();
	   
   while(true){}
   
 
   return 0;
 }

