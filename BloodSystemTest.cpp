/*
 *  POOSV 2024
 * Marco Antognini & Jamila Sam
 */

#include <Tests/GraphicalTests/BloodSystemTest.hpp>
#include <Utility/Utility.hpp>
#include <Env/Organ.hpp> // UNCOMMENT WHEN READY
#include <Env/Lab.hpp>
#include <Env/Hamster.hpp>

IMPLEMENT_MAIN(BloodSystemTest)

void BloodSystemTest::onRun()
{
}
void BloodSystemTest::onSimulationStart()
{
  mCurrentOrgan = new TransplantOrgan();
  mTransplantedHamster = new TransplantedHamster(getApp().getLabSize()/2);
  mTransplantedHamster->replaceOrgan(mCurrentOrgan);
  mStartCapillary = true;
  mSimulationStart = true;
  mCurrentCapillaryLength = 0;
  mSimulationStart=true;
}

void BloodSystemTest::onUpdate(sf::Time /*dt*/)
{
  if (mSimulationStart){
    getAppEnv().reset();
    getAppEnv().addAnimal(mTransplantedHamster);
    getAppEnv().trackAnimal(mTransplantedHamster);
    getApp().switchToView(ECM);
    mSimulationStart = false;
  }
}

bool TransplantOrgan::generateCapillaryOneStep(CellCoord& current_position, const CellCoord& initial_dir, int& nbCells, const int& maxLength)
{

  return Organ::generateCapillaryOneStep(current_position, initial_dir, nbCells, maxLength);
}

void BloodSystemTest::onEvent(sf::Event event, sf::RenderWindow&)
{
  if (event.type == sf::Event::KeyPressed) {
    switch (event.key.code) {
    case sf::Keyboard::Num0: // to start a new capillary
      {
	mStartCapillary = true;
	mCurrentCapillaryLength = 0;
      }
      break;
			
    case sf::Keyboard::Num6:
      {

	// UNCOMMENT WHEN READY
	if (mStartCapillary)
	  {
	    auto position(getCursorPositionInView());
	    mCurrentStart = mCurrentOrgan->toCellCoord(position);
	    mStartCapillary = false;
	    mCurrentDir = CellCoord(1,0);					

	  }
	mCurrentOrgan->generateCapillaryOneStep(mCurrentStart,
						mCurrentDir,
						mCurrentCapillaryLength,
						getAppConfig().simulation_organ_nbCells/2);
      } 

      break;
		
    case sf::Keyboard::Num5:
      {

	// UNCOMMENT WHEN READY
	if (mStartCapillary)
	  {
	    auto position(getCursorPositionInView());
	    mCurrentStart = mCurrentOrgan->toCellCoord(position);
	    mStartCapillary = false;
	    mCurrentDir = CellCoord(-1,0);					

	  }
	mCurrentOrgan->generateCapillaryOneStep(mCurrentStart,
	mCurrentDir, 
	mCurrentCapillaryLength, 
	getAppConfig().simulation_organ_nbCells/2);
      }

      break;		
    default:
      break;
    }
  }
}


  /* void BloodSystemTest::resetStats(){
  // Application::resetStats();

  }
*/

void BloodSystemTest::onDraw(sf::RenderTarget& /*target*/)
{
  // ADD INSTRUCTIONS IF NEEDED
}

std::string BloodSystemTest::getWindowTitle() const {
  return getAppConfig().window_title  + " (BloodSystemTest)";
}

std::string BloodSystemTest::getHelpTextFile() const {
  return RES_LOCATION + "help-bloodSystem.txt";
}
