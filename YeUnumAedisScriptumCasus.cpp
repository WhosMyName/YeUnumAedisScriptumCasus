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
std::string fontfile = "hachicro.ttf" ;
std::vector<std::string> history;
std::vector<std::string>::iterator it = history.begin();
std::vector<std::string> inventory;
std::vector<std::string>::iterator inv_it = inventory.begin();
std::stringstream textstream;
int lvl = 0;
int delim;
std::stringstream outputStream;

bool clean_insert(std::string in){// Special custom Insert Function to avoid Double Entrys
    if(!(std::find(history.begin(), history.end(), in) != history.end()) && !in.empty()){
        history.push_back(in);
        it = history.end();
        return true;
    }
    else{
        return false;
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

void read(std::string obj){
    std::cout << obj << std::endl;
}
void light(std::string obj){
    std::cout << obj << std::endl;
}
void roll(std::string obj){
    std::cout << obj << std::endl;
}
void play(std::string obj){
    std::cout << obj << std::endl;
}
void walk(std::string obj){
    std::cout << obj << std::endl;
}
void fall(std::string obj){
    std::cout << obj << std::endl;
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
        fall(obj);
    }
    else{
        std::cout << "This is not a valid Option!" << std::endl;
    }
}
void print(std::string s){
    outputStream << s;

}
void flush(){
	outputStream.str(std::string());

}
int main(){
    /*---------------------Tips and Tracks-----------------------------------------------------------------\\
    //Use Booleans to mark a pressed key for smooth Movement-Systems or real-time Keyboard-Event
    //
    //-----------------------------------------------------------------------------------------------------*/
    int w = 1280;
    int h = 720;
    window.create(sf::VideoMode(w, h, 32), "Enter Title here!"); //Creates Window
    window.setFramerateLimit(60);
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
        output.setCharacterSize(24);
        output.setColor(sf::Color::White);
        output.setPosition(w/3, (h/3));
    }
    thread_running = true;
    std::thread thread(blinkCursor);// Creates Thread (C++11) and calls blinkCursor
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
			}
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                    textstream << " ";
                    cursor.setPosition(cmd_size, pos2.y);
            }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
                    std::stringstream newss;
                    newss << textstream.str().substr(0, (textstream.str().length() - 1));
                    textstream.str(std::string());
                    textstream << newss.str();
                    newss.str(std::string());
                    cursor.setPosition(cmd_size, pos2.y);
                }     
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    clean_insert(textstream.str());
                    textstream.str(std::string());
                    cursor.setPosition(cmd_size, pos2.y);
                    if(!history.empty()){
                        if((*(it-1)) == "exit"){
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
                        switch_context((*(it-1)));
                        }
                    }
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                    if(!(history.empty()) && it != history.begin()){
                        if(clean_insert(textstream.str())){
                            it = it - 2;
                        }
                        else{
                            it--;
                        }
                        textstream.str(std::string());
                        textstream.str(*it);
                    }
                    cursor.setPosition(cmd_size, pos2.y);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                    if(!(history.empty()) && it++ != (history.end() - 1)){
                        textstream.str(std::string());
                        textstream.str(*it);
                    }
                    else if(!(history.empty()) && it == history.end()){
                        it--;
                    }
                    cursor.setPosition(cmd_size, pos2.y);
                }
        }
        text.setPosition(5 + entry.getGlobalBounds().width, (h - 32));
        window.clear(sf::Color::Black); // clear the window with black color
        text.setString(textstream.str());
        cursor.setPosition(cmd_size, pos2.y);
	    output.setString(outputStream.str());
        window.draw(entry);
        window.draw(text);
        window.draw(output);
        window.draw(cursor);
        window.display();
    }
    return 0;
}
