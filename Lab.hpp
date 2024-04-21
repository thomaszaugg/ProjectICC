#ifndef LAB_HPP
#define LAB_HPP
#include <vector>
#include "Cage.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#pragma once

class Pellets;
class Hamster;
class Entity;
class Animal;

typedef std::vector<std::vector<Cage*>> Cages;
typedef std::vector<Entity*> Entities;

class Lab
{
private:
    Cages cages;
    Entities entities;

    /*!
    * @brief Check whether the value nbCagesPerRow is inbetween the min and max barrier
    * if not, the function does also correct the value
    */
    void CageNumberCheck(unsigned int& nbCagesPerRow);

    /*!
    * @brief deletes all the cages or all the entities
    */
    void clearCages();
    void clearEntities();

    /*!
    * @brief Helper function that draws the Cages of the lab
    */
    void drawOnCages(sf::RenderTarget& targetWindow);


public:
    /*!
    * @brief default constructor
    */
    Lab();

    /*!
    * @brief defines the maxCageNumber
    */
    unsigned int maxCageNumber();

    /*!
    * @brief constructs the different cages
    */
    void makeBoxes(unsigned int nbCagesPerRow);

    /*!
    * @brief Getter for attribut nbCagesPerRow
    */
    unsigned int getNbCagesPerRow();

    /*!
    * @brief this function increases the nbCagesPerRow by one (if possible under the constraint)
    * and reinitializes the boxes with the new number
    */
    void addCageToRow();

    /*!
    * @brief this function decreases the nbCagesPerRow by one (if possible under the constraint
    * and reinitialises the boxes with the new number
    */
    void removeCageFromRow();

    /*!
    * @brief change the contents of the cages over time
    */
    void update(sf::Time dt);

    /*!
    * @brief Draws the lab
    */
    void drawOn(sf::RenderTarget& targetWindow);

    /*!
    * @brief partially or totaly reset the lab, if reset = false, only the content of the cages is deleted,
    * otherwise content and cages are deleted
    */
    void reset(bool reset = false);

    /*!
    * @brief deconstructer
    */
    ~Lab();

    /*!
    * @brief to make it impossible to copy a Lab
    */
    Lab(const Lab&)=delete;

    /*!
    * @brief add hamsters and pellets, addAnimal and addPellets call addEntity
    */
    bool addEntity(Entity* e);
    bool addAnimal(Hamster* h);
    bool addFood(Pellets* p);

    /*!
    * @brief assigns the entitiy to a Cage in the Lab
    */
    bool declareEntityCage(Entity* e);

};

#endif // LAB_HPP



