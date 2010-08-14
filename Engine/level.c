void NewTile(int sheet, int sheetx, int sheety, int x, int y){
	Tile = realloc(Tile, (TileSet_Count + 1) * sizeof(struct TileSet));
	Tile[TileSet_Count].Sheet = sheet;
	Tile[TileSet_Count].SheetX = sheetx;
	Tile[TileSet_Count].SheetY = sheety;
	Tile[TileSet_Count].X = x;
	Tile[TileSet_Count].Y = y;
	TileSet_Count += 1;
}

void LoadLevel(char path[200]){
  //Read Level Contents
	char contents[128*1024];
	int fd;
	int flen = 0;
	if (!(fd = sceIoOpen(path, PSP_O_RDONLY, 0777))) {
		return;
	} else{
		flen = sceIoRead(fd, contents, sizeof(contents));
		if (flen <= 0){return;}
	}
	sceIoClose(fd);
  //Load Level
	int current = 0;
	int cury = -3;
		while(1){
			sceDisplayWaitVblankStart();
			int pos = IndexOfFrom(contents, "\n", current);
			if (pos == -1){break;}
			char theline[2048];
			Substring(theline, contents, current, pos);
			current = pos + 1;
			cury += 1;
			if (Level_Width == -1 || Level_Height == -1){
        int i = 0;
        int total = 0;
        for (i = 0; i < strlen(theline); i++){
          int j = CharToInt(theline[i]);
          if (j != -1){total = (total * 10) + j;}
        }
        if (Level_Width == -1){Level_Width = total * 16;}
        else{Level_Height = total * 16;}
			} else{
        int i = 0;
        int curx = 0;
        int mode = 0;
        int sx = 0;
        int sy = 0;
        for (i = 0; i < strlen(theline); i++){
          if (theline[i] == '-'){
            curx += 1;
          } else if (theline[i] == '|'){
            mode += 1;
            if (mode > 1){
              NewTile(0, (sx * 16), (sy * 16), (curx * 16), (cury * 16));
              mode = 0;
              sx = 0;
              sy = 0;
              curx += 1;
            }
          } else{
            if (mode == 0){
              sx = (sx * 10) + CharToInt(theline[i]);
            } else{
              sy = (sy * 10) + CharToInt(theline[i]);
            }
          }
        }
			}
		}
		if (Level_Width == -1 || Level_Height == -1){
      oslFatalError("Error loading level dimensions.");
		}
		if (Level_Width < 480){Level_Width = 480;}
		if (Level_Height < 272){Level_Height = 272;}
}
