#include "Config.hpp"
#include <JSON/JSONSerialiser.hpp>
// window
Config::Config (const j::Value& cfg): mConfig(cfg)
    , simulation_debug(mConfig["debug"].toBool())
    , window_simulation_width(mConfig["window"]["simulation"]["size"].toDouble())
    , window_simulation_height(mConfig["window"]["simulation"]["size"].toDouble())
    , window_stats_height(mConfig["window"]["stats"]["height"].toDouble())
    , window_control_width(mConfig["window"]["control"]["width"].toDouble())
    , window_title(mConfig["window"]["title"].toString())
    , window_antialiasing_level(mConfig["window"]["antialiasing level"].toInt())

// stats
    , stats_refresh_rate(mConfig["stats"]["refresh rate"].toDouble())

// simulation
    , simulation_lab_texture(mConfig["simulation"]["lab"]["texture"].toString())
    , simulation_lab_debug_texture(mConfig["simulation"]["lab"]["debug texture"].toString())
    , simulation_lab_fence(mConfig["simulation"]["lab"]["fence"].toString())
    , simulation_lab_size(mConfig["simulation"]["lab"]["size"].toDouble())
    ,  simulation_lab_nb_boxes(mConfig["simulation"]["lab"]["initial nb boxes"].toInt())
    ,  simulation_lab_min_box_size(mConfig["simulation"]["lab"]["min box size"].toDouble())
    , simulation_time_factor(mConfig["simulation"]["time"]["factor"].toDouble())
    , simulation_fixed_step(mConfig["simulation"]["time"]["fixed step"].toDouble())
    , simulation_time_max_dt(sf::seconds(mConfig["simulation"]["time"]["max dt"].toDouble()))

    //Organ
    , simulation_organ(mConfig["simulation"]["organ"])
    , simulation_organ_size(mConfig["simulation"]["organ"]["size"].toDouble())

    , simulation_organ_nbCells(mConfig["simulation"]["organ"]["cells"].toInt())
    ,ecm_texture(mConfig["simulation"]["organ"]["textures"]["ecm cell"].toString())

    ,blood_texture(mConfig["simulation"]["organ"]["textures"]["blood cell"].toString())
    ,organ_texture(mConfig["simulation"]["organ"]["textures"]["organ cell"].toString())
    ,concentration_texture(mConfig["simulation"]["organ"]["textures"]["concentration"].toString())

    ,tumoral_texture(mConfig["simulation"]["organ"]["textures"]["cancer"].toString())
    , base_atp_usage(mConfig["simulation"]["organ"]["atp"]["base usage"].toDouble())
    , range_atp_usage(mConfig["simulation"]["organ"]["atp"]["range"].toDouble())
   ,initial_atp(mConfig["simulation"]["organ"]["atp"]["initial energy"].toDouble())

    // Blood system
    ,blood_capillary_min_dist(mConfig["simulation"]["organ"]["blood"]["capillary min dist"].toInt())
    ,blood_creation_start(mConfig["simulation"]["organ"]["blood"]["creation start"].toInt())

    // healthy organ cell

    ,organ_fract_uptake(mConfig["simulation"]["organ"]["healthy"]["fract uptake"].toDouble())
    ,organ_km_glycolysis(mConfig["simulation"]["organ"]["healthy"]["km glycolysis"].toDouble())
    ,organ_km_max_glycolysis(mConfig["simulation"]["organ"]["healthy"]["km max glycolysis"].toDouble())
    ,organ_km_krebs(mConfig["simulation"]["organ"]["healthy"]["km krebs"].toDouble())
    ,organ_km_max_krebs(mConfig["simulation"]["organ"]["healthy"]["km max krebs"].toDouble())
    ,organ_time_next_division(mConfig["simulation"]["organ"]["healthy"]["time next division"].toInt())
    ,organ_range_next_division(mConfig["simulation"]["organ"]["healthy"]["range next division"].toInt())
    ,organ_decay_atp(mConfig["simulation"]["organ"]["healthy"]["decay atp"].toInt())
    ,organ_division_cost(mConfig["simulation"]["organ"]["healthy"]["division cost"].toDouble())	,organ_division_radius(mConfig["simulation"]["organ"]["healthy"]["division radius"].toInt())
    ,organ_division_energy(mConfig["simulation"]["organ"]["healthy"]["division energy"].toDouble())
    ,organ_glucose_usage(mConfig["simulation"]["organ"]["healthy"]["glucose usage"].toDouble())
    ,organ_K_inhibitor(mConfig["simulation"]["organ"]["healthy"]["K inhibitor"].toDouble())

    // cancer cell
    ,cancer_fract_uptake(mConfig["simulation"]["organ"]["cancer"]["fract uptake"].toDouble())
    ,cancer_km_glycolysis(mConfig["simulation"]["organ"]["cancer"]["km glycolysis"].toDouble())
    ,cancer_km_max_glycolysis(mConfig["simulation"]["organ"]["cancer"]["km max glycolysis"].toDouble())
    ,cancer_time_next_division(mConfig["simulation"]["organ"]["cancer"]["time next division"].toInt())
    ,cancer_range_next_division(mConfig["simulation"]["organ"]["cancer"]["range next division"].toInt())
    ,cancer_division_energy(mConfig["simulation"]["organ"]["cancer"]["division energy"].toDouble())
    ,cancer_glucose_usage(mConfig["simulation"]["organ"]["cancer"]["glucose usage"].toDouble())
    ,cancer_threshold(mConfig["simulation"]["organ"]["cancer"]["threshold"].toInt())
// food
    , food_texture(mConfig["simulation"]["food"]["texture"].toString())
//, grass_size(mConfig["simulation"]["grass"]["size"].toDouble())
    , food_initial_energy(mConfig["simulation"]["food"]["energy"]["initial"].toDouble())
    , food_max_energy(mConfig["simulation"]["food"]["energy"]["max"].toDouble())

// cheese
, cheese_texture(mConfig["simulation"]["cheese"]["texture"].toString())
, cheese_initial_energy(mConfig["simulation"]["cheese"]["energy"]["initial"].toDouble())
, cheese_max_energy(mConfig["simulation"]["cheese"]["energy"]["max"].toDouble())


// animal
    , animal_random_walk_low_energy(mConfig["simulation"]["animal"]["random walk low energy"].toBool())
//, animal_safe_distance(mConfig["simulation"]["animal"]["random walk low energy"].toDouble())
    , animal_meal_retention(mConfig["simulation"]["animal"]["meal retention"].toDouble())
    , animal_feed_time(mConfig["simulation"]["animal"]["feed time"].toDouble())
    , animal_satiety_min(mConfig["simulation"]["animal"]["satiety"]["min"].toDouble())
    , animal_satiety_max(mConfig["simulation"]["animal"]["satiety"]["max"].toDouble())
    , animal_idle_probability(mConfig["simulation"]["animal"]["idle"]["probability"].toDouble())
    , animal_idle_time_min(mConfig["simulation"]["animal"]["idle"]["min"].toDouble())
    , animal_idle_time_max(mConfig["simulation"]["animal"]["idle"]["max"].toDouble())
    , animal_min_energy(mConfig["simulation"]["animal"]["min energy"].toDouble())
    , animal_fatigue_factor(mConfig["simulation"]["animal"]["fatigue factor"].toDouble())
    , animal_base_energy_consumption(mConfig["simulation"]["animal"]["base consumption"].toDouble())
    , animal_rotation_delay(mConfig["simulation"]["animal"]["rotation delay"].toDouble())
// hamster
    , hamster_max_speed(mConfig["simulation"]["animal"]["hamster"]["max speed"].toDouble())
    , hamster_mass(mConfig["simulation"]["animal"]["hamster"]["mass"].toDouble())
    , hamster_energy_loss_factor(mConfig["simulation"]["animal"]["hamster"]["energy"]["loss factor"].toDouble())
    , hamster_view_range(mConfig["simulation"]["animal"]["hamster"]["view"]["range"].toDouble())
    , hamster_view_distance(mConfig["simulation"]["animal"]["hamster"]["view"]["distance"].toDouble())
    , hamster_longevity(sf::seconds(mConfig["simulation"]["animal"]["hamster"]["longevity"].toDouble()))
    , hamster_energy_initial(mConfig["simulation"]["animal"]["hamster"]["energy"]["initial"].toDouble())
    , hamster_texture_brown(mConfig["simulation"]["animal"]["hamster"]["texture"]["brown"].toString())
    , hamster_texture_sick(mConfig["simulation"]["animal"]["hamster"]["texture"]["sick"].toString())
    , hamster_size(mConfig["simulation"]["animal"]["hamster"]["size"].toDouble())
    , hamster_energy_bite(mConfig["simulation"]["animal"]["hamster"]["energy"]["bite"].toDouble())
    , hamster_deceleration(mConfig["simulation"]["animal"]["hamster"]["hamster_deceleration"].toDouble())

    // substance
    ,substance_max_value(mConfig["simulation"]["substance"]["max"].toDouble())
    ,substance_diffusion_radius(mConfig["simulation"]["substance"]["diffusion radius"].toInt())
    ,vgef_diffusion_radius(mConfig["simulation"]["substance"]["vgef"]["diffusion radius"].toInt())

    ,substance_diffusion_constant(mConfig["simulation"]["substance"]["diffusion constant"].toDouble())
    ,base_glucose(mConfig["simulation"]["substance"]["glucose"]["base"].toDouble())
    ,base_bromo(mConfig["simulation"]["substance"]["bromopyruvate"]["base"].toDouble())
    ,delta_glucose(mConfig["simulation"]["substance"]["glucose"]["delta"].toDouble())
    ,delta_bromo(mConfig["simulation"]["substance"]["bromopyruvate"]["delta"].toDouble())
    ,delta_vgef(mConfig["simulation"]["substance"]["vgef"]["delta"].toDouble())

{
}

// TODO : getter for debug
void Config::switchDebug()
{
    mConfig["debug"] = j::boolean(!mConfig["debug"].toBool());
    simulation_debug = mConfig["debug"].toBool();
}

bool Config::getDebug()
{
    return simulation_debug;
}
