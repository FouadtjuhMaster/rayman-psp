//General Variables
int Screen = 0;

//Audio
OSL_SOUND *Background_Music;

//Images
#define Number_Of_TileSheets 1
#define Number_Of_Sheets 1
OSL_IMAGE *World_Map, *Background, *TileSheet[Number_Of_TileSheets], *Sheet[Number_Of_Sheets];

//Rayman Variables
int Rayman_Direction = 1;
int Start_Gap = 24;
int Rayman_Width = 16;

//Level Variables
int Level_Width = -1;
int Level_Height = -1;
int Level_Position_X = 0;
int Level_Position_Y = 0;
int Background_VTile = 0;
int Background_HScroll = 0;
int TileSet_Count = 0;
struct TileSet
{
  int Sheet;
  int SheetX;
	int SheetY;
	int X;
	int Y;
};
struct TileSet *Tile;

//Animation Variables
SceUID ThreadID_Animate;
int Animation_Index = -1;
int AnimationSet_Count = 0;
struct AnimationSet
{
  int Sheet;
  int StartRow;
	int ImgWidth;
	int ImgHeight;
	int Stage;
	int MaxStages;
	int Delay;
	int Repeat;
};
struct AnimationSet *Animation;
