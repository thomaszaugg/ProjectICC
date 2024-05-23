#ifndef LAB_HPP
#define LAB_HPP
#include <vector>
#include "Cage.hpp"
#include "Env/Animal.hpp"
#include "SFML/Graphics.hpp"
#include "Drawable.hpp"
#include "Updatable.hpp"
#include "Types.hpp"
#pragma once

class Pellets;
class Hamster;
class Entity;
class Animal;

typedef std::vector<std::vector<Cage*>> Cages;
typedef std::vector<Entity*> Entities;

class Lab : public Drawable, public Updatable
{
private:
    Cages cages;
    Entities entities;
    Animal* animal=nullptr; //tracked animal

    /*!
    * @brief Check whether the value nbCagesPerRow is inbetween the min and max barrier
    * if not, the function does also corrects the value
    */
    void CageNumberCheck(unsigned int& nbCagesPerRow);

    /*!
    * @brief deletes all the cages (entities included) or all the entities
    */
    void clearCages();
    void clearEntities();

    /*!
    * @brief Helper functions that draws the cages and the entities
    */
    void drawOnCages(sf::RenderTarget& targetWindow);
    void drawOnEntities(sf::RenderTarget& targetWindow);

    /*!
    * @brief constructs the different cages
    */
    void makeBoxes(unsigned int nbCagesPerRow);

    /*!
    * @brief assigns the entitiy to a Cage in the Lab
    */
    bool declareEntityCage(Entity* e);

public:
    /*!
    * @brief default constructor
    */
    Lab();

    /*!
    * @brief deconstructer
    */
    virtual ~Lab();

    /*!
    * @brief defines the maxCageNumber
    */
    unsigned int maxCageNumber();

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
    * @brief to make it impossible to copy a Lab
    */
    Lab(const Lab&)=delete;

    /*!
    * @brief add hamsters and pellets, addAnimal and addPellets call addEntity
    * @attention the lab class is responsible for the freeing of the memory of the pointers
    */
    //write for every
    bool addEntity(Entity* e);
    bool addAnimal(Hamster* h);
    bool addFood(Pellets* p);

    /*!
    * @brief finds the closest eatable entity to e that is in cage c
    * @return either pointer to the eatable entity or nullptr if there is none
    */
    Entity* getClosesedEatableEntity(Cage* c, Entity* const& e);

    /*!
    * @brief called by trackAnimal method and sets the animal attribut
    */
    void trackAnimal(Animal* a);

    /*!
    * @brief checks whether there is an animal at the given positon,
    * if yes, calls trackAnimal(Animal*) method
    */
    void trackAnimal(const Vec2d& position);

    /*!
    * @brief checks if an animal of the Lab is tracked
    * @return true if the animal attribut is not a nullptr
    */
    bool isAnyTrackedAnimal();

    /*!
    * @brief switching views
    */
    void switchToView(View view);

    /*!
    * @brief sets animal to nullptr
    */
    void stopTrackingAnyEntity();

    /*!
    * @brief updates the organ of the tracked animal
    */
    void updateTrackedAnimal();

    /*!
    * @brief draws the tracker icon
    */
    void drawTracker(sf::RenderTarget& target);

    /*!
    * @brief drawing of the organ
    */
    void drawCurrentOrgan(sf::RenderTarget& target);

    /*!
    * @brief changing to the next substance
    */
    void nextSubstance();

    /*!
    * @brief increasing of current Substance
    */
    void increaseCurrentSubst();

    /*!
    * @brief deceasing of current Substance
    */
    void decreaseCurrentSubst();

    /*!
    * @brief Getter
    * @return delta value of current Substance
    */
    double getDelta(SubstanceId id) ;

    /*!
    * @brief Getter for Current Substance
    * @return Id of current Substance, if there is no tracked animal ID 0 is returned
    */
    SubstanceId getCurrentSubst();

    /*!
    * @brief Setter for Cancer Cell
    */
    void setCancerAt(const Vec2d& pos);

    };

#endif // LAB_HPP



