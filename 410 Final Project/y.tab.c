
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 3 "project3.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define YYSTYPE char *

struct castle{
	int num_items;		//keep track of the # of items in each room
	char item_name[20];	//store the item name in room
	char enemy_name[20];	//store the enemy names
	int talkFlag;
};

struct inventory{
	int inv_count;		//keep track of the # of items in the players inventory
	char inv_name[20];	//store the item's name
};

struct player{	//self
	int health;
	int armor_rating;
	int attack_power;
	int xp;
};

struct equipment{
	char name[30];
	int count;
};

struct enemy{
	int enemy_count;
	int health;
	int armor_rating;
	int attack_power;
	char status[20];
	int experience;
	char item[20];
};

int currentRoom, examineFlag, openFlag, fightFlag, talkFlag, dirFlag;
struct castle room[18];
struct inventory bag[9];
struct enemy opponent[3]; 
struct player self;
struct equipment equip[3];

void useItem(char *);
void printRoom();
void startGame();
void stopRun();
void takeItem();
void printInv();
void examineArea();
void openObject();
void soldierFight(char *, int);
void soldierChat();
void wrongDir();
void exitGame();
void move(char *);
void equipItem(char *);
void equippedItems();

int main(){
	yyparse();
}

//handle error's
yyerror(char * msg){
	main();
}

int yywrap() {
  return 1;
}

/*initialize the rooms*/
void startGame(){
	int i;

	/*Player*/
	self.health = 100;
	self.armor_rating = 25;
	self.attack_power = 25;
	talkFlag = 0;
	
	/*Items within the rooms*/
	strcpy(room[0].item_name, "Iron Sword");
	strcpy(room[2].item_name, "Leather Chest Guard");
	strcpy(room[5].item_name, "Leather Boots");
	strcpy(room[6].item_name, "Small Health Potion");
	strcpy(room[8].item_name, "Bronze Skeleton Key");
	strcpy(room[10].item_name, "Leather Gloves");
	strcpy(room[12].item_name, "Medium Health Potion");
	strcpy(room[15].item_name, "Steel Sword");
	strcpy(room[17].item_name, "100 gold pieces");

	room[4].talkFlag = 0;
	room[11].talkFlag = 0;
	room[14].talkFlag = 0;
	room[16].talkFlag = 0;
	
	room[0].num_items = 1;
	room[2].num_items = 1;
	room[5].num_items = 1;
	room[6].num_items = 1;
	room[8].num_items = 1;
	room[10].num_items = 1;
	room[12].num_items = 1;
	room[15].num_items = 1;
	room[17].num_items = 1;
	
	for(i = 0; i < 9; i++)
		bag[i].inv_count = 0;

	for(i = 0; i < 4; i++)
		equip[i].count = 0;

	/*Enemies within the rooms*/
	strcpy(room[4].enemy_name, "Soldier");
	opponent[0].enemy_count = 1;
	opponent[0].health = 100;
	opponent[0].armor_rating = 50;
	opponent[0].attack_power = 25;
	opponent[0].experience = 1000;
	strcpy(room[11].enemy_name, "Soldier");
	opponent[1].enemy_count = 1;
	opponent[1].health = 100;
	opponent[1].armor_rating = 50;
	opponent[1].attack_power = 25;
	opponent[1].experience = 1000;
	strcpy(room[14].enemy_name, "Old Man");
	opponent[2].enemy_count = 1;
	opponent[2].health = 50;
	strcpy(opponent[2].item, "small silver key");
	strcpy(room[16].enemy_name, "Great Knight");
	opponent[3].enemy_count = 1;
	opponent[3].health = 200;
	opponent[3].armor_rating = 150;
	opponent[3].attack_power = 40;
	opponent[3].experience = 4000;

	currentRoom = 0;
	printf("You've just woken up, but don't recognize any of your surroundings or how you ended up here without all of your weapons and armor. After examining the room, it appears as if you are in a castle. There are also three other doors that should lead to some answers: one to the north, another south, and the final to the east. It could be dangerous moving around without a weapon. Perhaps you should examine the area for a weapon before leaving.\n\n");

}

/*Compare user's choice of direction with current location*/
void move(char * user_Direction){
	int lock = 1;
	dirFlag = 1;
	
	if(opponent[0].health == 0 || opponent[1].health == 0 || opponent[2].health == 0)
		fightFlag = 0;

	if(strcmp(user_Direction, "north") == 0){
		
		switch(currentRoom){
			case 1: case 2: case 5: case 8: case 10:
			case 13: case 15: wrongDir(); dirFlag = 0; break;
			case 0: currentRoom = 1; break;
			case 3: currentRoom = 0; break;
			case 4: 
				if(fightFlag == 1 || opponent[0].health != 0)
					stopRun();
				else	
					currentRoom = 5; 
				break;
			case 6: currentRoom = 3; break;
			case 7: currentRoom = 6; break;
			case 9: currentRoom = 10; break;
			case 11: 
				if(fightFlag == 1 || opponent[1].health != 0)
					stopRun();
				else	
					currentRoom = 13; 
				break;
			case 12: currentRoom = 11; break;
			case 14: currentRoom = 15; break;
			case 16: 
				if(fightFlag == 1)
					stopRun();
				else	
					currentRoom = 14; 
				break;
			case 17: currentRoom = 16; break;
		}
	} else if(strcmp(user_Direction, "south") == 0){

		switch(currentRoom){
			case 2: case 4: case 7: case 8: case 9: 
			case 12: case 17: wrongDir(); dirFlag = 0; break;
			case 0: currentRoom = 3; break;
			case 1: currentRoom = 0; break;
			case 3: currentRoom = 6; break;
			case 6: currentRoom = 7; break;
			case 5: currentRoom = 4; break;
			case 10: currentRoom = 9; break;
			case 13: currentRoom = 11; break;
			case 11:
				if(fightFlag == 1 || opponent[1].health != 0)
					stopRun();
				else	
					currentRoom = 12; 
				break;
			case 15: currentRoom = 14; break;
			case 14: 
				if(bag[4].inv_count == 0){
						printf("The door is locked, and looks as if it requires a fairly large key. You need to find it if you wish to continue.\n\n");				
				} else{
					printf("Unlocking the door with the Bronze Skeleton Key.\n\n");
					currentRoom = 16;
				}
				
				break;
			case 16: 
				if(fightFlag == 1 || opponent[3].health != 0)
					stopRun();
				else	
					currentRoom = 17; 
				break;
		}	
	} else if(strcmp(user_Direction, "east") == 0){
		
		switch(currentRoom){
			case 1: case 3: case 5: case 7: case 12:
			case 11: case 9: case 10: case 15: case 14:
			case 16: wrongDir(); dirFlag = 0; break;
			case 0: currentRoom = 9; break;
			case 2: currentRoom = 1; break;
			case 4: 
				if(fightFlag == 1)
					stopRun();
				else	
					currentRoom = 3; 
				break;
			case 6: currentRoom = 11; break;
			case 13: currentRoom = 14; break;
			case 8: currentRoom = 7; break;
			case 17: currentRoom = 18; break;
		}
	} else if(strcmp(user_Direction, "west") == 0){
		
		switch(currentRoom){
			case 0: case 2: case 5: case 4: case 6: case 8:
			case 10: case 13: case 12: case 15:
			case 16: case 17: wrongDir(); dirFlag = 0; break;
			case 1: currentRoom = 2; break;
			case 3: currentRoom = 4; break;
			case 7:
				if(bag[9].inv_count == 0){
					printf("The door is locked. Looks like you'll need to find the key if you wish to enter this room.\n\n"); 
					lock = 0;
				} else if(bag[4].inv_count == 0){
					printf("Unlocking the door with the small silver key.\n\n");
					currentRoom = 8;
				} else
					currentRoom = 8; 

				break;
			case 9: currentRoom = 0; break;
			case 11: 
				if(fightFlag == 1)
					stopRun();
				else	
					currentRoom = 6; 
				break;
			case 14: currentRoom = 13; break;
		}
	} else
		printf("The given direction is not recognized.\n\n");
	
	if(dirFlag == 1 && lock == 1)
		printRoom();
}

void stopRun(){
	printf("The enemy won't let you escape that easily, quickly manuevering himself to keep you from leaving. You can't make a move to the door without leaving yourself open to a potentially fatal attack.\n\n");
	dirFlag = 0;
}

void wrongDir(){
	printf("It doesn't look like you can move this way since there isn't a door on this side of the room.\n\n");
}

/*Compare user action choice to available game actions*/
void executeAction(char *user_action){
	int i;

	if(strcmp(user_action, "look") == 0)
		printRoom();
 	else if(strcmp(user_action, "take") == 0 || strcmp(user_action, "grab") == 0)
		takeItem();
	else if(strcmp(user_action, "search") == 0 || strcmp(user_action, "examine") == 0)
		examineArea();
	else if(strcmp(user_action, "inventory") == 0)
		printInv();
	else if(strcmp(user_action, "open") == 0)
		openObject();	
	
}

void takeItem(){
	
		if(currentRoom == 0 && room[0].num_items != 0 && examineFlag == 1){
			printf("Picking up the sword.\n\n");
			strcpy(bag[0].inv_name, "Iron Sword");
			bag[0].inv_count++;
			room[0].num_items--;
			examineFlag = 0;		
		} else if(currentRoom == 2 && room[2].num_items != 0){
			printf("Taking the leather armor.\n\n");
			strcpy(bag[1].inv_name, "Leather Chest Guard");
			bag[1].inv_count++;
			room[2].num_items--;
		}else if(currentRoom == 5 && room[5].num_items != 0){
			printf("Taking the leather boots.\n\n");
			strcpy(bag[2].inv_name, "Leather Boots");
			bag[2].inv_count++;
			room[5].num_items--;
		} else if(currentRoom == 6 && room[6].num_items != 0 && examineFlag == 1){
			printf("Taking the health potion.\n\n");
			strcpy(bag[3].inv_name, "Small Health Potion");
			bag[3].inv_count++;
			room[6].num_items--;
			examineFlag = 0;
		} else if(currentRoom == 8 && room[8].num_items != 0 && openFlag == 1){
			printf("You got the Bronze Skeleton Key!\n\n");
			strcpy(bag[4].inv_name, "Bronze Skeleton Key");
			bag[4].inv_count++;
			room[8].num_items--;
			openFlag = 0;
		} else if(currentRoom == 10 && room[10].num_items != 0){
			printf("Taking the leather gloves.\n\n");
			strcpy(bag[5].inv_name, "Leather Gloves");
			bag[5].inv_count++;
			room[10].num_items--;
		} else if(currentRoom == 12 && room[12].num_items != 0 && examineFlag == 1){
			printf("Taking the health potion.\n\n");
			strcpy(bag[6].inv_name, "Medium Health Potion");
			bag[6].inv_count++;
			room[12].num_items--;
			examineFlag = 0;
		} else if(currentRoom == 15 && room[15].num_items != 0){
			printf("Taking the sword.\n\n");
			strcpy(bag[7].inv_name, "Steel Sword");
			bag[7].inv_count++;
			room[15].num_items--;
		} else if(currentRoom == 17 && room[17].num_items != 0 && openFlag == 1){
			printf("Taking the gold.\n\n");
			strcpy(bag[8].inv_name, "100 gold pieces");
			bag[8].inv_count++;
			room[17].num_items--;
			openFlag = 0;
		} else
			printf("There's nothing of use to pick up.\n\n");	
	
}

void printInv(){
	int i;
	int check = 0;

	for(i = 0; i < 10; i++)
		if(bag[i].inv_count == 1)
			check = 1;	
	
	if(!check)
		printf("You aren't carrying anything.\n\n");
	else{
		printf("You are carrying:\n\n");
		for(i = 0; i < 10;i++){
			if(bag[i].inv_count == 1)
				printf("%s\n", bag[i].inv_name);
		} 
		printf("\n");
		
	}	
}

void equipItem(char *item){
	
	if(strcmp(item, "iron") == 0 && bag[0].inv_count == 1 && equip[0].count == 0){
		if(strcmp(equip[0].name, "Steel Sword") == 1)
			printf("Equipped Iron Sword over Steel Sword.\n\n");
		else
			printf("Equipped Iron Sword.\n\n");

		strcpy(equip[0].name, "Iron Sword");
		self.attack_power = 35;
		equip[0].count = 1;	
	} else if(strcmp(item, "steel") == 0 && bag[7].inv_count == 1){
		if(strcmp(equip[0].name, "Iron Sword") == 1)
			printf("Equipped Steel Sword over Iron Sword.\n\n");
		else
			printf("Equipped Steel Sword.\n\n");

		strcpy(equip[0].name, "Steel Sword");
		self.attack_power = 50;
		equip[0].count = 1;		
	} else if(strcmp(item, "chest") == 0 && bag[1].inv_count == 1 && equip[1].count == 0){
		printf("Equipped chest guard.\n\n");
		strcpy(equip[1].name, "Leather Chest Guard");
		self.armor_rating += 25;
		equip[1].count = 1;	
	} else if(strcmp(item, "boots") == 0 && bag[2].inv_count == 1 && equip[2].count == 0){
		printf("Equipped boots.\n\n");
		strcpy(equip[2].name, "Leather Boots");
		self.armor_rating += 10;
		equip[2].count = 1;
	} else if(strcmp(item, "gloves") == 0 && bag[5].inv_count == 1 && equip[3].count == 0){
		printf("Equipped gloves.\n\n");
		strcpy(equip[3].name, "Leather Gloves");
		self.armor_rating += 10;
		equip [3].count = 1;
	} else
		printf("You have nothing to equip.\n\n");

}

void equippedItems(){
	int i;
	
	printf("Currently Equipped Items: \n\n");
	for(i = 0; i < 4; i++){
		if(equip[i].count == 1)
			printf("%s\n", equip[i].name);	
	}
	
}

void examineArea(){
	
	switch(currentRoom){
		case 0:
		case 6:
		case 12:
		case 15:
			examineFlag = 1;
			printRoom();
			break;
	}
	
}

/*Checks player's inventory for available potions to drink*/
void useItem(char *item){
	int i;

	if(bag[3].inv_count || bag[6].inv_count){
		if(strcmp(item, "small") == 0 && strcmp(bag[3].inv_name, "Small Health Potion") == 0){
			
			if(self.health == 100){
				printf("You don't need to drink that right now since you have full health.\n\n");			
			} else{
				printf("You drank a small potion and recovered a small amount of health.\n\n");
				bag[3].inv_count--;

				for(i = self.health; i < 100; i++){
					if(i < 50 && self.health < 100)
						self.health++;				
				} 
			}
		
		} else if(strcmp(item, "medium") == 0 && strcmp(bag[1].inv_name, "Medium Health Potion") == 0){
			
			if(self.health == 100){
				printf("You don't need to drink that right now since ou have full health.\n\n");			
			} else{
				printf("You drank a medium potion and recovered a fair amount of health.\n\n");	
				bag[6].inv_count--;	

				for(i = self.health; i < 100; i++){
					if(self.health < 100)
						self.health++;				
				}	
			}
		
		}
	}
	else
		printf("There's nothing in your inventory to use.\n\n");
}

void openObject(){
	
	if((currentRoom == 8 || currentRoom == 17) && openFlag == 0){
		printf("Opening the chest...time to claim your prize.\n\n");
		openFlag = 1;
	} else
		printf("You have already opened the chest in this room.\n\n");
		
}

void fightEnemy(char *action){
	
	fightFlag = 1;	
	
	if(currentRoom == 4 && opponent[0].health != 0){
		soldierFight(action, 0);
	} else if(currentRoom == 11 && opponent[1].health != 0){
		soldierFight(action, 1);
	} else if(currentRoom == 14 && opponent[2].health != 0){
		printf("You quickly draw your sword and move in on the old man, lunging. His eyes widen in horror and disbelief as your sword burrows into his chest, stealing his life.\n\n");
		opponent[2].health = 0;
		opponent[2].enemy_count--;
		printf("A silver key falls from the old mans hand, and you pick it up.\n\n");
		strcpy(bag[9].inv_name, opponent[2].item);
		bag[9].inv_count++;
	} else if(currentRoom == 16 && opponent[3].health != 0){
	} else
		printf("There's nobody here to fight...\n\n");	
	
}

void soldierFight(char *action, int i){

	if(opponent[0].health == 0 || opponent[1].health == 0){
		printf("You feel much stronger and more confident after your first battle. After sizing up the opponent it's obvious that his level of skill is similar to that of the first soldier you encountered. You'd rather finish this fight as fast as possible. With a blinding display of speed and skill you rush the man and attack with a variety of slashes, deft parries, and feints...easily putting the guard on the defensive.\n");
		printf("The soldier realizes he's made a grave mistake in threatening to arrest you, but his pride will not allow him to falter here.\n");
		printf("Purposefully leaving yourself open for an attack from the side, you bait the man to attack. Desperation driving away all clear thought, the soldier greedily takes the offered opening and lunges towards your side with his sword in the lead.\n");
		printf("Quickly spinning towards the mans body while reversing the direction of your hold on the sword, you plunge it into his stomach with your back facing him.\n");
		opponent[i].health = 0;
		opponent[i].enemy_count--;
		self.xp += opponent[i].experience;
		fightFlag = 0;
	} else{
		if(strcmp(action, "attack") == 0){

			if(opponent[i].health == 100 && opponent[i].armor_rating == 50 && self.health == 100 ){
				printf("You swing your sword hard at the soldier, catching him by surprise with your level of skill. You score a direct blow to his armored side.\n");
				opponent[i].armor_rating -= self.attack_power;
				printf("He felt that one, and narrows his eyes in fury as he counterattacks.\n");
				printf("In his haste to counter, along with your lightweight armor and manueverability, the enemy only grazes your chest.\n");
				self.armor_rating -= (opponent[i].attack_power - 20); 
				printf("After exchanging parries and dodging one another's attacks, it's apparent that you have the upper hand in both skill and stamina.\n");
				printf("The enemy's movements are slowing, and his sword arm is heavy. It's time to go on the offensive.\n");
			} else if(strcmp(opponent[i].status, "tripped") == 0){
				printf("Before the soldier has time to regain his wits and footing, you move in for the killing strike, plunging your sword straight down into his chest, through his armor.\n\n");
				opponent[i].health = 0;
				fightFlag = 0;
				self.xp += opponent[i].experience;
				opponent[i].enemy_count = 0;						
			} else if(strcmp(opponent[i].status, "wide open") == 0){
				printf("Quickly and smoothly, you move in for the finishing strike, not giving the enemy the chance to recover his weapon.\n\n");
				opponent[i].health = 0;
				fightFlag = 0;
				self.xp += opponent[i].experience;
				opponent[i].enemy_count = 0;		
			} else if(opponent[i].health < 100 || opponent[i].armor_rating < 50){
				printf("Your opponent is breathing heavily and is moving slower than when the fight began, but you are still in top fighting shape. You move in on him with a few quick slashes and knock away his sword after cutting the opponents wrist, leaving him wide open.\n\n");
				opponent[i].health -= (self.attack_power - 20);
				strcpy(opponent[i].status, "wide open");
			} 
		} else if(strcmp(action, "trip") == 0){
			if(opponent[i].armor_rating < 50){
				printf("You feign an attack to the enemies left. Panicking from the realization at your superior skill, the solider hastily lifts his sword to block. With your right leg, you make a fast sweeping kick along the ground, tripping him up and dislodging his weapon.\n\n");
				strcpy(opponent[i].status, "tripped");	
			} else{
				printf("You rush the opponent with quick strikes, catching him off guard with your fast charge. The opponent is still fresh, however, and when you make a feint to his right side and try to sweep his legs out from underneath him, he easily recognizes the ploy and steps back from your leg, countering with a direct hit to your left arm.\n\n");
				self.health -= opponent[i].attack_power;
			}
		}
	}
}


void talk(){
	
	if(currentRoom == 4 && room[4].talkFlag == 0){
		soldierChat();
		room[4].talkFlag++;
	} else if(currentRoom == 11 && room[11].talkFlag == 0){
		soldierChat();
		room[11].talkFlag++;
	} else if(currentRoom == 14 && room[14].talkFlag == 0){
		printf(" ");
		room[14].talkFlag++;
	} else if(currentRoom == 16 && room[16].talkFlag == 0){
		printf(" ");
		room[16].talkFlag++;
	} else
		printf("There's nobody here to talk with.\n");
}

void soldierChat(){
	
	if(opponent[0].health == 0 || opponent[1].health == 0){
			printf("Since it's another soldier, you don't feel like talking as it will probably be a waste of time, but you need to get through the door he is guarding. Trying once more, you slowly approach the soldier, keeping your hands far away from your weapon.\n");
			printf("Soldier: Stop right there! I don't know how you came to be here, but intruders are strictly forbidden. I won't hurt you, but I will have to arrest you. Throw your weapon aside.\n\n");
			printf("You've come this far. You can't let yourself be arrested.\n\n");
			fightFlag = 1;
	} else{
			printf("Calling out to the soldier only ends up startling him. He hurriedly turns towards your direction and puts his hand on the pommel of his sword.\n");
			printf("Soldier: How did you get in here!?\n...\n");
			printf("Soldier: Nevermind, it doesn't matter. I don't recognize you, and you shouldn't be in the castle. Hmph, I was bored anyway. Looks like I can alleviate that by killing you!\n");
			printf("The soldier pulls out his weapon, slowly advancing towards you with a crooked smile.\n\n");
			fightFlag = 1;
	}

}

void getStats(){
	
	printf("---Player Stats---\n");
	printf("Health:        	%d\n", self.health);
	printf("Armor Rating:  	%d\n", self.armor_rating);
	printf("Attack Power:  	%d\n\n", self.attack_power);	
	
}

void displayHelp(){

	printf("Available commands:\n\n");
	printf("Movement: 	move, walk, run, go (plus the direction)\n");
	printf("Direction:	north, south, east, west\n");
	printf("Actions: 	take, look, inventory, open, grab, search, examine\n");
	printf("Potion use: 	drink, use (plus the size)\n");
	printf("Size Potion: 	Small, Medium\n");
	printf("Fighting: 	attack, stab, trip, lunge\n");
	printf("Conversing: 	talk, speak\n");
	printf("Quit Game: 	exit, quit, leave, terminate, finished\n");
	
}


/*Display information on the room the player moves to*/
void printRoom(){
	
	switch(currentRoom){
		case 0:
			if(bag[0].inv_count == 0 && examineFlag == 1){
				printf("There's a pile of lumber in a corner that appears to be covering something. Removing it has revealed a long case. After opening the case, a weapon is revealed. What luck! You should take it.\n\n");
			}else
				printf("This is the room where everything started. There are still three doors leading north, south, and east.\n\n");
			break;
		case 1:
			//printf("bag 1: %d\n", bag[1].inv_count); //testing
			if(bag[1].inv_count == 0)
				printf("There doesn't appear to be anything of interest in this room, but there is a single door to the west, or you can go back the way you came.\n\n");
			else
				printf("You should move south since the door to the west only leads to the room where you found the chest piece.\n\n");
			break;
		case 2:
			//printf("bag 1: %d\n", bag[1].inv_count); //testing
			if(bag[1].inv_count == 0 && bag[2].inv_count == 1)
				printf("It's another dead end, but it also looks like another piece of leather armor is here. This time it's a leather chest piece. This should provide you with more protection than what you're currently wearing.\n\n");
			else if(bag[1].inv_count == 0)
				printf("Looks like this is a dead end. However, you can see an armor stand with what looks to be a leather chest piece. This should be beneficial.\n\n"); 
			else
				printf("You found the leather chest piece in this room, but nothing else of interest. You should probably go back the way you came.\n\n");		
			break;
		case 3:
			printf("This room is larger than the previous room, but you can't see anything that will give you clues about how you got here. There are exits to the north, south, and west.\n\n");
			break;
		case 4:
			if(opponent[0].health == 0)
				printf("The room in which you defeated a soldier.\n\n");
			else if(opponent[1].enemy_count == 0)
				printf("There appears to be another soldier in this room...\n\n"); 
			else
				printf("Looks like somebody else is already in this room. He appears to be a soldier, guarding a door to the north. Maybe you should try and talk with him.\n\n");
			break;
		case 5:
			if(bag[2].inv_count == 0 && bag[1].inv_count == 1)
				printf("It's another dead end, but it also looks like another piece of leather armor is here. This time it's leather boots. These should provide you with more protection than what you're currently wearing.\n\n");
			else if(bag[2].inv_count == 0)
				printf("Looks like this is a dead end. However, you can see a rack of leather boots. There's bound to be one your size, and should provide you with more protection than what you're currently wearing.\n\n");
			break;
		case 6:
			if(bag[3].inv_count == 0 && examineFlag == 1){
				printf("After searching the desk, you came across a hidden drawer with a vial of liquid, maybe it will help you.\n\n");
			} else if(bag[3].inv_count == 1)
				printf("This is the room where you found the small potion. There are doors to the north, south, and east.\n\n");
			else
				printf("Another room that has three doors. This rooms looks like someone's bedchamber. There's a desk by the bed and across the room is a fireplace. Maybe you can find something useful in the desk.\n\n");
			break;
		case 7:
			printf("There's a door to the west, but nothing else of interest can be seen.\n\n");
			break;	
		case 8:
			printf("This room is pretty small, but there's a big chest in the very center. I doubt there would be a trap at this point.\n\n");
			break;	//open action
		case 9:
			//printf("Bag count for gloves: %d\n", bag[5].inv_count);
			if(bag[5].inv_count == 0)
				printf("There doesn't appear to be anything of interest in this room, but there is a single door leading north, or you can go back the way you came.\n\n");
			else
				printf("You should move west since the door to the north only leads to the room where you found the leather gloves.\n\n");
			break;
		case 10:
			if((bag[1].inv_count == 1 || bag[2].inv_count == 1) && bag[5].inv_count == 0)
				printf("It's another dead end, but it also looks like another piece of leather armor is here. This time it's leather gloves. This should provide you with more protection along with what you're currently wearing.\n\n");
			else if(bag[5].inv_count == 0)
				printf("Looks like this is a dead end. However, you can see some leather gloves on the mantle. These should provide good protection.\n\n"); 						
			else
				printf("You found the leather gloves in this room, but nothing else of interest. You should probably go back the way you came.\n\n");		
			break;
		case 11:
			if(opponent[1].health == 0)
				printf("You defeated a soldier in this room.\n\n");
			else if(opponent[0].enemy_count == 0)
				printf("There appears to be another soldier in this room...behind him is a door.\n\n"); 
			else
				printf("Looks like somebody else is already in this room. He appears to be a soldier, guarding the door behind him. Thankfully not a knight since you probably couldn't handle one right now. Maybe you should try and talk with him.\n\n"); 
			break;
		case 12:
			if(bag[6].inv_count == 0 && examineFlag == 1){
				printf("Looks like there's a pouch on the fire place mantle. Examining the contents has revealed a fairly large vial. This could be useful.\n\n");
			}else if(bag[6].inv_count == 1)
				printf("This is the room where you found the medium potion. There are no other doors here.\n\n");
			else
				printf("There are no other doors here, and it looks like someone's bedchamber. There's a desk by the bed and across the room is a fireplace. Maybe you can find something useful by the fireplace.\n\n");
			break;
		case 13:
			printf("You've found a staircase that leads from north to east. Whatever's at the end should be interesting.\n\n");
			break;
		case 14:
			if(opponent[2].health == 50)
				printf("This room is completely different from all of the previous rooms. There's a long table in the middle of the room, with a lot of leftover food. It appears as if a feast was recently held here. It finally looks like you're making some progress. There are three doors including the one you just came from. At the far end of the room is a harmless looking old man. Maybe you can finally get some answers.\n\n");
			else
				printf("This is the room where you got the silver key. There are doors to the north, south, and west.\n\n");
			break;
		case 15:
			if(bag[7].inv_count == 0 && examineFlag == 1)
				printf("After searching through the debris, you find a steel sword.\n\n");
			else if(bag[7].inv_count == 0)
				printf("The floor here is scattered with debris. A fight appears to have taken place in this room.\n\n");
			else
				printf("This is the room where you found the steel sword. I don't think anything else of value can be found among the wreckage.\n\n");
			break;
		case 16:
			if(opponent[3].health == 100)
				printf("This looks like the outer hall before the entrance to the castle. There's also an opposing figure on the other side of the room, but you can't quite make out anything but his silhouette. You've come pretty far, but you can't stop now.\n\n");
			else
				printf("You fought the great knight in this room, and it was a tough battle. There doesn't appear to be anything else of note here.\n\n");
			break;
		case 17:
			if(bag[8].inv_count == 0)
				printf("There's a small chest in the corner. Maybe you'll get a reward for winning such a tough fight against the great 					knight. There's also an exit to the east which seems to lead out of the castle.\n\n"); //open action
			else
				printf("You found the 100 gold pieces in the small chest here. There are only two exits, one to the north, and the other is to the 						east which leads out of the castle.\n\n"); 
			break;
		case 18:
			printf("You've finally made it out of the castle. Looks like your adventure has only begun!\n\n");
			exitGame();
			
	}

}

void exitGame(){
	printf("Thank you for playing!\n\n");
	exit(0);
}



/* Line 189 of yacc.c  */
#line 832 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     MOTION = 258,
     DIRECTION = 259,
     ACTION = 260,
     DRINK = 261,
     POTION = 262,
     START = 263,
     EXIT = 264,
     FIGHT = 265,
     HELP = 266,
     STATS = 267,
     CONVERSE = 268,
     EQUIP = 269,
     ITEM = 270,
     EQUIPPED = 271
   };
#endif
/* Tokens.  */
#define MOTION 258
#define DIRECTION 259
#define ACTION 260
#define DRINK 261
#define POTION 262
#define START 263
#define EXIT 264
#define FIGHT 265
#define HELP 266
#define STATS 267
#define CONVERSE 268
#define EQUIP 269
#define ITEM 270
#define EQUIPPED 271




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 906 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   16

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  17
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  25
/* YYNRULES -- Number of states.  */
#define YYNSTATES  29

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   271

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     7,     9,    11,    13,    15,    17,
      19,    21,    23,    25,    27,    29,    31,    34,    36,    38,
      40,    42,    45,    48,    50,    52
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      18,     0,    -1,    -1,    18,    19,    -1,    20,    -1,    21,
      -1,    22,    -1,    24,    -1,    23,    -1,    25,    -1,    27,
      -1,    28,    -1,    26,    -1,    29,    -1,    30,    -1,     8,
      -1,     3,     4,    -1,    10,    -1,     5,    -1,    12,    -1,
      11,    -1,     6,     7,    -1,    14,    15,    -1,    16,    -1,
      13,    -1,     9,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   765,   765,   766,   771,   772,   773,   774,   775,   776,
     777,   778,   779,   780,   781,   785,   788,   791,   794,   797,
     800,   803,   806,   809,   812,   815
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MOTION", "DIRECTION", "ACTION", "DRINK",
  "POTION", "START", "EXIT", "FIGHT", "HELP", "STATS", "CONVERSE", "EQUIP",
  "ITEM", "EQUIPPED", "$accept", "commands", "command", "startGame",
  "moveType", "fightType", "actionType", "statType", "helpType",
  "drinkType", "equipType", "equippedType", "talkType", "game", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    17,    18,    18,    19,    19,    19,    19,    19,    19,
      19,    19,    19,    19,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     2,     2,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,    18,     0,    15,    25,    17,    20,
      19,    24,     0,    23,     3,     4,     5,     6,     8,     7,
       9,    12,    10,    11,    13,    14,    16,    21,    22
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -12
static const yytype_int8 yypact[] =
{
     -12,     0,   -12,    -3,   -12,    -5,   -12,   -12,   -12,   -12,
     -12,   -12,   -11,   -12,   -12,   -12,   -12,   -12,   -12,   -12,
     -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,
     -12,   -12,   -12,   -12
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
       2,    26,    27,     3,    28,     4,     5,     0,     6,     7,
       8,     9,    10,    11,    12,     0,    13
};

static const yytype_int8 yycheck[] =
{
       0,     4,     7,     3,    15,     5,     6,    -1,     8,     9,
      10,    11,    12,    13,    14,    -1,    16
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    18,     0,     3,     5,     6,     8,     9,    10,    11,
      12,    13,    14,    16,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,     4,     7,    15
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 15:

/* Line 1455 of yacc.c  */
#line 785 "project3.y"
    { startGame(); }
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 788 "project3.y"
    { move((yyvsp[(2) - (2)])); }
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 791 "project3.y"
    { fightEnemy((yyval)); }
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 794 "project3.y"
    { executeAction((yyval)); }
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 797 "project3.y"
    { getStats(); }
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 800 "project3.y"
    { displayHelp(); }
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 803 "project3.y"
    { useItem((yyvsp[(2) - (2)])); }
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 806 "project3.y"
    { equipItem((yyvsp[(2) - (2)])); }
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 809 "project3.y"
    { equippedItems(); }
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 812 "project3.y"
    { talk(); }
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 815 "project3.y"
    { exitGame(); }
    break;



/* Line 1455 of yacc.c  */
#line 2189 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



