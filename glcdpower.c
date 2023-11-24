#include&quot;lpc214x.h&quot;
#define LCD_PORT 0x00FF0000
#define EN 1&lt;&lt;31
#define RS 1&lt;&lt;27
#define CS1 1&lt;&lt;26
#define CS2 1&lt;&lt;25
#define GRST 1&lt;&lt;30
#define RW 1&lt;&lt;24
#define LCD_SHIFT 16
void delay(unsigned int time) //small delay
{
int i,j;
for(i=0;i&lt;time;i++)
for(j=0;j&lt;10;j++);

}

void ldelay(unsigned int time) //long delay
{
int i,j;
for(i=0;i&lt;time;i++)
for(j=0;j&lt;5000;j++);

}

void LCD_strobe(void) //generate ENABLE pulse
{

IO1SET = EN;
delay(5);
IO1CLR = EN;
delay(5);
}

void GLCD_data(unsigned char ch)
{
IO1CLR = LCD_PORT;
IO1SET = ch&lt;&lt;LCD_SHIFT;
IO1SET = RS;
LCD_strobe();
}

void GLCD_cmd(unsigned char ch)
{
IO1CLR = LCD_PORT;
IO1SET = ch&lt;&lt;LCD_SHIFT;
IO1CLR = RS;
LCD_strobe();
}

void GLCD_init()
{
int i;

PINSEL0 = 0; //set pins as GPIO
PINSEL1 = 0;
PINSEL2 = 0;

IODIR1 = LCD_PORT | RS | EN | CS1 | CS2 | GRST | RW; //set pins as output

IOSET1 = GRST | CS1 | CS2;
IOCLR1 = RW | RS | EN;

for(i=0;i&lt;10;i++)
GLCD_cmd(0x3F); //Display ON
GLCD_cmd(0x40); //Set Y address as 0 (range 0-63)
GLCD_cmd(0xB8); //Set X address as 0 (page address) (range
0-7)
}
int main()
{
int i,j,l,m;
GLCD_init();

for(i=1;i&lt;=6;i++)
{
IO1SET = CS1; //select controller 1
IO1CLR = CS2;
GLCD_cmd(0xB8 | i);
for(j=29;j&lt;=42;j++)

{
GLCD_cmd(0x40| j);

GLCD_data(0x00); // To send the high values at those locations rows and columns of

GLCD
}
}

for(l=3;l&lt;=4;l++)
{
// IO1SET = CS1;
// IO1CLR = CS2;
GLCD_cmd(0xB8 | l);
for(m=10;m&lt;=60;m++)
{
GLCD_cmd(0x40 | m);

GLCD_data(0x00); // To send the high values at those locations rows and columns of

GLCD

}
}
}
