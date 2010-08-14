#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <psppower.h>
#include <pspctrl.h>
#include <pspgu.h>
#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


int IndexOf(char *input, char *message)
{
	int pos = 0;
	int found = 0;
	while(pos < strlen(input)){
		if(input[pos] == message[found]){
			while(found < strlen(message)){
				if(input[pos + found] == message[found]){found++;}
				else{found = 0; break;}
			}
			if(found != 0){return pos;}
		}
		pos++;
	}
	return -1;
}

int IndexOfFrom(char *input, char *message, int start)
{
	int pos = start;
	int found = 0;
	while(pos < strlen(input)){
		if(input[pos] == message[found]){
			while(found < strlen(message)){
				if(input[pos + found] == message[found]){found++;}
				else{found = 0; break;}
			}
			if(found != 0){return pos;}
		}
		pos++;
	}
	return -1;
}

int LastIndexOf(char *input, char *message)
{
	int pos = strlen(input);
	int found = 0;
	while(pos > 0){
		if(input[pos] == message[found]){
			while(found < strlen(message)){
				if(input[pos + found] == message[found]){found++;}
				else{found = 0; break;}
			}
			if(found != 0){return pos;}
		}
		pos--;
	}
	return -1;
}

int LastIndexOfBefore(char *input, char *message, int before)
{
	if(before > strlen(input)){return -1;}
	int pos = before;
	int found = 0;
	while(pos > 0){
		if(input[pos] == message[found]){
			while(found < strlen(message)){
				if(input[pos + found] == message[found]){found++;}
				else{found = 0; break;}
			}
			if(found != 0){return pos;}
		}
		pos--;
	}
	return -1;
}

int Substring(char *input, char *message, int start, int end)
{
	char newinput[2048] = "";
	while(start < end){
		newinput[strlen(newinput)] = message[start];
		start++;
	}
	sprintf(input, newinput);
	return 0;
}

int BetweenText(char *input, char *message, char *first, char *second)
{
	if(IndexOf(message, first) == -1){return -1;}
	int i = IndexOf(message, first) + strlen(first);
	int i2 = IndexOfFrom(message, second, i);
	if(i2 == -1){return -1;}
	char newinput[2048] = "";
	while(i < i2){
		newinput[strlen(newinput)] = message[i];
		i++;
	}
	sprintf(input, newinput);
	return 0;
}

int BetweenTextFrom(char *input, char *message, char *first, char *second, int start)
{
	if(IndexOfFrom(message, first, start) == -1){return -1;}
	int i = IndexOfFrom(message, first, start) + strlen(first);
	int i2 = IndexOfFrom(message, second, i);
	if(i2 == -1){return -1;}
	char newinput[2048] = "";
	while(i < i2){
		newinput[strlen(newinput)] = message[i];
		i++;
	}
	sprintf(input, newinput);
	return 0;
}

int Replace(char *input, char *replace, char *withthis)
{
	int pos = 0;
	while(1){
		int i = IndexOfFrom(input, replace, pos);
		if(i != -1){
			pos = i + strlen(withthis);
			char new[2048] = "";
			int i2 = 0;
			while(i2 < i){
				new[strlen(new)] = input[i2];
				i2++;
			}
			strcat(new, withthis);
			i2 += strlen(replace);
			while(i2 < strlen(input)){
				new[strlen(new)] = input[i2];
				i2++;
			}
			sprintf(input, new);
		}
		else{break;}
	}
	return 0;
}

int ToInt(char *input)
{
	char newinput[2048] = "";
	sprintf(newinput, input);
	Replace(newinput, ",", "");
	int num = 0;
	int i2 = 0;
	int isnegative = 0;
	if (IndexOf(newinput, "-") == 0){
		isnegative = 1;
		i2 = 1;
	}
	while(i2 < strlen(newinput)){
		int subnum = 0;
		if(newinput[i2] == '0'){subnum = 0;}
		else if(newinput[i2] == '1'){subnum = 1;}
		else if(newinput[i2] == '2'){subnum = 2;}
		else if(newinput[i2] == '3'){subnum = 3;}
		else if(newinput[i2] == '4'){subnum = 4;}
		else if(newinput[i2] == '5'){subnum = 5;}
		else if(newinput[i2] == '6'){subnum = 6;}
		else if(newinput[i2] == '7'){subnum = 7;}
		else if(newinput[i2] == '8'){subnum = 8;}
		else if(newinput[i2] == '9'){subnum = 9;}
		else{return -1;}
		num = (num * 10) + subnum;
		i2++;
	}
	if (isnegative == 0){
		return num;
	} else{
		return -num;
	}
}

int CharToInt(char input)
{
	if(input == '0'){return 0;}
	else	if(input == '1'){return 1;}
	else	if(input == '2'){return 2;}
	else	if(input == '3'){return 3;}
	else	if(input == '4'){return 4;}
	else	if(input == '5'){return 5;}
	else	if(input == '6'){return 6;}
	else	if(input == '7'){return 7;}
	else	if(input == '8'){return 8;}
	else	if(input == '9'){return 9;}
	else{return -1;}
}

int InstancesOf(char *input, char *tofind)
{
	int count = 0;
	int pos = -1;
	while(1){
		pos = IndexOfFrom(input, tofind, pos + 1);
		if(pos != -1){count += 1;}
		else{break;}
	}
	return count;
}

int RemoveFirstLines(char *input, int numlines, int type)
{
	if(IndexOf(input, "\n") == -1){return -1;}
	int num1 = 0;
	while(num1 < numlines){
		int i = IndexOf(input, "\n");
		if(i == -1){return -1;}
		Substring(input, input, i + 1, strlen(input));
		if(type == 1 && input[0] == '\n'){numlines += 1;}
		num1 += 1;
	}
	return 0;
}

int AreEqual(char *input, char *input2)
{
	if(IndexOf(input, input2) == 0 && strlen(input) == strlen(input2)){
		return 1;
	} else{
		return 0;
	}
}

int StartsWith(char *input, char *input2)
{
	if(IndexOf(input, input2) == 0){
		return 1;
	} else{
		return 0;
	}
}

int EndsWith(char *input, char *input2)
{
	int pos = LastIndexOf(input, input2);
	if(pos == strlen(input) - strlen(input2) && pos != -1){
		return 1;
	} else{
		return 0;
	}
}
