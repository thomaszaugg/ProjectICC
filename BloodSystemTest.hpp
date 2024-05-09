/*
 *  POOSV 2024
 * Marco Antognini & Jamila Sam
 */

#pragma once

#include <Application.hpp>
#include <Env/Hamster.hpp>
#include <Env/Organ.hpp>

/*!
 * Test generation of capilarity
 *
 * Choose one point of the artery
 * Generate one cell of capilary on click
 */

class TransplantOrgan : public Organ
{
public:
  TransplantOrgan()
    :Organ(false) // precludes content generation
  {
		
    generate();
  }

  // shadowing here
  // overriding is useless since polymorphic behaviour is ignored
  // in constructors
  void generate() 
  {
    reloadConfig();
    initOrganTexture();
    createBloodSystem(false); // blood system only with artery
    updateRepresentation();
  }
public:
  // breaking encapsulation for the TransplantOrgan class
  bool generateCapillaryOneStep(CellCoord& current_position, const CellCoord& initial_dir, int& nbCells, const int& maxLength) override;
//I changed the return type

  CellCoord toCellCoord(Vec2d const& substrateCoord) const override
  {
    return Organ::toCellCoord(substrateCoord);
  }
	
};


class TransplantedHamster : public Hamster
{
public:
  TransplantedHamster(Vec2d const& position)
    : Hamster(position)
  {}
	
  void replaceOrgan(TransplantOrgan* org)
  {
    transplant(org);
  }
};

class BloodSystemTest : public Application
{
public:
  BloodSystemTest(int argc, char const** argv)
    : Application(argc, argv)
  {
  }
  virtual void onRun() override final;
  virtual void onUpdate(sf::Time dt) override final;
  virtual void onEvent(sf::Event event, sf::RenderWindow& window) override final;
  virtual void onSimulationStart() override final;
  virtual void onDraw(sf::RenderTarget& target) override final;
  //virtual void resetStats() override final;
  std::string virtual getWindowTitle() const override final;
  std::string getHelpTextFile() const override final;
private:
  TransplantOrgan* mCurrentOrgan = nullptr;
  TransplantedHamster* mTransplantedHamster = nullptr;
  CellCoord mCurrentStart;
  CellCoord mCurrentDir;
  bool mStartCapillary = true;
  bool mSimulationStart = true;
  int mCurrentCapillaryLength = 0;
};
