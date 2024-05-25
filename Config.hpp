/*
 * POOSV 2024
 * Marco Antognini & Jamila Sam
 */

#pragma once

#include <string>
#include "JSON/JSON.hpp"
#include <SFML/Graphics.hpp>


class Config
{
private:
    j::Value mConfig;
    bool simulation_debug;

public:
    Config(const j::Value& cfg);

    // enables / disables debug mode
    void switchDebug();
    bool getDebug();

    // returns read
    j::Value& getJsonRead()
    {
        return mConfig;
    }

    j::Value const& getJsonRead() const
    {
        return mConfig;
    }


    //window
    const double window_simulation_width;
    const double window_simulation_height;
    const double window_stats_height;
    const double window_control_width;
    const std::string  window_title;
    const int window_antialiasing_level;

    // stats
    const double stats_refresh_rate;
    const std::string stats_log_folder = "logs/";
    const std::string stats_log_prefix = "log_";
    const std::string stats_log_header = "# Plot with GNUPLOT : gnuplot -e \"plot for [i=1:6] 'log_0.txt' u i w l title columnheader(i)\"";

    // debug
    const sf::Color debug_text_color = sf::Color::White;
    const size_t default_debug_text_size = 20;


    //simulation
    const std::string simulation_lab_texture;
    const std::string simulation_lab_debug_texture;
    const std::string simulation_lab_fence;
    const int  simulation_lab_size;
    const int  simulation_lab_nb_boxes;
    const double simulation_lab_min_box_size;
    const double  simulation_time_factor;
    const double  simulation_fixed_step;
    const sf::Time  simulation_time_max_dt;

    // organ
    const j::Value simulation_organ;
    const int  simulation_organ_size;
    const int  simulation_organ_nbCells;
    const std::string ecm_texture;
    const std::string blood_texture;
    const std::string organ_texture;
    const std::string concentration_texture;
    const std::string tumoral_texture;

    const double base_atp_usage;
    const double range_atp_usage;
    const double initial_atp;
    // blood system

    const int blood_capillary_min_dist;
    const int blood_creation_start;


    // healthy organ cell
    const double organ_fract_uptake;
    const double organ_km_glycolysis;
    const double organ_km_max_glycolysis;
    const double organ_km_krebs;
    const double organ_km_max_krebs;
    const int organ_time_next_division;
    const int organ_range_next_division;
    const int organ_decay_atp;
    const double organ_division_cost;
    const int organ_division_radius;
    const double organ_division_energy;
    const double organ_glucose_usage;
    const double organ_K_inhibitor;

    // cancer cell
    const double cancer_fract_uptake;
    const double cancer_km_glycolysis;
    const double cancer_km_max_glycolysis;
    const int cancer_time_next_division;
    const int cancer_range_next_division;
    const double cancer_division_energy;
    const double cancer_glucose_usage;
    const int cancer_threshold;

    // living entity
    const std::string entity_texture_tracked = "target.png";
    const double entity_energy_critical = 5;

    // food
    const std::string food_texture;
    const double food_initial_energy = 30;
    const double food_max_energy = 300;

    //cheese
    const std::string cheese_texture;
    const double cheese_initial_energy = 30;
    const double cheese_max_energy = 300;

    // animal
    const bool animal_random_walk_low_energy;
    const double animal_meal_retention ;
    const float animal_feed_time;
    const double animal_satiety_min;
    const double animal_satiety_max;
    const double animal_idle_probability;
    const float animal_idle_time_min;
    const float animal_idle_time_max;
    const double animal_min_energy;
    const float animal_base_energy_consumption;
    const double animal_rotation_delay;
    const double animal_fatigue_factor;

    // hamster
    const double hamster_max_speed;
    const double hamster_mass;
    const double hamster_energy_loss_factor;
    const double hamster_view_range;
    const double hamster_view_distance;
    const sf::Time hamster_longevity;
    const double hamster_energy_initial;
    const std::string hamster_texture_brown;
    const std::string hamster_texture_sick;
    const double hamster_size;
    const double hamster_energy_bite;
    const double hamster_deceleration;

    // substance
    const double substance_max_value;
    const int substance_diffusion_radius;
    const int vgef_diffusion_radius;
    const double substance_diffusion_constant;
    const double base_glucose;
    const double base_bromo;
    const double delta_glucose;
    const double delta_bromo;
    const double delta_vgef;
};


