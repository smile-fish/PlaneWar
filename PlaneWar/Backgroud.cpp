//
//  Backgroud.cpp
//  PlaneWar
//
//  Created by 徐 BOWEI on 15/5/19.
//  Copyright (c) 2015年 徐 BOWEI. All rights reserved.
//

#include "Backgroud.h"       
#include <iostream>
#include <string>
using namespace std;
sf::RenderWindow Backgroud::window(sf::VideoMode(480,800),"plane");
Backgroud::Backgroud()
{
    if (!texture.loadFromFile(resourcePath()+"background.png")) {
        return EXIT_FAILURE;
    }
    sprite.setTexture(texture);
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    text = new sf::Text(str, font, 30);
    plane.setowner(this);
    sf::Vector2u myplane_size = plane.getsize();
    plane.setPosition((screen_size.x-myplane_size.x)/2,screen_size.y-myplane_size.y);
    setbullets(&(plane.getweapon()->bullets));
};
sf::RenderWindow& Backgroud::getwindow()
{
    return window;
}
void Backgroud::setbullets(std::vector<Bullet*> *p)
{
    bullets = p;
}
void Backgroud::setenemys(std::vector<Enemy*> *p)
{
    enemys = p;
}
void Backgroud::addscore(int score)
{
    sumscore +=score;
    str ="SCORE:"+ std::to_string(sumscore);
    text->setString(str);
    
}

void Backgroud::refresh()
{
    window.clear();
   
    window.draw(sprite);
    window.draw(plane);
    window.draw(*text);
    for(auto &a:(*bullets))
    {
        window.draw(*a);
    }
    for(auto &a:(*enemys))
    {
        window.draw(*a);
        for(auto &b:(((a)->getweapon())->bullets))
        {
            window.draw(*b);
        }
    }
    window.display();
}
void Backgroud::check()
{
    for (auto i =( bullets->begin()); i<(bullets->end()); i++) {
        if ((*i)->getPosition().y<-5) {
            delete *i;
            bullets->erase(i);
            
        }
    }
    
    for (auto i = (enemys->begin()); i<
         (enemys->end()); i++) {
        if ((*i)->getPosition().y>800) {
            delete *i;
            enemys->erase(i);
            
        }
    }
    for(auto &a:(*enemys))
    {
        for(auto i = (((a)->getweapon())->bullets).begin();i<(((a)->getweapon())->bullets).end();i++)
        {
            if ((*i)->getPosition().y>800) {
                delete *i;
                (((a)->getweapon())->bullets).erase(i);
                
            }
        }
    }

}
void Backgroud::touch()
{
    
    for(auto &a:(*bullets))
    {
        for (auto i = enemys->begin(); i<enemys->end(); i++) {
            if ((!(*i)->isdown())&&a->getGlobalBounds().intersects((*i)->getGlobalBounds())) {
                (*i)->setdownbegin(true);
                addscore(10);
            a->setuse(true);
            }
        }
    }
}
void Backgroud::touchhero()
{
    for (auto i = enemys->begin(); i<enemys->end(); i++) {
        if ((!(*i)->isdown())&&plane.getGlobalBounds().intersects((*i)->getGlobalBounds())) {
            (*i)->setdownbegin(true);
            plane.down();
            addscore(20);
            
        }
}
}
void Backgroud::touchenemy(){
    for (auto i = enemys->begin(); i<enemys->end(); i++) {
        if ((*i)->isdownover()) {
            delete *i;
            enemys->erase(i);
        }
    }
 
}
bool Backgroud::touchbullet()
{
    bool panduan = false;
    for (auto i = bullets->begin(); i<bullets->end(); i++) {
        if ((*i)->getuse()) {
            delete *i;
            bullets->erase(i);
            panduan = true;
        }
    }
    return panduan;
}
void Backgroud::enemybulletstouch()
{
    for(auto &a:(*enemys))
    {
        for(auto i = (((a)->getweapon())->bullets).begin();i<(((a)->getweapon())->bullets).end();i++)
        {
            if ((*i)->getGlobalBounds().intersects(plane.getGlobalBounds())) {
                delete *i;
                (((a)->getweapon())->bullets).erase(i);
                plane.down();
            }
        }
    }

}
void Backgroud::isover()
{
    if (plane.isdown()) {
        sf::Text over("game over",font,60);

        window.clear() ;
        window.draw(over);
        window.display();

        while (true) {
            ;
        }
    }
}
