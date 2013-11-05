%error-verbose

%{
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

%}

%token MOTION DIRECTION ACTION DRINK POTION START EXIT FIGHT HELP STATS CONVERSE EQUIP ITEM EQUIPPED

%%

commands: /* empty */
	| commands command
	;


command:
	startGame
	| moveType
	| fightType
	| statType
	| actionType
	| helpType
	| equipType
	| equippedType
	| drinkType
	| talkType
	| game
	;


startGame:	START { startGame(); }
;

moveType:	MOTION DIRECTION { move($2); }
;

fightType:	FIGHT { fightEnemy($$); }
;

actionType:	ACTION { executeAction($$); }
;

statType:	STATS { getStats(); }
;

helpType:	HELP { displayHelp(); }
;

drinkType: 	DRINK POTION { useItem($2); }
;

equipType:	EQUIP ITEM { equipItem($2); }
;

equippedType:	EQUIPPED { equippedItems(); }
;

talkType:	CONVERSE { talk(); }
;

game: 		EXIT { exitGame(); }
;


