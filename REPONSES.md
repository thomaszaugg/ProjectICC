#Programmation Orientée-objets(SV)

##REPONSES du groupe 144 (Thomas Zaugg, Lisa Kienle) 

*************************************************

[Question Q1.1] Comment coder les deux opérateurs précédemment décrits en évitant toute duplication de code dans le fichier CircularBody.cpp ? 

The operand > creates first a circular object with the same position as the point and radius 0.0 (a circle of radius 0.0 is a point).
Then, it makes use of the operand |, thus avoiding any duplication of code.

[Question Q1.2] Quelle surcharge choisissez-vous pour les opérateurs qu'il vous a été demandé de coder jusqu'ici (interne ou externe) et comment justifiez-vous ce choix ?

We followed the advice of the book "INTRODUCTION À LA PROGRAMMATION ORIENTÉE OBJET (EN C++)": "Un premier conseil est de préférer la surcharge externe lorsque le corps de la fonction peut être écrit sans avoir recours au mot-clé friend qui brise l’encapsulation et sans devoir coder des accesseurs inutiles”.
Since it was possible to code it without friend and without extra getters, we decided for a surcharge externes.

[Question Q1.3] Quels arguments de méthodes, parmi celles qu'il vous a été demandé de coder ci-dessus, vous semblent-ils judicieux de passer par référence constante ? 

No method/function parameters are changed in anywhere, so every argument can be passed by constant reference. We did constant reference for every Vect2d and CircularBody, but not the double, since it is small.

[Question Q1.4] Quelles méthodes, parmi celles qu'il vous a été demandé de coder ci-dessus, vous semblent-ils judicieux de déclarer comme const ? 

Neither the getters nor the checkers modify the object in any way, so it makes sense to make them all constant. 
 
[Question Q1.5] Quels arguments de méthodes, parmi celles qu'il vous a été demandé de coder ci-dessus, vous semblent-ils judicieux de passer par référence constante ? 
 
The arguments for the operators can be passed by constant reference. 
 
[Question Q1.6] Quelles méthodes, parmi celles qu'il vous a été demandé de coder ci-dessus, vous semblent-ils judicieux de déclarer comme const ? 
 
It makes sense to declare the methods that only check something and the operator, who access or compare something declared, as constant.

*************************************************

[Question Q2.1] What precaution should be taken when destroying cages to avoid memory leaks?
 
Since Cages is a vector to pointers to cages it is important to fully delete them. We solved this issue by making two for loops going through every cage and delete the allocation.
 
[Question Q2.2] We would like to not allow the copying of a Lab. What solution(s) do you propose to satisfy this constraint? Why is compliance with this constraint desirable?

We added the line: 
Lab(const Lab&)=delete;
To delete the copy constructor.
Since Lab is a very big object (containing many entities and cages), copying a lab takes too much memory.
 
[Question Q2.3] In which classes should the lines of code relating to the drawing of a cage appear in your opinion?

Drawing a cage should obviously be in the cage class, since it is closely related to the class itself. The drawing of Cages must be in the Lab class, since Cages are a typedef and not a class and therefore can't have their own methods.
 
[Question(s) Q2.4] Why can addFood and addAnimal potentially cause memory leaks and how to fix them? What other modification(s) do you need to make to the Lab class so that the hamster and the pile of pellets are now displayed in addition to the cages and what precaution(s) do you need to take to avoid a “crash” of the program if there is no hamster or no pile of pellets (value at nullptr)? 
 
It is not clear who has the responsibility to destroy the pointer given to the original addAnimal method. We solve it by clearly stating in the brief that we have the responsibility over the object pointed to by the pointer.
The drawOn method of the lab now includes the draw on methods of Hamster and Pellet (only if the pointer is not nullptr)
[Question Q2.5] What modification should be made to Lab to implement this functionality without memory leaks? 
We created two helper methods: clearEntities and clearCages
The first one deletes the allocated memory of the entities and sets them to nullptr. The second calls first the clearEntities method followed by a deallocation of memory used by the cages.
[Question Q2.6] A laboratory is non-copyable (is not intended to share its content with another laboratory). A Lab can therefore be considered responsible for the lifespan of the Entities created in the simulation. How does this affect the destruction of a Lab ? Answer these questions in your REPONSES file and implement the suggested developments. 
 
We added clearCages to the destructor.
 
[Question Q2.7] How do you propose to proceed to display the energy levels without repeating in Hamster and Pellets the instructions used to display the desired text? 
 
We added a method drawEnergy to the entity class, so both Hamster and Pellets can access it.
 
[Question Q2.8] What other modification do you need to make to the Lab class so that this is now concretely the case for our hamster and our pile of pellets (once again be careful, they may not exist and watch out for memory leaks! ). 
 
We added an increaseAge method to the entity class that is called upon (after checking it exists) in the update method.

[Question Q2.9] Here we make a first small foray into the application of polymorphism. Why should the method returning longevity here be marked as virtual? 

Because a fly doesn't live as long as a turtle: we want to make it possible to give different animals different longevities while keeping the code (here the isDead method) compact.

*************************************************

[Question Q3.1] Pourquoi le symbole & après auto dans la boucle réalisant les upate?
 
If the update method makes a nullptr, this change needs to be made to the Entities attribute and not a local copy of the element. Therefore, an iteration through the element can only update the pointer (in case of death) if it also gets the actual pointer. (Changing the object pointed to, for example age and position, would be also possible without the & symbol.)
 
[Question Q3.2] Pourquoi une collection de pointeurs  ?
 
Because we want to make use of virtual methods and polymorphism. Since a vector of references is not possible, a vector of pointers is our only option.
 
[Question Q3.3] Les méthodes de dessin des Hamster et Pellets sont pour l'heure probablement quasiment identiques (seul l'accès à la texture change), ce qui induit des duplications de code. Sachant que la façon de dessiner les informations de debugging peut être amenée à être spécifique (plus d'informations à afficher en mode «debug» pour les animaux que pour les tas de granulés par exemple), quelles modifications suggérez vous d'apporter au code existant pour éviter les duplications de codes non nécessaires lors du dessin des objets?
 
To avoid copying the code, we made a method drawOn in entity, that calls (as a parameter) the method getTexture, which is virtual and overwritten in Hamster and Pellet to get the corresponding texture. Hence, we don't copy code.
 
[Question Q3.4] Quelles retouches devez vous apporter à votre programme pour que les entités en fin de vie continuent de disparaître proprement et pour que le «reset» et la destruction du Lab demeurent corrects ?
 
It is important to deallocate the memory used by the object the pointer points to before setting them to nullptr and deleting them. 
This is the case with two methods: clearEntities and update, where we made sure to free up all the memory.
 
[Question Q3.5] : comment redéfinir getCenter dans Entity pour que la position de l'entité correspondent à son centre en tant que CircularBody? 
 
After making the getCenter method purely virtual, we only had to rename the Entity::getPosition getter to Entity::getCenter.
 
[Question Q3.6] : quelle autre conception est-il possible de mettre en place pour utiliser la classe CircularBody en vue de faire des tests de collision entre Entity ? Quel avantage/inconvénient y voyez-vous à ce stade ? 
 
It would be possible for the entity to HAVE a circular body as an attribute. 
Advantages: We wouldn't have to modify circular body as much (or operator didn't work anymore because CircularBody is now an abstract class)
 
Disadvantages: Conceptually it makes much more sense that Entity is a CircularBody. Further, the implementation of movement would be more difficult for the animal class, since the attribute position wouldn’t belong to it anymore.

[Question Q3.8] : Quelle méthode(s) parmi celle(s) que vous avez introduite vous semble t-elle devoir être polymorphique ? 
Cage::isEmpty() & Cage::reset: not polymorphic because only Cage is concerned
 
Entity::adjustPosition() is not polymorphic because it is the same for each entity.
 
Entity::canBeConfinedIn(Cage*): It is polymorphic. We defined it in Entity as returning true. In the animal class, this is overwritten as returning false if there is already an animal inside.
 
[Question Q3.9] : Où vous semble t-il pertinent de placer le traitement permettant d'ajuster la position d'une entité trop proche d'un mur ?

In Entity because position is an attribute of Entity, and we don't want to break encapsulation.
 
[Question Q3.10] : Comment proposez vous de procéder pour, que lors de son passage à l'état WANDERING, un animal adopte une vélocité constante de getMaxSpeed? 

We created a new method Animal::getAdjustedMaxSpeed() that returns the adapted value for all animals (and doesn't leave choice up to the adder of a new animal class)
 
[Question Q3.11] Comment proposez vous pour faire en sorte qu'un animal continue de vieillir sans dupliquer le code qui le fait vieillir ? 

Call the Entity::update method with the indication of the port.
 
[Question Q3.12] Quelles méthodes proposez-vous d'ajouter et à quelle(s) classe(s) pour garantir que l'animal se retourne dans la direction opposée à son déplacement si la nouvelle position calculée par la méthode move induit une collision avec l'un des murs de l'une des boites du laboratoire? 
 
We chose to calculate the displacement vector and check if it collides in Animal (overloaded inCollison method), since it is the class containing the attribute speed. For this, we created helper methods to setPosition or flipOrientation and used the modularized methods from the first part.
 
[Question Q3.13] Comment proposez-vous de modifier la méthode getMaxSpeed de sorte à ce qu'en dessous d'un seuil critique d'énergie l'animal se déplace plus lentement ? 
 
We tried multiple versions. In one of them we modified the value in the getMaxSpeed method in the hamster class. However, the implementation of a new animal would be unnecessary difficult. Therefore, we simply added getAdjustedMaxSpeed that modifies the speed (with virtual getters for the fatigue energy and the scaler of the speed to facilitate the implementation of new animal classes). 
 
[Question Q3.14] Pourquoi tester le type des objets à l'exécution est-il potentiellement nocif  ? 
 
This list would have to be updated every time a new type of entity (maybe completely unrelated to the hamsters) is added to the lab, which is easily forgotten. Hence, encapsulation would be broken.
 
[Question Q3.15] Pourquoi selon vous cela n'est pas une bonne idée de stocker la masse du hamster dans un attribut ? (en quoi cela fait-il perdre un avantage offert par les fichiers de configuration ?) Répondez à cette question dans votre fichier REPONSES (et pensez-y à chaque fois que vous souhaiterez utiliser un attribut pour une donnée paramétrable). 
 
First, all the parameters are concentrated in one compact file, changing them is made easy. Therefore, it allows us to play around and test the edge cases more easily using the central configuration file instead of searching the initialization somewhere in our code. 
 
[Question Q3.16] Quelle(s) méthode(s) proposez-vous de mettre en place et dans quelle classe pour permettre de simuler la consommation de nourriture par un Animal? 

First, it is (again) checked in the method eatFood if the entity can eat the other entity. Then, we added the virtual method provideEnergy to the entity class that does nothing. In food it has been overwritten to do the correct thing. These helper methods are managed from the Animal::eatFood() method.

[Question Q3.17] Comment proposez-vous de mettre en oeuvre le pas 1 de l'algorithme de Animal::update sans donner un accès publique à toutes les entités simulées depuis Lab : quelles méthodes/attributs ajoutez vous et à quelles classes et au moyen de quelle(s) méthodes déjà codée(s). 

We decided to break encapsulation as little as possible by creating the method getClosesedEatableEntity in the lab class that returns only the pointer to the closest eatable entity (as the name suggests). Then, the rest is managed in animal class.

[Question Q3.18] Quel nouvel algorithme proposez-vous pour updateState afin de mettre en oeuvre proprement les transitions d'états suggérées par l'algorithme ci-dessus? 

We implemented it as described in the enounce. It is important to note that an animal can only be feeding if it can be targeting and that it can only be idle if it can be wandering.
 
[Question Q3.19 ] : les classes fournies dans le répertoire Interface, à savoir Drawable et Updatable, fournissent deux méthodes polymorphiques drawOn et update. Quelles classes de votre conception actuelle serait-il bon de faire hériter de ces sous-classes ? Quel plus cela amène t-il à la conception ? 
 
Updatable: Lab, Entity
Drawable: Lab, Entity, Cage
 
First, it makes the central properties updatable and drawable visible on a class structural level.
Further, we can organize things on a more general level (like the getDepth method).

*************************************************

[Question Q4.1] It doesn't make sense to track down piles of pellets. To avoid having to test the type of entities to implement the trackAnimal(const Vec2d&) method , it is possible for example to: 1) introduce a collection of animals in parallel with the collection of entities or 2) introduce a polymorphic method indicating whether an entity is an animal that can be tracked or not. Which method seems preferable to you and why? 

To avoid type testing we made a polymorphic method called isAnimal. It is easier to call this method than make a new attribute that has to be updated all the time.

[Question Q4.2] We suggest you code the generate method as virtual. How do you think this could be useful? 

In the tests, the OrganCellTest class inherits from Organ and to better test it overrides generate (but still calls the original through the portal Organ::generate()).

[Question Q4.3] What other changes do you need to make to your program to code these methods? In particular, how do you propose to code updateTrackedAnimal() and drawCurrentOrgan without coding a getter on the animal's organ (too intrusive)?

We decided to create public methods in animal that draw, initialize, and update the organ. These can be called from the lab using the tracked animal pointer.

[Question Q4.4] With what value should the CellsLayer constructor invoke that of the ECMCell that it dynamically allocates?

The ECMCell should be a part of the CellsLayer we are constructing at the moment. Therefore, we invoke the constructor with the parameter (this)

[Question Q4.5] What should the destructor of a Cell do to avoid memory leaks?

The destructor of a Cell should delete the substances it allocated dynamically.

[Question Q4.6] What should the destructor of a CellsLayer do to avoid memory leaks?

To avoid memory leak the destructor of CellsLayer has to destroy all the cell it constructed at the beginning.

[Question Q4.7] What method(s) are you adding and to what class(es) to enable the coding of CellsLayer::updateSubstance ?

One method Cell::addSubstance that coordinates the use of the += substance operator.

[Question Q4.8] What method(s) do you add and to what class(es) to allow the coding of “getters” on the quantities of substances conveyed by each level of a CellsLayer ?

We added one method Cell::getQuantitiy that is called upon in each of the getters.

[Question Q4.9] What method(s) are you adding and to what class(es) to enable the coding of CellsLayers::organCellTakeFromEcm  ?

We added a method Cell::uptakeSubstance method that makes use of the uptakeOnGradient method of the Substance class.

[Question Q4.10] What adjustment(s) do you need to make to setBlood and setOrganCell so that a change in the content of a CellsLayer is correctly reflected in its graphical representation ? Why does setECM not necessarily need any modifications on its own ?

We call Organ::updateRepresentationAt to make the new cell visible. It is not necessary to do this for the ECM cell, since there is no change of the visual representation over the time.

*************************************************

[Question Q5.1] What additions/tweaks do you need to make to the existing code to implement the creation of the organ fragment?

Our existing methods were coded sufficiently that no changes were needed.

[Question Q5.2] How do you propose to proceed to make a cell of the organ fragment die (and disappear from the representation of the organ) if the value of atp_ becomes negative.

Making is Dead method and then calling the updateRepresentationAt method.

[Question Q5.3] What method(s) do you introduce in which class(es) to update the content of the cells on which the diffusion is done (remember the CellLayers method: : updatePreviously encoded substance).

We tried to minimize the breaking of encapsulation by only introducing a getter for the CellsLayer in the cell method. 

Like proposed we coded for a method Organ::updateCellsLayerAt(const CellCoord& pos, const Substance& diffusedSubst) that is called by a method with the same name in CellsLayer(keep encapsulation)

All these methods are called by a private surcharge of update.

*************************************************

Question 6.1] Which method(s) do you introduce and in which class(es) to implement the required methods without intrusive accessors such as getOrgan() ?

To not be too intrusive, we decided to use a cascade of methods: Lab calls the methods (with the same name) of Animal, Animal calls the methods of Organ. Hence, encapsulation is kept at a maximum.

Analogously, the BloodCell needs to know what the deltas are: for this, it calls the getters in cell which call the getters in cellsLayer which then call the getters in organ.

[Question 6.2] Which of the newly introduced methods have you decided to program as polymorphic?

We coded different new methods that are called in OrganCell::update. The only polymorphic one is ATPSynthesis. For the rest, we used polymorphic getters to access the different condition of OrganCell and TumoralCell.

[Question 6.3] Which method(s) do you introduce and in which class(es) to implement the setCancerAt method?

To implement the Organ::setCancerAt method we called the setCancer method in CellsLayer. The method in CellsLayer does the actual construction of the cell and updates the Representation.

[Question 6.4] For the graphical representation of TumoralCell, we suggest you introduce a new vertex array organCancerVertexes_ into Organ and use the texture identified by &getAppTexture(textures["cancer"].toString()). What changes do you need to make to the Organ class to enable cancer cells to be drawn ?

We had to make changes in our setVertex method. Now the method has a parameter more, indicating whether the Vertexes of the CancerCell need to be coloured or transparent. Additionally, we had to add the according line in our drawCells and drawRepresentation method.

[Question 6.5] How do you code ATPSynthesis without duplicating code between OrganCell and TumoralCell?

We made a protected method glycolysis that is called from the ATPSynthesis from TumoralCell (and apart from that, the code is written with polymorphic getters).

[Question 6.6] What method(s) do you introduce and in which class(es) to implement cell division of the organ fragment (always avoiding introducing overly intrusive getters like getOrgan or getCellsLayers) ? 

We coded the method division that handles division for both organ and tumoral cells using polymorphic getters. If a cell is ready to divide, it sends a request to divide using the requestToDivide(bool hasCancer) method, that is passed up to Cell, then CellsLayer and finally Organ where the necessary checks are made. If there is a free position, the organ sets a new cell and returns a bool (back through the cascade). The cell thereby knows if it has divided and then resets the counter and subtracts the energy.
