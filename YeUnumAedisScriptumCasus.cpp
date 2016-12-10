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
sf::Text cursor;
bool isWhite = false;
bool thread_running = false;
std::string fontfile = "hachicro.ttf" ;
std::vector<std::string> history;
std::vector<std::string>::iterator it = history.begin();
std::stringstream textstream;

bool clean_insert(std::string in){
    if(!(std::find(history.begin(), history.end(), in) != history.end()) && !in.empty()){
        history.push_back(in);
        it = history.end();
        return true;
    }
    else{
        return false;
    }
}

void blinkCursor(){
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

void switch_context(std::string in){
    std::cout << in << std::endl;
    if(in == ""){

    }
    else if(in == ""){

    }
    else{

    }
}

int main(){
    /*---------------------Tips and Tracks-----------------------------------------------------------------\\
    //Use Booleans to mark a pressed key for smooth Movement-Systems or real-time Keyboard-Event
    //
    //-----------------------------------------------------------------------------------------------------*/
    int w = 1280;
    int h = 720;
    window.create(sf::VideoMode(w, h, 32), "Enter Title here!");
    window.setFramerateLimit(60);
    if (!font.loadFromFile(fontfile)){
    std::cout << "Could not Load font !" << std::endl;
    }
    else{
        text.setFont(font);
        text.setCharacterSize(24); // in pixels, not points!
        cursor.setFont(font);
        cursor.setCharacterSize(24); // in pixels, not points!
        text.setColor(sf::Color::White);
        cursor.setColor(sf::Color::White);
        //text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        //cursor.setStyle(sf::Text::Bold);
        isWhite = true;
        cursor.setString("[]");
        text.setPosition(0, (h- 32));
        cursor.setPosition(text.getCharacterSize(), (h - 32));
    }
    thread_running = true;
    std::thread thread(blinkCursor);// Creates Thread (C++11) and calls treadnochill
    while (window.isOpen()){    // run the program as long as the window is open
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Vector2f pos = text.getPosition();
        sf::Vector2f pos2 = cursor.getPosition();
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                thread_running = false;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                thread.join();
                window.clear(sf::Color::Black);
                window.close(); // "close requested" event: we close the window
            }
            if (event.type == sf::Event::KeyPressed){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "A";
                    }
                    else{
                        textstream << "a";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "B";
                    }
                    else{
                        textstream << "b";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "C";
                    }
                    else{
                        textstream << "c";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "D";
                    }
                    else{
                        textstream << "d";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "E";
                    }
                    else{
                        textstream << "e";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "F";
                    }
                    else{
                        textstream << "f";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::G)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "G";
                    }
                    else{
                        textstream << "g";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::H)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "H";
                    }
                    else{
                        textstream << "h";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "I";
                    }
                    else{
                        textstream << "i";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "J";
                    }
                    else{
                        textstream << "j";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "K";
                    }
                    else{
                        textstream << "k";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "L";
                    }
                    else{
                        textstream << "l";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "M";
                    }
                    else{
                        textstream << "m";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "N";
                    }
                    else{
                        textstream << "n";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "O";
                    }
                    else{
                        textstream << "o";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "P";
                    }
                    else{
                        textstream << "p";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "Q";
                    }
                    else{
                        textstream << "q";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "R";
                    }
                    else{
                        textstream << "r";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "S";
                    }
                    else{
                        textstream << "s";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "T";
                    }
                    else{
                        textstream << "t";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::U)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "U";
                    }
                    else{
                        textstream << "u";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::V)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "V";
                    }
                    else{
                        textstream << "v";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "W";
                    }
                    else{
                        textstream << "w";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "X";
                    }
                    else{
                        textstream << "x";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "Y";
                    }
                    else{
                        textstream << "y";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "Z";
                    }
                    else{
                        textstream << "z";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "=";
                    }
                    else{
                        textstream << "0";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "!";
                    }
                    else{
                        textstream << "1";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "\"";
                    }
                    else{
                        textstream << "2";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "§";
                    }
                    else{
                        textstream << "3";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "$";
                    }
                    else{
                        textstream << "4";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "%";
                    }
                    else{
                        textstream << "5";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "&";
                    }
                    else{
                        textstream << "6";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "/";
                    }
                    else{
                        textstream << "7";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << "(";
                    }
                    else{
                        textstream << "8";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                    } 
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
                        textstream << ")";
                    }
                    else{
                        textstream << "9";
                    }
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                    textstream << " ";
                    cursor.setPosition(text.getCharacterSize() + text.getGlobalBounds().width, pos2.y);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
                    std::stringstream newss;
                    newss << textstream.str().substr(0, (textstream.str().length() - 1));
                    textstream.str(std::string());
                    textstream << newss.str();
                    newss.str(std::string());
                    cursor.setPosition(text.getGlobalBounds().width, pos2.y);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
                    clean_insert(textstream.str());
                    textstream.str(std::string());
                    cursor.setPosition(text.getGlobalBounds().width, pos2.y);
                    if(!history.empty()){
                        if((*(it-1)) == "exit"){
                            textstream.str(std::string());
                            textstream << "Have Fun!";
                            thread_running = false;
                            cursor.setColor(sf::Color::Black);
                            window.clear(sf::Color::Black); // clear the window with black color
                            text.setString(textstream.str());
                            cursor.setPosition(text.getLocalBounds().width, pos2.y);
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
                    cursor.setPosition(text.getGlobalBounds().width, pos2.y);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                    if(!(history.empty()) && it++ != (history.end() - 1)){

                        textstream.str(std::string());
                        textstream.str(*it);
                    }
                    else if(!(history.empty()) && it == history.end()){
                        it--;
                    }
                    cursor.setPosition(text.getGlobalBounds().width, pos2.y);
                }
            }
        }
        cursor.setPosition(text.getLocalBounds().width, pos2.y);
        window.clear(sf::Color::Black); // clear the window with black color
        text.setString(textstream.str());
        window.draw(text);
        window.draw(cursor);
        window.display();
    }
    return 0;
}