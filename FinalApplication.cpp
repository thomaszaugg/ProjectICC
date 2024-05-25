/*
 * POOSV 2024
 * Marco Antognini & Jamila Sam
 */

#include <Config.hpp>
#include <Tests/GraphicalTests/FinalApplication.hpp>
#include <Env/Hamster.hpp>
#include <Env/Pellets.hpp>
#include <Env/Cage.hpp>
#include <Env/Cheese.hpp>
#include <iostream>
#include <cassert>

IMPLEMENT_MAIN(FinalApplication);

void FinalApplication::onRun()
{
  // Setup stats
  Application::onRun();
}

void FinalApplication::onSimulationStart()
{
  // TODO add more stuff here
  Application::onSimulationStart();
}

void FinalApplication::onEvent(sf::Event event, sf::RenderWindow&)
{
  if (event.type == sf::Event::KeyReleased) {
    switch (event.key.code){

    case sf::Keyboard::H:
      {
	if (!isOrganViewOn()){
	  getAppEnv().addAnimal(new Hamster
				(getCursorPositionInView()));
	}
      }
      break;
	
    case sf::Keyboard::F: // F for food
      {	if (!isOrganViewOn()){
      getAppEnv().addEntity(new Pellets
				(getCursorPositionInView()));
	}
					
      }
      break;

    case sf::Keyboard::C: // C for cheese
    {	if (!isOrganViewOn()){
            getAppEnv().addEntity(new Cheese
                                  (getCursorPositionInView()));
        }

    }
    break;
			
    case sf::Keyboard::S: // S stands for Substance
      {
	if (isOrganViewOn()){
	  toggleConcentrationView();
	}
      }
      break;
				

    case sf::Keyboard::X: 
      {

         //UNCOMMENT in STEP 6
        if (isOrganViewOn()){
        getAppEnv().setCancerAt(getCursorPositionInView());
        }

      }
      break;

    case sf::Keyboard::N: // next substance
    {

         //UNCOMMENT in STEP 6
        {
        if (isOrganViewOn()){
          getAppEnv().nextSubstance();
        }
			

      }
      break;

    case sf::Keyboard::Num3:
    case sf::Keyboard::PageUp: // increase substance
      {

         //UNCOMMENT in STEP 6
        if (isOrganViewOn()){
        getAppEnv().increaseCurrentSubst();
        }

      }
      break;

    case sf::Keyboard::Num2:
    case sf::Keyboard::PageDown: // decrease substance
      {

         //UNCOMMENT in STEP 6
        if (isOrganViewOn()){
         getAppEnv().decreaseCurrentSubst();
        }

      }
      break;
			

    case sf::Keyboard::T:
      {

         //UNCOMMENT WHEN READY
	getAppEnv().trackAnimal(getCursorPositionInView());

      }
      break;
			
    case sf::Keyboard::Z:
      {

         //UNCOMMENT WHEN READY
	if (!isOrganViewOn()){
	  getAppEnv().stopTrackingAnyEntity();
	}

      }
      break;

    default:
      break;
    }
  }
  }}

void FinalApplication::onDraw(sf::RenderTarget& /*target*/)
{
  // ADD INSTRUCTIONS IF NEEDED
}
