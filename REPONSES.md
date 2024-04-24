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

We added the line 
Lab(const Lab&)=delete;
To delete the copy constructor.
Since Lab is a very big object (containing many entities and cages), copying a lab takes to much memory.
 
[Question Q2.3] In which classes should the lines of code relating to the drawing of a cage appear in your opinion?

Drawing a cage should obviously be in the cage class, since it is closely related to the class itself. The drawing of Cages has to be in the Lab class, since Cages are a typedef and not a class and therefore can't have their own methods.
 
[Question(s) Q2.4] Why can addFood and addAnimal potentially cause memory leaks and how to fix them? What other modification(s) do you need to make to the Lab class so that the hamster and the pile of pellets are now displayed in addition to the cages and what precaution(s) do you need to take to avoid a “crash” of the program if there is no hamster or no pile of pellets (value at nullptr )? 
 
It is not clear who has the responsibility to destroy the pointer given to the original addAnimal function. We solve it by clearly stating in the brief that we have the responsibility over the object pointed to by the pointer.
The drawOn function of the lab now includes the draw on functions of Hamster and Pellet (only if the pointer is not nullptr)
[Question Q2.5] What modification should be made to Lab to implement this functionality without memory leaks? 
We created two helper functions: clearEntities and clearCages
The first one deletes the allocated memory of the entities and sets them to nullptr. The second calls first the clearEntities function followed by a deallocation of memory used by the cages
[Question Q2.6] A laboratory is non-copyable (is not intended to share its content with another laboratory). A Lab can therefore be considered responsible for the lifespan of the Entities created in the simulation. How does this affect the destruction of a Lab ? Answer these questions in your REPONSES file and implement the suggested developments. 
 
We added clearCages to the destructor.
 
[Question Q2.7] How do you propose to proceed to display the energy levels without repeating in Hamster and Pellets the instructions used to display the desired text? 
 
We added a method drawEnergy to the entity class, so both Hamster and Pellets can access it.
 
[Question Q2.8] What other modification do you need to make to the Lab class so that this is now concretely the case for our hamster and our pile of pellets (once again be careful, they may not exist and watch out for memory leaks! ). 
 
We added a increaseAge function to the entity class that is called upon (after checking it exists) in the update function

[Question Q2.9] Here we make a first small foray into the application of polymorphism. Why should the method returning longevity here be marked as virtual? 

Because a fly doesn't live as long as a turtle: we want to make it possible to give different animals different longevities while keeping the code (here the isDead function) compact.

*************************************************

[Question Q3.1] Pourquoi le symbole & après auto dans la boucle réalisant les upate?
 
If the update method makes a nullptr, this change needs to be made to the Entities attribute and not a local copy of the element. Therefore, an iteration through the element can only update the pointer (in case of death) if it also gets the actual pointer. (Changing the object pointed to, for example age and position, would be also possible without the & symbol.)
 
[Question Q3.2] Pourquoi une collection de pointeurs  ?
 
Because we want to make use of virtual methods and polymorphism. Since a vector of references is not possible, a vector of pointers is our only option.
 
[Question Q3.3] Les méthodes de dessin des Hamster et Pellets sont pour l'heure probablement quasiment identiques (seul l'accès à la texture change), ce qui induit des duplications de code. Sachant que la façon de dessiner les informations de debugging peut être amenée à être spécifique (plus d'informations à afficher en mode «debug» pour les animaux que pour les tas de granulés par exemple), quelles modifications suggérez vous d'apporter au code existant pour éviter les duplications de codes non nécessaires lors du dessin des objets?
 
To avoid copying the code, we made a function drawOn in entity, that calls (as a parameter) the function getTexture, which is virtual and overwritten in Hamster and Pellet to get the corresponding texture. Hence, we don't copy code.
 
[Question Q3.4] Quelles retouches devez vous apporter à votre programme pour que les entités en fin de vie continuent de disparaître proprement et pour que le «reset» et la destruction du Lab demeurent corrects ?
 
It is important to deallocate the memory used by the object the pointer points to before setting them to nullptr and deleting them. 
This is the case with two functions: clearEntities and update, where we made sure to free up all the memory.
 
[Question Q3.5] : comment redéfinir getCenter dans Entity pour que la position de l'entité correspondent à son centre en tant que CircularBody? 
 
After making the getCenter method purely virtual, we only had to rename the Entity::getPosition getter to Entity::getCenter.
 
[Question Q3.6] : quelle autre conception est-il possible de mettre en place pour utiliser la classe CircularBody en vue de faire des tests de collision entre Entity ? Quel avantage/inconvénient y voyez-vous à ce stade ? 
 
It would be possible for the entity to HAVE a circular body as an attribute. 
Advantages: We wouldn't have to modify circular body as much (or operator didn't work anymore because CircularBody is now an abstract class)
 
Disadvantages: Conceptually it makes much more sense  that Entity is a CircularBody. Further, the implimentation of movement would be more difficult for the animal class, since the attribute position wouldn belong to it anymore

[Question Q3.8] : Quelle méthode(s) parmi celle(s) que vous avez introduite vous semble t-elle devoir être polymorphique ? 
Cage::isEmpty() & Cage::reset: not polymorphic because only Cage is concerned
 
Entity::adjustPosition() is not polymorphic because it is the same for each entity.
 
Entity::canBeConfinedIn(Cage*): It is polymorphic. We defined it in Entity as returning true. In the animal class, this is overwritten as returning false if there is already an animal inside.
 
[Question Q3.9] : Où vous semble t-il pertinent de placer le traitement permettant d'ajuster la position d'une entité trop proche d'un mur ?

In Entity because position is an attribute of Entity, and we don't want to break encapsulation.
 
[Question Q3.10] : Comment proposez vous de procéder pour, que lors de son passage à l'état WANDERING, un animal adopte une vélocité constante de getMaxSpeed? 

We created a new function Animal::getAdjustedMaxSpeed() that returns the adapted value for all animals (and doesn't leave choice up to the adder of a new animal class)
 
[Question Q3.11] Comment proposez vous pour faire en sorte qu'un animal continue de vieillir sans dupliquer le code qui le fait vieillir ? 

Call the Entity::update function with the indication of the port.
 
[Question Q3.12] Quelles méthodes proposez-vous d'ajouter et à quelle(s) classe(s) pour garantir que l'animal se retourne dans la direction opposée à son déplacement si la nouvelle position calculée par la méthode move induit une collision avec l'un des murs de l'une des boites du laboratoire? 
 
We chose to calculate the displacement vector and check if it collides in Animal (overloaded inCollison function), since it is the class contaning the attribute speed. For this, we created helper functions to setPosition or flipOrientation and used the modularized functions from the first part.
 
[Question Q3.13] Comment proposez-vous de modifier la méthode getMaxSpeed de sorte à ce qu'en dessous d'un seuil critique d'énergie l'animal se déplace plus lentement ? 
 
We tried multiple versions. In one of them we modified the value in the getMaxSpeed function in the hamster class. However, the implementation of a new animal would be unnecessary difficult. Therefore, we simply added getAdjustedMaxSpeed that modifies the speed (with virtual getters for the fatigue energy and the scaler of the speed to facilitate the implementation of new animal classes). 
 
[Question Q3.14] Pourquoi tester le type des objets à l'exécution est-il potentiellement nocif  ? 
 
This list would have to be updated every time a new type of entity (maybe completely unrelated to the hamsters) is added to the lab, which is easily forgotten. Hence, encapsulation would be broken.
 
[Question Q3.15] Pourquoi selon vous cela n'est pas une bonne idée de stocker la masse du hamster dans un attribut ? (en quoi cela fait-il perdre un avantage offert par les fichiers de configuration ?) Répondez à cette question dans votre fichier REPONSES (et pensez-y à chaque fois que vous souhaiterez utiliser un attribut pour une donnée paramétrable). 
 
First, all the parameters are concentrated in one compact file, changing them is made easy. Therefore, it allows us to play around and test the edge cases more easily using the central configuration file instead of searching the initialization somewhere in our code. 
 
[Question Q3.16] Quelle(s) méthode(s) proposez-vous de mettre en place et dans quelle classe pour permettre de simuler la consommation de nourriture par un Animal? 

First, it is (again) checked in the function eatFood if the entity can eat the other entity. Then, we added the virtual function provideEnergy to the entity class that does nothing. In food it has been overwritten to do the correct thing. These helper functions are managed from the Animal::eatFood() function

[Question Q3.17] Comment proposez-vous de mettre en oeuvre le pas 1 de l'algorithme de Animal::update sans donner un accès publique à toutes les entités simulées depuis Lab : quelles méthodes/attributs ajoutez vous et à quelles classes et au moyen de quelle(s) méthodes déjà codée(s). 

We decided to break encapsulation as little as possible by creating the method getClosesedEatableEntity in the lab class that returns only the pointer to the closest eatable entity (as the name suggests). Then, the rest is managed in animal class.

[Question Q3.18] Quel nouvel algorithme proposez-vous pour updateState afin de mettre en oeuvre proprement les transitions d'états suggérées par l'algorithme ci-dessus? 

We implemented it as described in the enounce. It is important to note that an animal can only be feeding if it can be targeting and that it can only be idle if it can be wandering.
 
[Question Q3.19 ] : les classes fournies dans le répertoire Interface, à savoir Drawable et Updatable, fournissent deux méthodes polymorphiques drawOn et update. Quelles classes de votre conception actuelle serait-il bon de faire hériter de ces sous-classes ? Quel plus cela amène t-il à la conception ? 
 
Updatable: Lab, Entity
Drawable: Lab, Entity, Cage
 
First of all, it makes the central properties updatable and drawable visible on a class structural level.
Further, we can organize things on a more general level (like the getDepth function).

*************************************************

