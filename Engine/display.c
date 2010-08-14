void UpdateDisplay(){
	oslStartDrawing();

  //Draw World Map
  if (Screen == 0){
    oslDrawImage(World_Map);
    oslEndDrawing();
    oslSyncFrame();
    return;
  }

  //Draw Background
  int XCounter = Background_HScroll;
  while (XCounter < 480){
    if (Background_VTile == 0){	
      Background->x = XCounter;
      Background->y = 272 - Background->sizeY;
      oslDrawImage(Background);
    } else{
      int YCounter = 0;
      while (YCounter < 272){	
        Background->x = XCounter;			
        Background->y = YCounter;
        oslDrawImage(Background);
        YCounter += Background->sizeY;
      }
    }
    XCounter += Background->sizeX;
  }
  
  //Draw Tiles
  int i = 0;
  for (i = 0; i < TileSet_Count; i++){
    oslSetImageTileSize(TileSheet[Tile[i].Sheet], Tile[i].SheetX, Tile[i].SheetY, 16, 16);
    TileSheet[Tile[i].Sheet]->x = Level_Position_X + Tile[i].X;							
    TileSheet[Tile[i].Sheet]->y = Level_Position_Y + Tile[i].Y;
    oslDrawImage(TileSheet[Tile[i].Sheet]);
  }

	//Draw Rayman
  int SheetX = Animation[Animation_Index].Stage * Animation[Animation_Index].ImgWidth;
	int SheetY = Animation[Animation_Index].StartRow * Animation[Animation_Index].ImgHeight;
	if (SheetX >= 512){
    SheetX -= 512;
    SheetY += Animation[Animation_Index].ImgHeight;
	}
	oslSetImageTileSize(Sheet[Animation[Animation_Index].Sheet], SheetX, SheetY, Animation[Animation_Index].ImgWidth, Animation[Animation_Index].ImgHeight);
	if (Rayman_Direction == 0){oslMirrorImageH(Sheet[Animation[Animation_Index].Sheet]);}
	oslDrawImage(Sheet[Animation[Animation_Index].Sheet]);

	oslEndDrawing();
	oslSyncFrame();		
}

void LoadImages(){
	oslSetTransparentColor(RGB(255, 0, 255));
	//Load World Map
	World_Map = oslLoadImageFile("Images/World Map.png", OSL_IN_RAM, OSL_PF_5551);
	if (!World_Map){oslFatalError("Unable to load one or more images.");}
	//Load Background
	Background = oslLoadImageFile("Images/JUNF5.png", OSL_IN_RAM, OSL_PF_5551);
	if (!Background){oslFatalError("Unable to load one or more images.");}
  //Load Tiles
	int i = 0;
	for (i = 0; i < Number_Of_TileSheets; i++){
    char path[200];
		sprintf(path, "Images/TileSheet%d.png", i);
    TileSheet[i] = oslLoadImageFile(path, OSL_IN_RAM, OSL_PF_5551);
    if (!TileSheet[i]){oslFatalError("Unable to load one or more images.");}
  }
  //Load Rayman
	for (i = 0; i < Number_Of_Sheets; i++){
    char path[200];
		sprintf(path, "Images/Sheet%d.png", i);
    Sheet[i] = oslLoadImageFile(path, OSL_IN_RAM, OSL_PF_5551);
    if (!Sheet[i]){oslFatalError("Unable to load one or more images.");}
  }
	oslDisableTransparentColor();
}

void ScrollBackground(){
  int amount = -Level_Position_X;
  if (amount % 2 == 0){amount = amount / 2;}
  else{amount = (amount - 1) / 2;}
  Background_HScroll = -amount;
  while (Background_HScroll > 0){
    sceDisplayWaitVblankStart();
    Background_HScroll -= Background->sizeX;
  }
  while (Background_HScroll <= -Background->sizeX){
    sceDisplayWaitVblankStart();
    Background_HScroll += Background->sizeX;
  }
}
