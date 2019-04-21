#include "editor.h"

#include "scenario/data.h"
#include "scenario/property.h"

void scenario_editor_request_get(int index, editor_request *request)
{
    request->year = scenario.requests[index].year;
    request->amount = scenario.requests[index].amount;
    request->resource = scenario.requests[index].resource;
    request->deadline_years = scenario.requests[index].deadline_years;
    request->favor= scenario.requests[index].favor;
}

void scenario_editor_invasion_get(int index, editor_invasion *invasion)
{
    invasion->year = scenario.invasions[index].year;
    invasion->type = scenario.invasions[index].type;
    invasion->amount = scenario.invasions[index].amount;
    invasion->from = scenario.invasions[index].from;
    invasion->attack_type = scenario.invasions[index].attack_type;
}

void scenario_editor_cycle_image(int forward)
{
    if (forward) {
        scenario.image_id++;
    } else {
        scenario.image_id--;
    }
    if (scenario.image_id < 0) {
        scenario.image_id = 15;
    }
    if (scenario.image_id > 15) {
        scenario.image_id = 0;
    }
}

void scenario_editor_cycle_climate(void)
{
    switch (scenario.climate) {
        case CLIMATE_CENTRAL:
            scenario.climate = CLIMATE_NORTHERN;
            break;
        case CLIMATE_NORTHERN:
            scenario.climate = CLIMATE_DESERT;
            break;
        case CLIMATE_DESERT:
        default:
            scenario.climate = CLIMATE_CENTRAL;
            break;
    }
}

void scenario_editor_set_enemy(int enemy_id)
{
    scenario.enemy_id = enemy_id;
}

int scenario_editor_is_building_allowed(int id)
{
    return scenario.allowed_buildings[id];
}

void scenario_editor_toggle_building_allowed(int id)
{
    scenario.allowed_buildings[id] = scenario.allowed_buildings[id] ? 0 : 1;
}

int scenario_editor_earthquake_severity(void)
{
    return scenario.earthquake.severity;
}

int scenario_editor_earthquake_year(void)
{
    return scenario.earthquake.year;
}

void scenario_editor_earthquake_cycle_severity(void)
{
    scenario.earthquake.severity++;
    if (scenario.earthquake.severity > EARTHQUAKE_LARGE) {
        scenario.earthquake.severity = EARTHQUAKE_NONE;
    }
}

void scenario_editor_earthquake_set_year(int year)
{
    scenario.earthquake.year = year;
}

int scenario_editor_gladiator_revolt_enabled(void)
{
    return scenario.gladiator_revolt.enabled;
}

int scenario_editor_gladiator_revolt_year(void)
{
    return scenario.gladiator_revolt.year;
}

void scenario_editor_gladiator_revolt_toggle_enabled(void)
{
    scenario.gladiator_revolt.enabled = !scenario.gladiator_revolt.enabled;
}

void scenario_editor_gladiator_revolt_set_year(int year)
{
    scenario.gladiator_revolt.year = year;
}

int scenario_editor_emperor_change_enabled(void)
{
    return scenario.emperor_change.enabled;
}

int scenario_editor_emperor_change_year(void)
{
    return scenario.emperor_change.year;
}

void scenario_editor_emperor_change_toggle_enabled(void)
{
    scenario.emperor_change.enabled = !scenario.emperor_change.enabled;
}

void scenario_editor_emperor_change_set_year(int year)
{
    scenario.emperor_change.year = year;
}

int scenario_editor_sea_trade_problem_enabled(void)
{
    return scenario.random_events.sea_trade_problem;
}

void scenario_editor_sea_trade_problem_toggle_enabled(void)
{
    scenario.random_events.sea_trade_problem = !scenario.random_events.sea_trade_problem;
}

int scenario_editor_land_trade_problem_enabled(void)
{
    return scenario.random_events.land_trade_problem;
}

void scenario_editor_land_trade_problem_toggle_enabled(void)
{
    scenario.random_events.land_trade_problem = !scenario.random_events.land_trade_problem;
}

int scenario_editor_raise_wages_enabled(void)
{
    return scenario.random_events.raise_wages;
}

void scenario_editor_raise_wages_toggle_enabled(void)
{
    scenario.random_events.raise_wages = !scenario.random_events.raise_wages;
}

int scenario_editor_lower_wages_enabled(void)
{
    return scenario.random_events.lower_wages;
}

void scenario_editor_lower_wages_toggle_enabled(void)
{
    scenario.random_events.lower_wages = !scenario.random_events.lower_wages;
}

int scenario_editor_contaminated_water_enabled(void)
{
    return scenario.random_events.contaminated_water;
}

void scenario_editor_contaminated_water_toggle_enabled(void)
{
    scenario.random_events.contaminated_water = !scenario.random_events.contaminated_water;
}

int scenario_editor_iron_mine_collapse_enabled(void)
{
    return scenario.random_events.iron_mine_collapse;
}

void scenario_editor_iron_mine_collapse_toggle_enabled(void)
{
    scenario.random_events.iron_mine_collapse = !scenario.random_events.iron_mine_collapse;
}

int scenario_editor_clay_pit_flooded_enabled(void)
{
    return scenario.random_events.clay_pit_flooded;
}

void scenario_editor_clay_pit_flooded_toggle_enabled(void)
{
    scenario.random_events.clay_pit_flooded = !scenario.random_events.clay_pit_flooded;
}
