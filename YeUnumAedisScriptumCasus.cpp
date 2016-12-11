#include <stdio.h> 
#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>

sf::RenderWindow window;
sf::Event event;
sf::Font font;
sf::Text text;
sf::Text output;
sf::Text entry;
sf::Text cursor;
bool isWhite = false;
bool thread_running = false;
bool isLight = false;
bool portal = false;
bool has_scroll = true;
bool matches = false;
int lvl = 0;
int delim;
int candleStage = 0;
std::string fontfile = "Welbut__.ttf" ;
std::vector<std::string> history;
std::vector<std::string>::iterator historyit = history.begin();
std::vector<std::string> inv;
std::vector<std::string>::iterator invit = inv.begin();
std::stringstream textstream;
std::stringstream outputstream;

std::vector<std::string>::iterator dirty_insert(std::string in, std::vector<std::string> * vec){// Special custom Insert Function to avoid Double Entrys
    vec->push_back(in);
    return vec->end();
}

std::vector<std::string>::iterator clean_insert(std::string in, std::vector<std::string> * vec){
    if(!(std::find(vec->begin(), vec->end(), in) != vec->end()) && !in.empty()){
        vec->push_back(in);
        return vec->end();
    }
    else{
        return vec->begin();
    }
}

void blinkCursor(){ //Let's the Cusor Blink
    while(thread_running){
        if (isWhite){
            isWhite = false;
            cursor.setColor(sf::Color::Black);
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
        else{
            isWhite = true;
            cursor.setColor(sf::Color::White);
            std::this_thread::sleep_for(std::chrono::milliseconds(250)); 
        }
    }
}

void print(std::string printinput){
    outputstream << printinput;
}

void flush(){
	outputstream.str(std::string());
    output.setString(outputstream.str());
    window.draw(output);
    window.clear(sf::Color::Black); // clear the window with black color
}

void intro(){
    if(lvl == 0){
        flush();
        print("You find yourself surrounded by darkness.\nYou feel a strong wind and tight shoes around your feet.\nThere is a CANDLE and a SCROLL in front of you.");
    }
    else if(lvl == 1){
        flush();
        print("You find yourself surrounded by darkness.\nYou feel a mild breeze.\nThere is a CANDLE and a SCROLL in front of you.");
    }
    else if(lvl == 2){
        flush();
        print("You find yourself surrounded by darkness.\nYou feel no movement of the air.\nThere is a CANDLE and a SCROLL in front of you.");
    }
    else if(lvl == 3){
        flush();
        print("THANK YOU FOR PLAYING\nYE UNUM AEDIS SCRIPTUM CASUS!");
    }
}

void inventory(){
    flush();
    print("Your Inventory contains: \n");
    for(invit = inv.begin(); invit != inv.end(); invit++){
        print((*invit) + "\n");
    }
}

void take(std::string obj){

}

void read(std::string obj){
    if(isLight){
        if(obj == "scroll" ){
            flush();
            switch(lvl){
                case 0:print("\"You might have lost the way and goal\nThe way to know is to see all whole\nTo grow in meaningful extent\nRead out the spell below's content\nWALK through the opening in spa\"\n\nThere is a SPELL attached to the scroll.");break;
                case 1:print("\"You are a closer match to clarity\nLack of attention your only enemy\n\nPLAY with the shadow of the light\nRevive this tale when the time is right:\n\nThe freeest monarch of the wind pounced,\nat a double-quad-limbed creep,\nwhilst your best friend's ancestors sing.\""); break;
                case 2:print("\"As the mind receives increase\nThoughts must expand\n\nFALL through the final phase\nTruth is not brought by your own hand\"\nThere is a SPELL attached to the scroll");break;
                case 3:print("You can't read at all.");break;
            }
        }
        else if(obj == "spell"){
            flush();
            print("As you read out the magic spell,\na PORTAL made out of energy opens.");
            portal = true;
        }
        else{
            flush();
            std::stringstream teemo;
            teemo << "Reading " << obj << " doesn't seem to be a good Idea!" << std::endl;
            print(teemo.str());
        }
    }
    else{
        flush();
        print("There is no Light! It's too dark to read.");
    }
}
void light(std::string obj){
    flush();
    if(matches){
        if(obj == "scroll"){
        flush();
        bool has_scroll = true;
        print("As the Scroll blazed into dust,\nyou realize that you just burned your only chance of Escape!\n gg wp");
        }
        else if(obj == "candle"){
            flush();
            isLight = true;
            print("A faint light fills the room!");
        }
        else if(obj == "self"){
        print("As your Entity is embraces by the warmth of the Flames,\nyou realize that you left Stove turned on at home!");
        isLight = true;
        }
    }
    else{
        flush();
        print("How?");
    }
}
void roll(std::string obj){
    if(obj == "portal" && portal){
        lvl++;
        isLight = false;
        portal = false;
        flush();
        print("As you roll through the Portal,\nyour Vision blurs\n and a slight breeze extinguishes the Flame of your Candle.");
        intro();
    }
    else if(obj == "portal" && !portal){
        flush();
        print("There's no Portal to roll into!\nWhat were you trying to achieve?");
    }
    else{
        flush();
        print("You are tired of rolling around.\nMaybe you should focus on your tasks.");
    }
}

void play(std::string obj){
	if(obj == "candle" && isLight){
		candleStage = 1;
		print("You can produce the following\n shadow puppets: WOLF, ELK,\n EAGLE, SPIDER, GOOSE \n");
	}
	else if(obj == "eagle" && candleStage == 1 && isLight){
		print("The light burns brighter.\n THIS WAS THE CORRECT CHOICE.\n");
		candleStage++;	
	}
	else if(obj == "spider" && candleStage == 2 && isLight){
		print("The light burns brighter.\n THIS WAS THE CORRECT CHOICE.\n");
		candleStage++;	
	}
	else if(obj == "wolf" && candleStage == 3 && isLight){
		print("As you play out the magic sequence,\n the room turns light and heat into a PORTAL.\n");
		candleStage++;
		portal = true;
			
	}
	else if(obj == "candle" && isLight){
		flush();
		print("You can produce the following\n shadow puppets: WOLF, ELK,\n EAGLE, SPIDER, GOOSE \n");
		print("The light flickers,\n the candle nearly extinguishes\n and then returns to burning normally.\n THIS WAS THE WRONG CHOICE.\n");
		candleStage=1;
	}
	else if(obj == "candle"){
		flush();
		print("You play with your fingers,\n but nobody sees it!\n");
	}
	else{
		flush();
		print("You play around but NOTHING happens.\n");
	}
}
void walk(std::string obj){
	if(lvl == 2){
    flush();
	print("You try to walk.\n You trip.\n You fall.\nYou fall through the portal.\nYou find yourself surrounded by light.\nYou have come back.\n And it all comes back to you.");
	lvl++;
    intro();
	}
	else{
        flush();
		print("You trip. You fall.\n\n You realize that you are wearing\n roller blades.\n You cannot walk. You can only ROLL.\nBut you find some matches!\n");
        matches = true;
	}
}
void fall(){
    flush();
    print("You do a 1080° Full-Frontal Node-Dive.");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    flush();
    print("This actually hurts!");
}

void switch_context(std::string in){ //Main Function to Play
    std::cout << in << std::endl;
    delim = in.find(" ");
    std::cout << delim << std::endl;
    std::string command = in.substr(0, delim);
    std::string obj = in.substr(delim + 1, in.length());
    std::cout << "Object: "<< obj << std::endl;
    if(command == "read"){
        read(obj);
    }
    else if(command == "roll"){
        roll(obj);
    }
    else if(command == "walk"){
        walk(obj);
    }
    else if(command == "light"){
        light(obj);
    }
    else if(command == "play"){
        play(obj);
    }
    else if(command == "fall"){
        fall();
    }
    else if(command == "intro"){
        intro();
    }
    else if(command == "inventory"){
        inventory();
    }
    else{
        flush();
        print("This is not a valid Option!\nNeed some help?");
    }
}

int main(){
    /*---------------------Tips and Tracks-----------------------------------------------------------------\\
    //Use Booleans to mark a pressed key for smooth Movement-Systems or real-time Keyboard-Event
    //
    //-----------------------------------------------------------------------------------------------------*/
    int w = 1650;
    int h = 720;
    window.create(sf::VideoMode(w, h, 32), "Enter Title here!"); //Creates Window
    window.setFramerateLimit(30);
    if (!font.loadFromFile(fontfile)){ //Loads Font
    std::cout << "Could not Load font !" << std::endl;
    }
    else{
        isWhite = true;
        cursor.setString("[]");
        entry.setString(">");
        text.setFont(font);
        text.setCharacterSize(24); // in pixels, not points!
        text.setColor(sf::Color::White);
        cursor.setFont(font);
        cursor.setCharacterSize(24); // in pixels, not points!
        cursor.setColor(sf::Color::White);
        entry.setFont(font);
        entry.setCharacterSize(24); // in pixels, not points!
        entry.setColor(sf::Color::White);       
        entry. setPosition(0, (h - 32));
        text.setPosition(entry.getCharacterSize(), (h - 32)); //Initial Text Position
        cursor.setPosition(text.getGlobalBounds().width, (h - 32));//Initial Cursor Position
	    output.setFont(font);
        output.setCharacterSize(18);
        output.setColor(sf::Color::White);
        output.setPosition(0, (h/3));
    }
    thread_running = true;
    std::thread thread(blinkCursor);// Creates Thread (C++11) and calls blinkCursor
    help();
    while (window.isOpen()){    // run the program as long as the window is open
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Vector2f pos = text.getPosition();
        sf::Vector2f pos2 = cursor.getPosition();
        int cmd_size = (5 + entry.getGlobalBounds().width + text.getLocalBounds().width);
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                thread_running = false;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                thread.join();
                window.clear(sf::Color::Black);
                window.close(); // "close requested" event: we close the window
            }
            if(event.type == sf::Event::KeyReleased){
				if(event.key.code >= sf::Keyboard::A && event.key.code<=sf::Keyboard::Z) { 
 					textstream << (char)(97 + event.key.code);
    	   		}
    	   		else if(event.key.code >= 26 && event.key.code <= 35){
    	   			textstream << (char)(48 - 26 + event.key.code);
    	   		}
  	            if(event.key.code == (sf::Keyboard::Space)){
                    textstream << " ";
                    cursor.setPosition(cmd_size, pos2.y);
                }

                if(event.key.code == (sf::Keyboard::BackSpace)){
                    std::stringstream newss;
                    newss << textstream.str().substr(0, (textstream.str().length() - 1));
                    textstream.str(std::string());
                    textstream << newss.str();
                    newss.str(std::string());
                    cursor.setPosition(cmd_size, pos2.y);
                }     

                if(event.key.code == sf::Keyboard::Return){
                    if(!textstream.str().empty()){
                        historyit = dirty_insert(textstream.str(), &history);
                        textstream.str(std::string());
                        cursor.setPosition(cmd_size, pos2.y);
                        if(!history.empty()){
                            if((*(historyit-1)) == "exit"){
                                textstream.str(std::string());
                                thread_running = false;
                                cursor.setColor(sf::Color::Black);
                                window.clear(sf::Color::Black); // clear the window with black color
                                text.setPosition(5 + entry.getGlobalBounds().width, (h- 32));
                                text.setString("Have Fun!");
                                cursor.setPosition(5 + entry.getGlobalBounds().width + text.getLocalBounds().width, pos2.y);
                                window.draw(entry);
                                window.draw(text);
                                window.draw(cursor);
                                window.display();
                                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                                thread.join();
                                window.clear(sf::Color::Black);
                                window.close(); // "close requested" event: we close the window
                                return 0;
                            }
                            else{
                                switch_context((*(historyit-1)));
                            }
                        }    
                    }
                }
            }

            if(event.type == sf::Event::KeyPressed){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                    if(!(history.empty()) && historyit != history.begin()){
                        if(clean_insert(textstream.str(), &history) != history.begin()){
                            historyit = historyit - 2;
                        }
                        else{
                            historyit--;
                        }
                        textstream.str(std::string());
                        textstream.str(*historyit);
                    }
                    cursor.setPosition(cmd_size, pos2.y);
                }

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                    if(!(history.empty()) && historyit++ != (history.end() - 1)){
                        textstream.str(std::string());
                        textstream.str(*historyit);
                    }
                    else if(!(history.empty()) && historyit == history.end()){
                        historyit--;
                    }
                    cursor.setPosition(cmd_size, pos2.y);
                }
            }
        }
        text.setPosition(5 + entry.getGlobalBounds().width, (h - 32));
        window.clear(sf::Color::Black); // clear the window with black color
        text.setString(textstream.str());
        cursor.setPosition(cmd_size, pos2.y);
	    output.setString(outputstream.str());
        window.draw(entry);
        window.draw(text);
        window.draw(output);
        window.draw(cursor);
        window.display();
    }
    return 0;
}
