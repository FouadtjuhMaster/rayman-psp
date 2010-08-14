int Animate(SceSize args, void *argp)
{
	Animation[Animation_Index].Stage = 0;
	while(1){
		sceDisplayWaitVblankStart();
		sceKernelDelayThread(Animation[Animation_Index].Delay);
		Animation[Animation_Index].Stage++;
    if (Animation[Animation_Index].Stage >= Animation[Animation_Index].MaxStages){
      if (Animation[Animation_Index].Repeat == 1){
        Animation[Animation_Index].Stage = 0;
      } else{
        Animation[Animation_Index].Stage -= 1;
      }
    }
	}
	return 0;
}

void SetAnimation(int index){
	if (Animation_Index != index){
		Animation_Index = index;
		sceKernelTerminateDeleteThread(ThreadID_Animate);
		ThreadID_Animate = sceKernelCreateThread("Animate", Animate, 0x18, 0x10000, PSP_THREAD_ATTR_USER, NULL);
		if (ThreadID_Animate < 0){oslFatalError("Unable to create animation thread.");}
		else{sceKernelStartThread(ThreadID_Animate, 0, NULL);}
	}
}

void NewAnimation(int sheet, int startrow, int imgwidth, int imgheight, int maxstages, int delay, int repeat){
	Animation = realloc(Animation, (AnimationSet_Count + 1) * sizeof(struct AnimationSet));
	Animation[AnimationSet_Count].Sheet = sheet;
	Animation[AnimationSet_Count].StartRow = startrow;
	Animation[AnimationSet_Count].ImgWidth = imgwidth;
	Animation[AnimationSet_Count].ImgHeight = imgheight;
	Animation[AnimationSet_Count].Stage = 0;
	Animation[AnimationSet_Count].MaxStages = maxstages;
	Animation[AnimationSet_Count].Delay = delay;
	Animation[AnimationSet_Count].Repeat = repeat;
	AnimationSet_Count += 1;
}

void SetX(int x){
  Sheet[Animation[Animation_Index].Sheet]->x = x;
}

void SetY(int y){
  Sheet[Animation[Animation_Index].Sheet]->y = y;
}

void MoveX(int x){
  //Check For Collisions & Reduce X Appropriately
  if (x < - (Sheet[Animation[Animation_Index].Sheet]->x + Start_Gap)){
    x = - (Sheet[Animation[Animation_Index].Sheet]->x + Start_Gap);
  }
  if (x > 480 - (Sheet[Animation[Animation_Index].Sheet]->x + Start_Gap + Rayman_Width)){
    x = 480 - (Sheet[Animation[Animation_Index].Sheet]->x + Start_Gap + Rayman_Width);
  }
  //Move
  int RaymanStart = Sheet[Animation[Animation_Index].Sheet]->x + Start_Gap;
  int RaymanEnd = RaymanStart + Rayman_Width;
  int LevelFreedom = 480 - Level_Width;
  if (x < 0){
    int dif = RaymanStart - 280;
    if (Level_Position_X >= 0 || dif >= -x){
      Sheet[Animation[Animation_Index].Sheet]->x += x;
    } else{
      if (dif > 0 && dif < -x){
        Sheet[Animation[Animation_Index].Sheet]->x -= dif;
        x += dif;
        dif = 0;
      }
      if (dif <= 0){
        if (Level_Position_X - x > 0){
          Sheet[Animation[Animation_Index].Sheet]->x += Level_Position_X;
          Level_Position_X = 0;
        } else{
          Level_Position_X -= x;
        }
      }
    }
  } else{
    int dif = 200 - RaymanEnd;
    if (Level_Position_X <= LevelFreedom || dif >= x){
      Sheet[Animation[Animation_Index].Sheet]->x += x;
    } else{
      if (dif > 0 && dif < x){
        Sheet[Animation[Animation_Index].Sheet]->x += dif;
        x -= dif;
        dif = 0;
      }
      if (dif <= 0){
        if (Level_Position_X - x < LevelFreedom){
          Sheet[Animation[Animation_Index].Sheet]->x += Level_Position_X - LevelFreedom;
          Level_Position_X = LevelFreedom;
        } else{
          Level_Position_X -= x;
        }
      }
    }
  }
}

void MoveY(int y){
  Sheet[Animation[Animation_Index].Sheet]->y += y;
}

void AdjustCamera(){
  int tochange = 0;
  int RaymanStart = Sheet[Animation[Animation_Index].Sheet]->x + Start_Gap;
  int RaymanEnd = RaymanStart + Rayman_Width;
  int LevelFreedom = 480 - Level_Width;
  if (Rayman_Direction == 0){
    if (RaymanStart < 280 && Level_Position_X < 0){
      tochange = 280 - RaymanStart;
      if (Level_Position_X + tochange >= 0){tochange = -Level_Position_X;}
    }
  } else{
    if (RaymanEnd > 200 && Level_Position_X > LevelFreedom){
      tochange = 200 - RaymanEnd;
      if (Level_Position_X + tochange <= LevelFreedom){tochange = LevelFreedom - Level_Position_X;}
    }
  }
  if (tochange >= 4){
    Level_Position_X += 4;
    Sheet[Animation[Animation_Index].Sheet]->x += 4;
  } else if (tochange <= -4){
    Level_Position_X -= 4;
    Sheet[Animation[Animation_Index].Sheet]->x -= 4;
  } else{
    Level_Position_X += tochange;
    Sheet[Animation[Animation_Index].Sheet]->x += tochange;
  }
}
